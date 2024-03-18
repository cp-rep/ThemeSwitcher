#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <ncurses.h>
#include <unordered_map>
#include "_cursesWinConsts.hpp"
#include "cursesWindow.hpp"

void initializeCurses();
void initializeStartingWindows(std::unordered_map<int, CursesWindow*>& wins);
void refreshAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void updatePromptWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                               const int& numLines,
                               const int& numCols);
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& wins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);

#endif // CURSESFUNCTIONS_HPP