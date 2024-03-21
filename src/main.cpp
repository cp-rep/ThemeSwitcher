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
  int currLines = 0;
  int currCols = 0;
  std::vector<std::string> promptStrings;
  std::vector<std::string> savedFilesStrings;

  // init the text display string vector with THEME SWITCHER for _PROMPTWIN
  definePromptTitle(promptStrings);

  // ## initialize curses and starting windows ##
#if _CURSES
  std::unordered_map<int, CursesWindow*> wins;
  initializeCurses();
  initializeWins(wins);
  defineWins(wins);

  //inititalizeSecondaryWins(secondaryWins);
#endif // _CURSES


  while(true)
    {
#if _CURSES
      // prepare windows for printing
      clearWins(wins);

      // check if the window size has changed
      getmaxyx(stdscr, currLines, currCols);
      if( (currLines != wins.at(_MAINWIN)->getNumLines()) ||
          (currCols != wins.at(_MAINWIN)->getNumCols()) )
        {
          // the window size has changed. update window dimensions
          wins.at(_MAINWIN)->setNumLines(currLines);
          wins.at(_MAINWIN)->setNumCols(currCols);
          defineWins(wins);
        }

      // string printing testing
      savedFilesStrings.clear();
      int lineMinOffset = 3;
      int lineMaxOffset = 3;
      int totalLineOffset = lineMinOffset + lineMaxOffset;
      int minColOffset = 3;
      int maxColOffset = 3;
      int extensionLen = 4;
      int totalColOffset = minColOffset + maxColOffset  + extensionLen;
      initTestStringVector(savedFilesStrings,
                           wins.at(_SAVEDFILESWIN)->getNumLines() - totalLineOffset,
                           wins.at(_SAVEDFILESWIN)->getNumCols() - totalColOffset,
                           log);

      // update window buffer data
      drawBoxes(wins);
      printPromptWin(wins,
                     promptStrings,
                     currCols,
                     currCols,
                     log);
      printSavedFilesWin(wins,
                         savedFilesStrings,
                         log);
      printSavedThemesWin(wins,
                          savedFilesStrings,
                          log);

      // print windows and update the screen
      refreshWins(wins);
      doupdate();
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
    }
  wins.clear();
#endif // _CURSES

  return 0;
} // end of "main"
