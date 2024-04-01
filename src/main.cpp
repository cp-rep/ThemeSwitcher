// ============================================================================
// File: main.c
// Author: https://github.com/cp-rep
//
// Disclaimer:
//  You may use and freely distribute my code from this project as long as you
//  leave the original author provided above in any works that use or borrow
//  from it.
//
//  Using this program is at your own discretion and trust in the software.
//  Using it means take you responsibility for any and all events that may
//  happen from its use.
//
// Program Description:
//  Changes the color theme for Linux Window Managers and/or Terminal
//  Emulators.  A GUI is provided by the Ncurses library.
//
// ============================================================================
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include "_cursesWinConsts.hpp"
#include "cursesFunctions.hpp"
#include "cursesWindow.hpp"
#include "log.hpp"
#include "testingInterface.hpp"

#define _DEBUG 0
#define _CURSES 1



// ==== main ==================================================================
//
// ============================================================================
int main()
{
  // ## CREATE LOGGING SYSTEM
  time_t rawtime;
  struct tm* timeinfo;
  Log logFile("./log/", "log", 1, ".log");
  std::ofstream log;

  //  get time info
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // open log file
  while(true)
    {
      std::ifstream inFile(logFile.getFullPath(), std::ifstream::in);

      // check if log exists
      if(inFile.is_open())
        {
          // increment the log number and close the open file
          logFile.incrementFileName();
          inFile.close();
        }
      // log doesn't exist, create the new log file
      else
        {
          log.open(logFile.getFullPath());
          break;
        }
    }

  // check if the file remained open, exit with error otherwise
  if(!log.is_open())
    {
      std::cerr << "Error creating log file." << std::endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      // output start of log session
      log << "LOG Started" << std::endl;
      log << "Time and Date: " << asctime(timeinfo) << std::endl;
    }

  // local variables
  int input = 0;
  int currLines = 0;
  int currCols = 0;
  int mouseLine = -1;
  int mouseCol = -1;
  int arrowClickVal = 0;
  int sfHighlightNum = -1;
  int stHighlightNum = -1;
  int currStartWin = 0;
  std::vector<std::string> promptStrings;
  // saved file variables
  std::vector<std::string> sfStrings;
  std::vector<std::string> sfThemes;
  std::vector<std::string> sfOutput;
  int sfStringPos = 0;
  // saved theme variables
  std::vector<std::string> stStrings;
  std::vector<std::string> stOutput;
  int stStringPos = 0;

  // init the temporary testing string vectors
  const int numStrings = 200;

  initTestFilesStringVector(sfStrings,
                            numStrings,
                            log);
  initTestCurrThemesStringVector(sfThemes,
                                 numStrings,
                                 log);
  initSTStrings(stStrings,
                numStrings,
                _STWINMAXCOLS,
                log);

  // ## initialize curses and starting windows ##
#if _CURSES
  std::unordered_map<int, CursesWindow*> wins;
  std::vector<CursesWindow*> sfStringWins;
  std::vector<CursesWindow*> stStringWins;
  MEVENT mouse;

  initializeCurses();
  initializeWins(wins,
                 sfStrings.size(),
                 log);
  stOutput = createSTOutputStrings(wins,
                                   stStrings,
                                   stStringPos,
                                   log);

  // run once, defining the windows and printing initial starting data
  {
    definePromptTitle(promptStrings);
    defineWins(wins,
               log);
    getmaxyx(wins.at(_MAINWIN)->getWindow(), currLines, currCols);
    defineSFStringWins(wins,
                       sfStringWins,
                       stOutput,
                       sfStringPos,
                       log);
    sfOutput = createSFOutputStrings(wins,
                                     sfStringWins,
                                     sfStrings,
                                     sfThemes,
                                     log);
    defineSTStringWins(wins,
                       stStringWins,
                       stOutput,
                       stStringPos,
                       log);
    printPromptWin(wins,
                   promptStrings,
                   currLines,
                   currCols,
                   mouseLine,
                   mouseCol,
                   log);
    printHelpWin(wins,
                 log);
    printSavedFilesWin(wins,
                       log);
    printSavedFilesStrings(wins,
                           sfStringWins,
                           sfOutput,
                           sfStringPos,
                           currStartWin,
                           sfHighlightNum,
                           log);
    printSavedThemesWin(wins,
                        log);
    printSavedThemesStrings(wins,
                            stStringWins,
                            stOutput,
                            stStringPos,
                            stHighlightNum,
                            log);
    refreshWins(wins);
    refreshSFStringWins(sfStringWins,
                        log);
    refreshSTStringWins(stStringWins,
                        log);
    doupdate();
  }
#endif // _CURSES

  while(true)
    {
#if _CURSES
      // get user input from mouse or keyboard
      input = wgetch(wins.at(_MAINWIN)->getWindow());
      input = toupper(input);

      if(input == 'Q')
        {
          break;
        }

      sfHighlightNum = -1;
      stHighlightNum = -1;
      mouseLine = -1;
      mouseCol = -1;

      if(getmouse(&mouse) == OK)
        {
          if(mouse.bstate & BUTTON1_PRESSED)
            {
              mouseLine = mouse.y;
              mouseCol = mouse.x;
            }
        }

      // check if the window size has changed
      getmaxyx(stdscr, currLines, currCols);

      // if screen size changed, reprint a default screen with current
      // data positions
      if((currLines != wins.at(_MAINWIN)->getNumLines()) ||
          (currCols != wins.at(_MAINWIN)->getNumCols()))
        {
          arrowClickVal = 0;
          clearWins(wins);
          clearSFStringWins(sfStringWins);
          clearSFStringWins(stStringWins);

          // the window size has changed. update window dimensions
          wins.at(_MAINWIN)->setNumLines(currLines);
          wins.at(_MAINWIN)->setNumCols(currCols);

          // redefine windows
          defineWins(wins,
                     log);
          defineSFStringWins(wins,
                             sfStringWins,
                             sfStrings,
                             sfStringPos,
                             log);
          defineSTStringWins(wins,
                             stStringWins,
                             stOutput,
                             stStringPos,
                             log);
          sfOutput = createSFOutputStrings(wins,
                                           sfStringWins,
                                           sfStrings,
                                           sfThemes,
                                           log);
          // print the window data
          printPromptWin(wins,
                         promptStrings,
                         currLines,
                         currCols,
                         mouseLine,
                         mouseCol,
                         log);
          printHelpWin(wins,
                       log);
          printSavedFilesWin(wins,
                             log);
          printSavedFilesStrings(wins,
                                 sfStringWins,
                                 sfOutput,
                                 sfStringPos,
                                 currStartWin,
                                 sfHighlightNum,
                                 log);
          printSavedThemesWin(wins,
                              log);
          printSavedThemesStrings(wins,
                                  stStringWins,
                                  stOutput,
                                  stStringPos,
                                  stHighlightNum,
                                  log);
          refreshWins(wins);
          refreshSFStringWins(sfStringWins,
                              log);
          refreshSTStringWins(stStringWins,
                              log);
          doupdate();
        }

      // check for a mouse click and operate on the line/col values
      if(mouseLine != -1 || mouseCol != -1)
        {
          // check _SAVEDFILESWIN arrows
          checkArrowClick(wins,
                          sfStringWins,
                          _SAVEDFILESWIN,
                          _LARROWSAVEDFILESWIN,
                          sfOutput,
                          sfStringPos,
                          mouseLine,
                          mouseCol,
                          leftArrow,
                          log);
          checkArrowClick(wins,
                          sfStringWins,
                          _SAVEDFILESWIN,
                          _RARROWSAVEDFILESWIN,
                          sfOutput,
                          sfStringPos,
                          mouseLine,
                          mouseCol,
                          rightArrow,
                          log);
          // check _SAVEDTHEMESWIN arrows
          checkArrowClick(wins,
                          stStringWins,
                          _SAVEDTHEMESWIN,
                          _LARROWSAVEDTHEMESWIN,
                          stOutput,
                          stStringPos,
                          mouseLine,
                          mouseCol,
                          leftArrow,
                          log);
          checkArrowClick(wins,
                          stStringWins,
                          _SAVEDTHEMESWIN,
                          _RARROWSAVEDTHEMESWIN,
                          stOutput,
                          stStringPos,
                          mouseLine,
                          mouseCol,
                          rightArrow,
                          log);
          checkSFClick(wins,
                       sfOutput,
                       sfStringPos,
                       mouseLine,
                       mouseCol,
                       sfHighlightNum,
                       log);
          printHelpWin(wins,
                       log);
          printSavedFilesStrings(wins,
                                 sfStringWins,
                                 sfOutput,
                                 sfStringPos,
                                 currStartWin,
                                 sfHighlightNum,
                                 log);
          checkSTClick(wins,
                       stStringWins,
                       mouseLine,
                       mouseCol,
                       stHighlightNum,
                       log);
          printSavedThemesStrings(wins,
                                  stStringWins,
                                  stOutput,
                                  stStringPos,
                                  stHighlightNum,
                                  log);
          refreshWins(wins);
          refreshSFStringWins(sfStringWins,
                              log);
          refreshSTStringWins(stStringWins,
                              log);
          doupdate();
        }
#endif // _CURSES

      usleep(15000);
    }

  // clean up
#if _CURSES
  endwin();
  for(std::unordered_map<int, CursesWindow*>::iterator it = wins.begin();
      it != wins.end(); it++)
    {
      it->second->deleteWindow();
      it->second->setWindow(nullptr);
      delete it->second;
    }

  wins.clear();

  for(int i = 0; i < sfStringWins.size(); i++)
    {
      if(sfStringWins.at(i)->getWindow() != nullptr)
        {
          sfStringWins.at(i)->deleteWindow();
          sfStringWins.at(i)->setWindow(nullptr);
          delete sfStringWins.at(i);
        }
    }

  sfStringWins.clear();

  for(int i = 0; i < stStringWins.size(); i++)
    {
      if(stStringWins.at(i)->getWindow() != nullptr)
        {
          stStringWins.at(i)->deleteWindow();
          stStringWins.at(i)->setWindow(nullptr);
          delete stStringWins.at(i);
        }
    }
  endwin();
#endif // _CURSES

  stStringWins.clear();
  promptStrings;
  sfStrings.clear();
  sfThemes.clear();
  stStrings.clear();
  sfOutput.clear();

  return 0;
} // end of "main"
