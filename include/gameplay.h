#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <chrono>
#include <utility>
#include <cmath>
#include "game.h"

class Gameplay {
public:
    Gameplay(const int &difficultyHighlight, GameState &current_state, bool isNewGame);
    ~Gameplay();
    void run();
    void addHistoryMessage(const std::string& message);

private:
    // Member Variables
    GameState &current_state; // Initialize current_State by reference to enable direct modification
    int difficultyHighlight;
    std::string diff_str;
    int map_size;
    int num_obs;
    int num_pkg;
    int height, width;
    int roundNumber;
    int currentStamina;
    int maxStamina;
    int staminaAtRoundStart;
    int stepsTakenThisRound;
    long long totalScore;
    int lastRoundStepScore;
    int lastRoundTimeScore;
    std::vector<std::string> historyMessages; // To store messages
    std::chrono::steady_clock::time_point startTime;

    // Package Tracking
    std::vector<bool> hasPackage; // Tracks if player is holding package i
    int currentPackageIndex;      // Index (0 to num_pkg-1) of selected package, -1 if none
    int packagesDelivered;

    // Gameplay Map & Player
    std::vector<std::string> mapGrid;
    int playerY, playerX;
    int exitY, exitX;
    std::vector<std::pair<int, int>> packagePickUpLocs;
    std::vector<std::pair<int, int>> packageDestLocs;
    std::vector<std::pair<int, int>> supplyStationLocations; // <<< Add this line
    std::vector<std::pair<int, int>> speedBumpLocations; // <<< This should already exist
    bool doubleStaminaCostNextMove;

    // Windows
    WINDOW *mapWin;
    WINDOW *statsWin;
    WINDOW *timeWin;
    WINDOW *legendWin;
    WINDOW *staminaWin;
    WINDOW *historyWin;
    WINDOW *packageWin;

    // Private Methods
    void updateDifficultyVariables();
    void initializeMap();
    void resizeWindows();
    void displayMap();
    void displayStats();
    void displayTime();
    void displayLegend();
    void displayStaminaBar();
    bool displayQuitOptions();

    void displayHistory();
    void displayPackages();
    void handleInput(int ch);
    void displayPopupMessage(const std::string& title, const std::vector<std::string>& lines); // Declare popup function

    // Helper functions
    bool invalidPackageDistance(const int& y, const int& x, const int& i);
    bool invalidDestinationDistance(const int& y, const int& x, const int& destinationsPlaced);

    // Gamesaving functions
    void saveGameState();
    void loadGameState();
};

#endif