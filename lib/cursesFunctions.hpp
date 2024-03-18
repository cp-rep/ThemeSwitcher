#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <ncurses.h>
#include <unordered_map>
#include "_cursesWinConsts.hpp"
#include "cursesWindow.hpp"

void initializeCurses();
void initializeWins(std::unordered_map<int, CursesWindow*>& wins);
void defineWins(std::unordered_map<int, CursesWindow*>& wins);
void refreshWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearWins(const std::unordered_map<int, CursesWindow*>& wins);
void updatePromptWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                               const int& numLines,
                               const int& numCols);
void updateHelpWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                               const int& numLines,
                               const int& numCols);
void updateProgramsWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                                 const int& numLines,
                                 const int& numCols);
void updateSavedFilesWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                                   const int& numLines,
                                   const int& numCols);
void updateSavedThemesWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                                    const int& numLines,
                                    const int& numCols);
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& wins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);

#endif // CURSESFUNCTIONS_HPP
