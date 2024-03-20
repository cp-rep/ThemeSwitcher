#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <ncurses.h>
#include <unordered_map>
#include <vector>
#include "_cursesWinConsts.hpp"
#include "cursesWindow.hpp"

void initializeCurses();
void initializeWins(std::unordered_map<int, CursesWindow*>& wins);
void definePromptWin(std::unordered_map<int, CursesWindow*>& wins,
                     const int& maxLines,
                     const int& maxCols);
void defineSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                         const int& maxLines,
                         const int& maxCols);
void defineSavedThemesWin(std::unordered_map<int, CursesWindow*>& wins,
                          const int& maxLines,
                          const int& maxCols);
void defineHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                   const int& maxLines,
                   const int& maxCols);
void defineWins(std::unordered_map<int, CursesWindow*>& wins);
void printPrompt(const std::unordered_map<int, CursesWindow*>& wins,
                 const std::vector<std::string>& prompt,
                 const int& currLines,
                 const int& currCols);
void refreshWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearWins(const std::unordered_map<int, CursesWindow*>& wins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);

#endif // CURSESFUNCTIONS_HPP
