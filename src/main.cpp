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


void printSFStringWins(std::unordered_map<int, CursesWindow*>& wins,
                       const std::vector<std::string>& savedFileStrings,
                       const int& mouseLine,
                       const int& mouseCol,
                       std::ofstream& log);

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
  int input = 0;
  MEVENT mouse;
  int currLines = 0;
  int currCols = 0;
  int mouseLine = -1;
  int mouseCol = -1;
  std::vector<std::string> promptStrings;
  std::vector<std::string> savedFileStrings;
  std::vector<std::string> currThemes;
  std::vector<std::string> savedThemesStrings;

  initTestFilesStringVector(savedFileStrings,
                            50,
                            log);
  initTestCurrThemesStringVector(currThemes,
                                 50,
                                 log);

  // ## initialize curses and starting windows ##
#if _CURSES
  std::unordered_map<int, CursesWindow*> wins;
  std::unordered_map<int, CursesWindow*> sfStringWins;
  initializeCurses();
  initializeWins(wins,
                 savedFileStrings.size(),
                 log);
#endif // _CURSES

  // create testing vectors
  initTestFilesStringVector(savedFileStrings,
                            50,
                            log);
  initTestCurrThemesStringVector(currThemes,
                                 50,
                                 log);
  const int numStrings = 1000;
  const int stringLength = 30;
  initTestStringVector(savedThemesStrings,
                       numStrings,
                       stringLength,
                       log);



  // run once
  {
    // init the text display string vector with THEME SWITCHER for _PROMPTWIN
    definePromptTitle(promptStrings);
    defineWins(wins,
               savedFileStrings,
               log);
    drawBoxes(wins);
    printPromptWin(wins,
                   promptStrings,
                   currLines,
                   currCols,
                   mouseLine,
                   mouseCol,
                   log);
    printSavedFilesWin(wins,
                       mouseLine,
                       mouseCol,
                       log);
    printSavedThemesWin(wins,
                        savedThemesStrings,
                        mouseLine,
                        mouseCol,
                        log);
  }

  while(true)
    {
      // get user input from mouse or keyboard
      input = wgetch(wins.at(_MAINWIN)->getWindow());

      if(input == 'q')
        {
          break;
        }

#if _CURSES
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
      if( (currLines != wins.at(_MAINWIN)->getNumLines()) ||
          (currCols != wins.at(_MAINWIN)->getNumCols()))
        {
          clearWins(wins);

          // the window size has changed. update window dimensions
          wins.at(_MAINWIN)->setNumLines(currLines);
          wins.at(_MAINWIN)->setNumCols(currCols);
          defineWins(wins,
                     savedFileStrings,
                     log);
          drawBoxes(wins);

          // begin printing windows to buffer
          printPromptWin(wins,
                         promptStrings,
                         currLines,
                         currCols,
                         mouseLine,
                         mouseCol,
                         log);
          printSavedFilesWin(wins,
                             mouseLine,
                             mouseCol,
                             log);
          printSavedThemesWin(wins,
                              savedThemesStrings,
                              mouseLine,
                              mouseCol,
                              log);
        }

      printSFStringWins(wins,
                        savedFileStrings,
                        mouseLine,
                        mouseCol,
                        log);

      // if(mouseLine != -1 || mouseCol != -1)
      //   {
      //     // log << "mouseLine: " << mouseLine << std::endl;
      //     // log << "startY: " << wins.at(100)->getStartY() << std::endl;
      //     // log << "added mouse: " << mouseLine + 100 - 13 << std::endl;
      //     std::string fileString = savedFileStrings.at(0);

      //     if(mouseLine == wins.at(mouseLine + 100 - 13)->getStartY())
      //       {
      //         wattron(wins.at(mouseLine + 100 - 13)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
      //         mvwaddstr(wins.at(mouseLine + 100 - 13)->getWindow(),
      //                   0,
      //                   0,
      //                   fileString.c_str());
      //       }
      //   }

      refreshWins(wins);
      doupdate();
      // print windows and update the screen


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





void printSFStringWins(std::unordered_map<int, CursesWindow*>& wins,
                         const std::vector<std::string>& savedFileStrings,
                         const int& mouseLine,
                         const int& mouseCol,
                         std::ofstream& log)

{

}
