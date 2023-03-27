#include <iostream>
#include "StatManager.h"

int main() {
    StatManager statManager;

    statManager.writeStatsToDatabase("player42");

    statManager.gameStat.getTotalPlayerCount();
    statManager.playerStat.getDeathCount();
}
