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
const std::string sfLeftArrow = "_LARROWSAVEDFILESWIN";
const std::string sfRightArrow = "_RARROWSAVEDFILESWIN";

// _SAVEDTHEMESWIN
const std::string stTitle = "SAVED THEMES:";

// arrows
const std::string leftArrow = " < ";
const std::string rightArrow = " > ";

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
                        std::vector<CursesWindow*>& sfStringWins,
                        const std::vector<std::string>& savedFileStrings,
                        const int& outputStringPos,
                        std::ofstream& log);
void defineSavedThemesWin(std::unordered_map<int, CursesWindow*>& wins,
                          const int& maxLines,
                          const int& maxCols);
void defineHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                   const int& maxLines,
                   const int& maxCols);
void defineWins(std::unordered_map<int, CursesWindow*>& wins,
                const int& outputStringPos,
                std::ofstream& log);
std::vector<std::string> createSFOutputStrings(std::unordered_map<int, CursesWindow*>& wins,
                                               const std::vector<std::string>& savedFileStrings,
                                               const std::vector<std::string>& currThemes,
                                               std::ofstream& log);
void printPromptWin(const std::unordered_map<int, CursesWindow*>& wins,
                    const std::vector<std::string>& promptStrings,
                    const int& currLines,
                    const int& currCols,
                    const int& mouseLine,
                    const int& mouseCol,
                    std::ofstream& log);
void printNumberedStrings(std::unordered_map<int, CursesWindow*>& wins,
                          const int& lineMaxOffset,
                          const int& colMaxOffset,
                          const int& lineMinOffset,
                          const int& colMinOffset,
                          std::ofstream& log);
void printSFWinArrow(const std::unordered_map<int, CursesWindow*>& wins,
                     const int win,
                     std::string outString,
                     const int colorPair,
                     std::ofstream& log);
void printSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                        const int& mouseLine,
                        const int& mouseCol,
                        std::ofstream& log);
void printSavedFilesStrings(std::unordered_map<int, CursesWindow*>& wins,
                            std::vector<CursesWindow*>& sfStringWins,
                            std::vector<std::string> outputStrings,
                            const int& outputStringPos,
                            const int& currStartWin,
                            const int& highlight,
                            std::ofstream& log);
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
void shiftFilesRight(const std::unordered_map<int, CursesWindow*>& wins,
                     std::vector<CursesWindow*>& sfStringWins,
                     const std::vector<std::string>& outputStrings,
                     int& outputStringPos,
                     std::ofstream& log);
void shiftFilesLeft(const std::unordered_map<int, CursesWindow*>& wins,
                    std::vector<CursesWindow*>& sfStringWins,
                    const std::vector<std::string>& outputStrings,
                    int& outputStringPos,
                    std::ofstream& log);
void checkArrowClick(const std::unordered_map<int, CursesWindow*>& wins,
                     std::vector<CursesWindow*>& sfStringWins,
                     const int win,
                     const std::vector<std::string>& outputStrings,
                     int& outputStringPos,
                     const int& mouseLine,
                     const int& mouseCol,
                     std::string outString,
                     std::ofstream& log);
int checkFileClick(const std::unordered_map<int, CursesWindow*>& wins,
                   const std::vector<std::string>& outputStrings,
                   int& outputStringPos,
                   const int& mouseLine,
                   const int& mouseCol,
                   int highlight,
                   std::ofstream& log);
void refreshWins(const std::unordered_map<int, CursesWindow*>& wins);
void refreshSFStringWins(const std::vector<CursesWindow*>& sfStringWins,
                         std::ofstream& log);
void clearWins(const std::unordered_map<int, CursesWindow*>& wins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins,
               std::ofstream& log);
void drawSFStringBoxes(const std::unordered_map<int, CursesWindow*>& wins,
                       const std::vector<CursesWindow*> & sfStringWins,
                       std::ofstream& log);

#endif // CURSESFUNCTIONS_HPP
