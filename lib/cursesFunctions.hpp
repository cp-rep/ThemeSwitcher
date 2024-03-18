#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <ncurses.h>
#include <unordered_map>
#include "_cursesWinConsts.hpp"
#include "cursesWindow.hpp"

void initializeCurses();
void initializeStartingWindows(std::unordered_map<int, CursesWindow*>& mainWins);
void refreshAllMainWins(const std::unordered_map<int, CursesWindow*>& mainWins);
void clearAllMainWins(const std::unordered_map<int, CursesWindow*>& mainWins);
void updatePromptWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                               const int& numLines,
                               const int& numCols);
void updateHelpWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                               const int& numLines,
                               const int& numCols);
void updateProgramsWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                                 const int& numLines,
                                 const int& numCols);
void updateSavedFilesWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                                   const int& numLines,
                                   const int& numCols);
void updateSavedThemesWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                                    const int& numLines,
                                    const int& numCols);
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& mainWins);

#endif // CURSESFUNCTIONS_HPP
