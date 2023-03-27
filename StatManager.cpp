//
// Created by merri on 20/03/23.
//
//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "StatManager.h"
#include "include/httplib.h"
#include "include/json.hpp"

using namespace std;

string gameToken = "213ef447-4b1a-444c-9ab8-73ed1dcb8741";
string apiUrl = "http://localhost:8080";
string gameStatEndpoint = "/game-stats/";
string gameStatUpdateEndpoint = "/game-stats/update/";

StatManager::StatManager() { }

void StatManager::getStatsFromDatabase() {
    httplib::Client client(apiUrl);

    auto response = client.Get(gameStatEndpoint + gameToken);

    if(response && response->status == 200) {
        nlohmann::json resultData = nlohmann::json::parse(response->body);
        gameStat = resultData;
        nlohmann::json j = gameStat;
        std::cout << j.dump(2) << endl;
    }
}

void StatManager::writeStatsToDatabase(string playerName) {
    // Convert gameStat struct to JSON format
    nlohmann::json gameData = gameStat;

    // Instantiate a http client pointed at the server URL
    httplib::Client client(apiUrl);

    // Send a post request to the server game-stats/update URL with a body of the gameStat Data
    auto response = client.Post(gameStatUpdateEndpoint, gameData.dump(), "application/json");

    // Check for a successful response from the server for gameStat
    if(response && response->status == 200) {
        // Save server response JSON in gameStat struct
        gameStat = nlohmann::json::parse(response->body);
        std::cout << "FAR-CAST: Server returned status 200. Success." << endl;
    }
    else {
        // Output error if any other http status returned
        std::cerr << "FAR-CAST: Server returned status " << response->status <<". Stat Write was unsuccessful" << endl;
    }

    // PlayerStat Post here
    //auto response = client.Post(playerStatEndpoint)
}


