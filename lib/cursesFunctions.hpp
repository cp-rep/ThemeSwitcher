#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <ncurses.h>
#include <unordered_map>
#include <vector>
#include "_cursesWinConsts.hpp"
#include "cursesWindow.hpp"
#include "log.hpp"
#include "typeConversions.hpp"

// helpwin
const std::string hwSFAddFile = "     Add File      ";
const std::string hwSFEditFilePath = "   Edit File Path  ";
const std::string hwSFViewFilePath = "   View File Path  ";
const std::string hwSFRemoveFile = "    Remove File    ";
const std::string hwSFAddTheme = "  Add File Theme   ";
const std::string hwSFEditTheme = "  Edit File Theme  ";
const std::string hwSFRemoveTheme = " Remove File Theme ";
const std::string hwSTAddTheme = "     Add Theme     ";
const std::string hwSTARemoveTheme = "     Add Theme     ";
const std::string hwSTRemoveTheme = "   Remove Theme    ";
const std::string hwSTEditTheme =   "     Edit Theme    ";
const std::string hwSTViewTheme = "    View Theme     ";

// _SAVEDFILESWIN
const std::string sfTitle = "SAVED FILES:";
const std::string sfThemeTitle = "CURRENT THEME:";
const std::string sfLeftArrow = "_LARROWSAVEDFILESWIN";
const std::string sfRightArrow = "_RARROWSAVEDFILESWIN";

// _SAVEDTHEMESWIN
const std::string stTitle = "SAVED THEMES:";
const std::string stLeftArrow = "_LARROWSAVEDTHEMESWIN";
const std::string stRightArrow = "_RARROWSAVEDTHEMESWIN";

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
                    const int mainWin,
                    const int arrowWin,
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
void defineSFStringWins(const std::unordered_map<int, CursesWindow*>& wins,
                        std::vector<CursesWindow*>& sfStringWins,
                        const std::vector<std::string>& savedFileStrings,
                        const int& sfStringPos,
                        std::ofstream& log);
void defineSTStringWins(const std::unordered_map<int, CursesWindow*>& wins,
                        std::vector<CursesWindow*>& stStringWins,
                        const std::vector<std::string>& savedSTStrings,
                        const int& stStringPos,
                        std::ofstream& log);
void defineSavedThemesWin(std::unordered_map<int, CursesWindow*>& wins,
                          const int& maxLines,
                          const int& maxCols,
                          std::ofstream& log);
void defineHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                   const int& maxLines,
                   const int& maxCols);
void defineWins(std::unordered_map<int, CursesWindow*>& wins,
                std::ofstream& log);
std::vector<std::string> createSFOutputStrings(const std::unordered_map<int, CursesWindow*>& wins,
                                               std::vector<CursesWindow*>& sfStringWins,
                                               const std::vector<std::string>& savedFileStrings,
                                               const std::vector<std::string>& currThemes,
                                               std::ofstream& log);
std::vector<std::string> createSTOutputStrings(const std::unordered_map<int, CursesWindow*>& wins,
                                               const std::vector<std::string>& stStrings,
                                               const int& stStringPos,
                                               std::ofstream& log);
void printPromptWin(const std::unordered_map<int, CursesWindow*>& wins,
                    const std::vector<std::string>& promptStrings,
                    const int& currLines,
                    const int& currCols,
                    const int& mouseLine,
                    const int& mouseCol,
                    std::ofstream& log);
void printHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                  std::ofstream& log);
void printNumberedStrings(std::unordered_map<int, CursesWindow*>& wins,
                          std::ofstream& log);
void printArrowWin(const std::unordered_map<int, CursesWindow*>& wins,
                   const int win,
                   std::string outString,
                   const int colorPair,
                   std::ofstream& log);
void printSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                        std::ofstream& log);
void printSavedFilesStrings(std::unordered_map<int, CursesWindow*>& wins,
                            std::vector<CursesWindow*>& sfStringWins,
                            std::vector<std::string> outputStrings,
                            const int& sfStringPos,
                            const int& currStartWin,
                            const int& highlightWinNum,
                            std::ofstream& log);
void printSavedThemesStrings(const std::unordered_map<int, CursesWindow*>& wins,
                             std::vector<CursesWindow*>& stStringWins,
                             const std::vector<std::string>& stStrings,
                             const int& stStringPos,
                             const int& stHighlightNum,
                             std::ofstream& log);
void printSavedThemesWin(const std::unordered_map<int, CursesWindow*>& wins,
                         std::ofstream& log);
void shiftSFRight(const std::unordered_map<int, CursesWindow*>& wins,
                  std::vector<CursesWindow*>& sfStringWins,
                  const std::vector<std::string>& outputStrings,
                  int& sfStringPos,
                  std::ofstream& log);
void shiftSFLeft(const std::unordered_map<int, CursesWindow*>& wins,
                 std::vector<CursesWindow*>& sfStringWins,
                 const std::vector<std::string>& outputStrings,
                 int& sfStringPos,
                 std::ofstream& log);
void shiftSTLeft(std::unordered_map<int, CursesWindow*>& wins,
                 std::vector<CursesWindow*>& stStringWins,
                 const std::vector<std::string>& outputStrings,
                 int& stStringPos,
                 std::ofstream& log);
void shiftSTRight(std::unordered_map<int, CursesWindow*>& wins,
                  std::vector<CursesWindow*>& stStringWins,
                  const std::vector<std::string>& outputStrings,
                  int& outputStringPos,
                  std::ofstream& log);
void checkArrowClick(std::unordered_map<int, CursesWindow*>& wins,
                     std::vector<CursesWindow*>& stringWins,
                     const int mainWin,
                     const int arrowWin,
                     const std::vector<std::string>& outputStrings,
                     int& sfStringPos,
                     const int& mouseLine,
                     const int& mouseCol,
                     std::string outString,
                     std::ofstream& log);
void checkSFClick(const std::unordered_map<int, CursesWindow*>& wins,
                  const std::vector<std::string>& outputStrings,
                  const int& sfStringPos,
                  const int& mouseLine,
                  const int& mouseCol,
                  int& highlightWinNum,
                  std::ofstream& log);
void checkSTClick(const std::unordered_map<int, CursesWindow*>& wins,
                  const std::vector<CursesWindow*>& stStringWins,
                  const int& mouseLine,
                  const int& mouseCol,
                  int& highlightWinNum,
                  std::ofstream& log);
void refreshWins(const std::unordered_map<int, CursesWindow*>& wins);
void refreshSFStringWins(const std::vector<CursesWindow*>& sfStringWins,
                         std::ofstream& log);
void refreshSTStringWins(const std::vector<CursesWindow*>& stStringWins,
                         std::ofstream& log);
void clearWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearSFStringWins(const std::vector<CursesWindow*>& sfStringWins);
void clearSTStringWins(const std::vector<CursesWindow*>& stStringWins);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins,
               std::ofstream& log);
void drawSFStringBoxes(const std::unordered_map<int, CursesWindow*>& wins,
                       const std::vector<CursesWindow*> & sfStringWins,
                       std::ofstream& log);
void drawSTStringBoxes(const std::unordered_map<int, CursesWindow*>& wins,
                       const std::vector<CursesWindow*> & stStringWins,
                       std::ofstream& log);

#endif // CURSESFUNCTIONS_HPP
