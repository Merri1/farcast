//
// Created by merri on 20/03/23.
//

#ifndef FARCAST_STATMANAGER_H
#define FARCAST_STATMANAGER_H

#include "GameStatistics.h"
#include "include/json.hpp"

class StatManager {
public:
    StatManager();
    void writeStatsToDatabase(std::string playername);
    void getStatsFromDatabase();

    struct GameStat{
        int getWinCount() const { return winCount; }
        void setWinCount(int winCount) { GameStat::winCount += winCount; }
        int getLossCount() const { return lossCount; }
        void setLossCount(int lossCount) { GameStat::lossCount += lossCount; }
        int getTotalPlayTime() const { return totalPlayTime; }
        void setTotalPlayTime(int totalPlayTime) { GameStat::totalPlayTime += totalPlayTime; }
        int getTotalSessions() const { return totalSessions; }
        void setTotalSessions(int totalSessions) { GameStat::totalSessions += totalSessions; }
        int getTotalPlayerCount() const { return totalPlayerCount; }
        void setTotalPlayerCount(int totalPlayerCount) { GameStat::totalPlayerCount += totalPlayerCount; }

        int id;
        int winCount;
        int lossCount;
        int totalPlayTime;
        int totalSessions;
        int totalPlayerCount;
    };

    struct PlayerStat{
        const std::string &getDisplayName() const { return displayName; }
        void setDisplayName(const std::string &displayName) { PlayerStat::displayName = displayName; }
        int getKillCount() const { return killCount; }
        void setKillCount(int killCount) { PlayerStat::killCount += killCount; }
        int getDeathCount() const { return deathCount; }
        void setDeathCount(int deathCount) { PlayerStat::deathCount += deathCount; }
        int getHighScore() const { return highScore; }
        void setHighScore(int highScore) { PlayerStat::highScore = highScore; }
        int getTotalPlayTime() const { return totalPlayTime; }
        void setTotalPlayTime(int totalPlayTime) { PlayerStat::totalPlayTime += totalPlayTime; }
        int getTotalSessions() const { return totalSessions; }
        void setTotalSessions(int totalSessions) { PlayerStat::totalSessions = +totalSessions; }

        int id;
        std::string displayName;
        int killCount;
        int deathCount;
        int highScore;
        int totalPlayTime;
        int totalSessions;
    };

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
                                       displayName,
                                       killCount,
                                       deathCount,
                                       highScore,
                                       totalPlayTime,
                                       totalSessions
                                   );

    StatManager::GameStat gameStat{};
    StatManager::PlayerStat playerStat{};

private:

};
#endif //FARCAST_STATMANAGER_H
