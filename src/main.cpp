// ============================================================================
// File: main.c
// Author: https://github.com/cp-rep
//
// Disclaimer:
//  You may use and freely distribute my code as long as you leave the original
//  author provided above in any works that use or heavily borrow from it.
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
#include <ncurses.h>
#include <unistd.h>
#include <unordered_map>
#include "_cursesWinConsts.hpp"
#include "cursesFunctions.hpp"
#include "cursesWindow.hpp"
#include "log.hpp"

#define _DEBUG 0
#define _LOG 1
#define _CURSES 1



// ==== main ==================================================================
//
// ============================================================================
int main()
{
#if _LOG
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

#endif // _LOG

  // local variables
  std::unordered_map<int, CursesWindow*> wins;

  // ## initialize curses and starting windows ##
#if _CURSES
  initializeCurses();
  initializeStartingWindows(wins);
#endif // _CURSES

  // ## define the window dimensions ##
  // local window variables
  int numLines = 0;
  int numCols = 0;
  int startY = 0;
  int startX = 0;

  // _MAINWIN
  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->defineWindow(stdscr,
                                  "_MAINWIN",
                                  numLines,
                                  numCols,
                                  startY,
                                  startX);
  // _HELPWIN
  numLines = (wins.at(_MAINWIN)->getNumLines() / 2) - 3;
  numCols = 60;
  startY = 2;
  startX =  wins.at(_MAINWIN)->getNumCols() - numCols - 3;
  wins.at(_HELPWIN)->defineWindow(newwin(numLines,
                                         numCols,
                                         startY,
                                         startX),
                                  "_HELPWIN",
                                  numLines,
                                  numCols,
                                  startY,
                                  startX);
  // _PROGRAMSWIN
  numLines = (wins.at(_MAINWIN)->getNumLines() / 2) - 2;
  numCols = 60;
  startY = wins.at(_HELPWIN)->getNumLines() + 3;
  startX =  wins.at(_MAINWIN)->getNumCols() - numCols - 3;
  wins.at(_PROGRAMSWIN)->defineWindow(newwin(numLines,
                                             numCols,
                                             startY,
                                             startX),
                                      "_PROGRAMSWIN",
                                      numLines,
                                      numCols,
                                      startY,
                                      startX);
  // _PROMPTWIN
  numLines = 6;
  numCols = wins.at(_MAINWIN)->getNumCols() -wins.at(_HELPWIN)->getNumCols() - 8;
  startY = 2;
  startX = 3;
  wins.at(_PROMPTWIN)->defineWindow(newwin(numLines,
                                        numCols,
                                        startY,
                                        startX),
                                    "_PROMPTWIN",
                                    numLines,
                                    numCols,
                                    startY,
                                    startX);
  // _SAVEDFILESWIN
  numLines = ((wins.at(_MAINWIN)->getNumLines() - wins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  numCols = wins.at(_MAINWIN)->getNumCols() -wins.at(_HELPWIN)->getNumCols() - 8;
  startY = wins.at(_PROMPTWIN)->getStartY() + wins.at(_PROMPTWIN)->getNumLines() + 1;
  startX = 3;
  wins.at(_SAVEDFILESWIN)->defineWindow(newwin(numLines,
                                               numCols,
                                               startY,
                                               startX),
                                        "_SAVEDFILESWIN",
                                        numLines,
                                        numCols,
                                        startY,
                                        startX);
  // _SAVEDTHEMESWIN
  numLines = ((wins.at(_MAINWIN)->getNumLines() - wins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  numCols = wins.at(_MAINWIN)->getNumCols() -wins.at(_HELPWIN)->getNumCols() - 8;
  startY = wins.at(_SAVEDFILESWIN)->getStartY() + wins.at(_SAVEDFILESWIN)->getNumLines() + 1;
  startX = 3;
  wins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(numLines,
                                                numCols,
                                                startY,
                                                startX),
                                         "_SAVEDTHEMESWIN",
                                         numLines,
                                         numCols,
                                         startY,
                                         startX);

#if _CURSES
  drawBoxes(wins);
#endif

  // refresh windows and update the screen
  refreshAllWins(wins);
  doupdate();

  while(true)
    {
      usleep(15000);
    }

  // clean up
  endwin();

  for(std::unordered_map<int, CursesWindow*>::iterator it = wins.begin();
      it != wins.end(); it++)
    {
      it->second->deleteWindow();
    }
  wins.clear();

  return 0;
} // end of "main"
