#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <ncurses.h>
#include <unordered_map>
#include <vector>
#include "_cursesWinConsts.hpp"
#include "cursesWindow.hpp"
#include "log.hpp"
#include "typeConversions.hpp"

// _SAVEDFILESWIN
const std::string sfTitle = "SAVED FILES:";
const std::string sfThemeTitle = "CURRENT THEME:";
const std::string leftArrow = " < ";
const std::string rightArrow = " > ";
const std::string sfLeftArrow = "_LARROWSAVEDFILESWIN";
const std::string sfRightArrow = "_RARROWSAVEDFILESWIN";
const int sfLArrowClicked = 1;
const int sfRArrowClicked = 2;


// _SAVEDTHEMESWIN
const std::string stTitle = "SAVED THEMES:";

void initializeCurses();
void initializeWins(std::unordered_map<int, CursesWindow*>& wins,
                    const int& numSavedFileWins,
                    std::ofstream& log);
void definePromptTitle(std::vector<std::string>& promptStrings);
void definePromptWin(std::unordered_map<int, CursesWindow*>& wins,
                     const int& maxLines,
                     const int& maxCols);
void defineArrowWin(std::unordered_map<int, CursesWindow*>& wins,
                    const int win,
                    const std::string winName,
                    const int startY,
                    const int startX,
                    const int numLines,
                    const int numCols,
                    std::ofstream& log);
void defineSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                         const int& maxLines,
                         const int& maxCols,
                         std::ofstream& log);
void defineSFStringWins(std::unordered_map<int, CursesWindow*>& wins,
                        const std::vector<std::string>& savedFileStrings,
                        std::ofstream& log);
void defineSavedThemesWin(std::unordered_map<int, CursesWindow*>& wins,
                          const int& maxLines,
                          const int& maxCols);
void defineHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                   const int& maxLines,
                   const int& maxCols);
void defineWins(std::unordered_map<int, CursesWindow*>& wins,
                const std::vector<std::string>& savedFileStrings,
                std::ofstream& log);
void printPromptWin(const std::unordered_map<int, CursesWindow*>& wins,
                    const std::vector<std::string>& promptStrings,
                    const int& currLines,
                    const int& currCols,
                    const int& mouseLine,
                    const int& mouseCol,
                    std::ofstream& log);
int printArrowWin(const std::unordered_map<int, CursesWindow*>& wins,
                  const int win,
                  const int& mouseLine,
                  const int& mouseCol,
                  std::string outString,
                  std::ofstream& log);
void printNumberedStrings(std::unordered_map<int, CursesWindow*>& wins,
                          std::unordered_map<int, CursesWindow*>& sfStringWins,
                          const int win,
                          const std::vector<std::string>& fileStrings,
                          const std::vector<std::string>& themeStrings,
                          const int& lineMaxOffset,
                          const int& colMaxOffset,
                          const int& lineMinOffset,
                          const int& colMinOffset,
                          const int& mouseLine,
                          const int& mouseCol,
                          const int& numToPrint,
                          const int& arrowVal,
                          std::ofstream& log,
                          bool& firstRun);
void printSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                        std::unordered_map<int, CursesWindow*>& sfStringWins,
                        const std::vector<std::string>& savedFilesStrings,
                        const std::vector<std::string>& currThemesStrings,
                        const int& mouseLine,
                        const int& mouseCol,
                        std::ofstream& log,
                        bool& firstRun);
void printSavedThemesStrings(const std::unordered_map<int, CursesWindow*>& wins,
                             const std::vector<std::string>& strings,
                             const int& lineMaxOffset,
                             const int& colMaxOffset,
                             const int& lineMinOffset,
                             const int& colMinOffset,
                             const int& mouseLine,
                             const int& mouseCol,
                             std::ofstream& log);
void printSavedThemesWin(const std::unordered_map<int, CursesWindow*>& wins,
                         const std::vector<std::string>& savedThemesStrings,
                         const int& mouseLine,
                         const int& mouseCol,
                         std::ofstream& log);
void refreshWins(const std::unordered_map<int, CursesWindow*>& wins,
                 const std::unordered_map<int, CursesWindow*>& sfStringWins);
void clearWins(const std::unordered_map<int, CursesWindow*>& wins,
               const std::unordered_map<int, CursesWindow*>& sfStringWins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);

#endif // CURSESFUNCTIONS_HPP
