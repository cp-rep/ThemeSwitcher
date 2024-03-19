#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <ncurses.h>
#include <unordered_map>
#include "_cursesWinConsts.hpp"
#include "cursesWindow.hpp"

void initializeCurses();
void initializeWins(std::unordered_map<int, CursesWindow*>& wins);
void definePromptWin(std::unordered_map<int, CursesWindow*>& wins,
                     const int& maxLines, const int& maxCols);
void defineSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                         const int& maxLines,
                         const int& maxCols);
void defineWins(std::unordered_map<int, CursesWindow*>& wins);
void updateWinDimensions(std::unordered_map<int, CursesWindow*>& wins);
void refreshWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearWins(const std::unordered_map<int, CursesWindow*>& wins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);

#endif // CURSESFUNCTIONS_HPP
