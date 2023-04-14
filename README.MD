# Farcast

### Introduction
Farcast is a C++ library for managing Game and Player statistics in C++ games.
<br><br>
Farcast is one of three modules of my fourth year Final Year Project that I developed while studying Games Design and Development at TUS Thurles.
<br><br>
Details, documentation and git repo links to the other modules can be found [on my website](https://merri1.github.io).

## Usage

### Adding to project

1. Clone this repo and add it to the root of your C++ project. The structure should look like this:

```bash
YourProjectRoot
├── farcast
│   ├── StatManager.h
│   ├── StatManager.cpp
│   └── include
│       ├── httplib.h
│       └── json.hpp
├── main.cpp
├── GameEngine.cpp
├── GameObject.cpp
... And so on ...
```

<br>

2. Include this library in your main Game Engine class
    
       #include "StatManager/StatManager.h"

<br>

### API Calls
#### Connecting to server

1. First of all you need to create a StatManager object and then initialise it.

          StatManager statManager();

    - For initialisation you need a game token. Game tokens can be acquired from the [Hyperion](https://github.com/Merri1/hyperion) application after you've created an account and registered the game.
    - If the [Tau-Ceti](https://github.com/Merri1/tau-ceti) backend is running locally you do not need to add an apiUrl, it will default to localhost:8080.

          statManager.init("yourGameToken");
   
    - If the Tau-Ceti application is running on a remote pc you need to initialise with an API URL and port number. This could be a remote server or simply an IP address for a PC in the classroom.

          statManager.init("yourGameToken", "serverURLorIP:portnumber");

<br>

#### Retrieving stats from server
Ideally you will take in the player name at the start of your game. This library will pull overall Game stats and also Player Stats for a specific player name from the backend server.
2. Before retrieving data set the current players name:

       statManager.setPlayerName("Merri");
3. Retrieve data from the server. The best practice is to retrieve data once at the start of the game and the write data once before the game exits.

       statManager.getStatsFromDatabase();

<br>

#### Updating Stats during playtime
4. There are a number of stats you can update during playtime. The current value of the stat will be incremented 
    - These are divided into Game stats and Player stats. Game stats can be updated using the following function calls:

          statManager.gameStat.updateTotalSessions(int);
          statManager.gameStat.updateTotalPlayTime(int);
          statManager.gameStat.updateTotalPlayerCount(int);
          statManager.gameStat.updateLossCount(int);
          statManager.gameStat.updateWinCount(int);
    - While Player stats can be updated using these function calls:
          
          statManager.playerStat.updateDeathCount(int);
          statManager.playerStat.updateHighScore(int);
          statManager.playerStat.updateKillCount(int);
          statManager.playerStat.updateTotalPlayTime(int);
          statManager.playerStat.updateTotalSessions(int);
      - NOTE: The Player High Score is not evaluated in the statManager. You will need to check the current high score value and deem if the new score value exceeds it before calling the updateHighScore() function.
        <br><br>

    - All of these functions also have getter functions which can be called by replacing 'update' from the above examples with 'get'. For example, to get the player death count you would call:
                
          statManager.playerStat.getDeathCount();

<br>

#### Writing stats to server
5. After gameplay has finished but before the game exits you will want to write your updated game and player stats to the server. This can be done with the following:

       statManager.writeStatsToDatabase();

### That's it!
6. You should see your updated Game and player stats in the web frontend.
   
<br>

## License
MIT License (c) 2023 Merri Mogridge

## Credits
[JSON for modern C++](https://github.com/nlohmann/json) by nlohmann. 
    
    ./include/json.hpp

[cpp-httplib](https://github.com/yhirose/cpp-httplib) by yhirose.

    ./include/httplib.h

