//
// Created by merri on 20/03/23.
//
//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "StatManager.h"

using namespace std;

// Endpoints that will always be the same
const string gameStatEndpoint = "/game-stats/";
const string gameStatUpdateEndpoint = "/game-stats/update/";
const string playerStatEndpoint = "/player-stats/";
const string playerStatUpdateEndpoint = "/player-stats/update/";

StatManager::StatManager() { }

// Set the web address for the server
void StatManager::setApiUrl(std::string url) {
    this->apiUrl = url;
}

// Set the unique game token
void StatManager::setGameToken(std::string token) {
    this->gameToken = token;
}

// Set the current player name
void StatManager::setPlayerName(std::string playerName) {
    this->playerName = playerName;
}

// Return player name
std::string StatManager::getPlayerName() {
    return this->playerName;
}

// Get stats for Game and Player that are stored in the database
void StatManager::getStatsFromDatabase() {
    // Initialise a HTTP Client pointing to the server Url
    httplib::Client client(this->apiUrl);

    // Send a Get request to the gameStat endpoint with the current game token
    auto gameResponse = client.Get(gameStatEndpoint + this->gameToken);

    // Check the status of the response
    if(gameResponse && gameResponse->status == 200) {
        // Parse the JSON returned from the server and then save in the gameStat struct
        nlohmann::json resultGameData = nlohmann::json::parse(gameResponse->body);
        this->gameStat = resultGameData;
    }
    else {
        // Output error if any other http status returned
        cerr << "FAR-CAST: Server returned status " << gameResponse->status << ". Game Stat retrieval was unsuccessful" << endl;
    }

    // Send a Get request to the playerStat endpoint with the current game token and current player name
    auto playerResponse = client.Get(playerStatEndpoint + this->gameToken + "/" + this->playerName);

    // Check response of Get request
    if(playerResponse && playerResponse->status == 200) {
        // Parse server returned JSON and then store in playerStat struct
        nlohmann::json resultPlayerData = nlohmann::json::parse(playerResponse->body);
        this->playerStat = resultPlayerData;
    }
    else {
        // Output error if any other http status returned
        cerr << "FAR-CAST: Server returned status " << gameResponse->status <<". Player Stat retrieval was unsuccessful" << endl;
    }
}

// Write game and player stats to the server/database
void StatManager::writeStatsToDatabase() {
    // Convert gameStat struct to JSON format
    nlohmann::json gameData = this->gameStat;
    nlohmann::json playerData = this->playerStat;

    // Instantiate a http client pointed at the server URL
    httplib::Client client(this->apiUrl);

    // Send a post request to the server game-stats/update URL with a body of the gameStat Data
    auto gameResponse = client.Post(gameStatUpdateEndpoint + this->gameToken, gameData.dump(), "application/json");

    // Check for a successful response from the server for gameStat
    if(gameResponse && gameResponse->status == 200) {
        // Save server response JSON in gameStat struct
        this->gameStat = nlohmann::json::parse(gameResponse->body);
    }
    else {
        // Output error if any other http status returned
        cerr << "FAR-CAST: Server returned status " << gameResponse->status <<". Game Stat Update was unsuccessful" << endl;
    }

    // Send a post request to the server player-stats/update URL with a body of the gameStat Data appended with the gameToken and playerName
    auto playerResponse = client.Post(playerStatUpdateEndpoint + this->gameToken + "/" + this->playerName, playerData.dump(), "application/json");

    // Check for a successful response from the server for gameStat
    if(playerResponse && playerResponse->status == 200) {
        // Save server response JSON in gameStat struct
        this->playerStat = nlohmann::json::parse(playerResponse->body);
    }
    else {
        // Output error if any other http status returned
        cerr << "FAR-CAST: Server returned status " << playerResponse->status <<". Player Stat Update was unsuccessful" << endl;
    }
}