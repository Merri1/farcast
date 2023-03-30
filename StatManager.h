//
// Created by merri on 20/03/23.
//

#ifndef FARCAST_STATMANAGER_H
#define FARCAST_STATMANAGER_H

#include "include/httplib.h"
#include "include/json.hpp"

class StatManager {
public:
    StatManager();
    void setApiUrl(std::string url);
    void setGameToken(std::string token);
    void writeStatsToDatabase();
    void getStatsFromDatabase();
    void setPlayerName(std::string playerName);
    std::string getPlayerName();

    // Struct to store information about GameStat data. Getter and setter methods are included for updating or reading
    // fields from the statManager object in game
    struct GameStat{
        int id;
        int winCount;
        int lossCount;
        int totalPlayTime;
        int totalSessions;
        int totalPlayerCount;

        int getWinCount() const { return winCount; }
        void updateWinCount(int winCount) { GameStat::winCount += winCount; }
        int getLossCount() const { return lossCount; }
        void updateLossCount(int lossCount) { GameStat::lossCount += lossCount; }
        int getTotalPlayTime() const { return totalPlayTime; }
        void updateTotalPlayTime(int totalPlayTime) { GameStat::totalPlayTime += totalPlayTime; }
        int getTotalSessions() const { return totalSessions; }
        void updateTotalSessions(int totalSessions) { GameStat::totalSessions += totalSessions; }
        int getTotalPlayerCount() const { return totalPlayerCount; }
        void updateTotalPlayerCount(int totalPlayerCount) { GameStat::totalPlayerCount += totalPlayerCount; }
    };

    // Struct to store information about the Player Stat data
    struct PlayerStat{
        int id;
        int killCount;
        int deathCount;
        int totalScore;
        int totalPlayTime;
        int totalSessions;

        int getKillCount() const { return killCount; }
        void updateKillCount(int killCount) { PlayerStat::killCount += killCount; }
        int getDeathCount() const { return deathCount; }
        void updateDeathCount(int deathCount) { PlayerStat::deathCount += deathCount; }
        int getHighScore() const { return totalScore; }
        void updateHighScore(int totalScore) { PlayerStat::totalScore = totalScore; }
        int getTotalPlayTime() const { return totalPlayTime; }
        void updateTotalPlayTime(int totalPlayTime) { PlayerStat::totalPlayTime += totalPlayTime; }
        int getTotalSessions() const { return totalSessions; }
        void updateTotalSessions(int totalSessions) { PlayerStat::totalSessions += totalSessions; }
    };

    // Nlohmann macros to map GameStat and PlayerStat structs fields to JSON objects
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameStat,
                                   id,
                                   winCount,
                                   lossCount,
                                   totalPlayTime,
                                   totalSessions,
                                   totalPlayerCount
    );

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayerStat,
                                   id,
                                   killCount,
                                   deathCount,
                                   totalScore,
                                   totalPlayTime,
                                   totalSessions
    );

    // Instance of GameStat and PlayerStat structs for updaing and reading data at runtime
    StatManager::GameStat gameStat{};
    StatManager::PlayerStat playerStat{};

    // Variables for data that is used when making requests to the server
    std::string playerName;
    std::string apiUrl;
    std::string gameToken;

private:

};
#endif //FARCAST_STATMANAGER_H
