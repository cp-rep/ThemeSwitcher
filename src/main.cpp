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
  std::vector<std::string> promptStrings;
  std::vector<std::string> savedFileStrings;
  std::vector<std::string> currThemes;
  std::vector<std::string> savedThemesStrings;
  std::vector<std::string> outputStrings;
  const int numStrings = 5;
  const int stringLength = 30;

  // init the temporary testing string vectors
  initTestFilesStringVector(savedFileStrings,
                            numStrings,
                            log);
  initTestCurrThemesStringVector(currThemes,
                                 numStrings,
                                 log);
  initTestStringVector(savedThemesStrings,
                       numStrings,
                       stringLength,
                       log);

  // ## initialize curses and starting windows ##
#if _CURSES
  std::unordered_map<int, CursesWindow*> wins;
  std::unordered_map<int, CursesWindow*> sfStringWins;
  MEVENT mouse;
  initializeCurses();
  initializeWins(wins,
                 savedFileStrings.size(),
                 log);

  // run once, defining the windows and printing initial starting data
  {
    // init the text display string vector with THEME SWITCHER for _PROMPTWIN
    definePromptTitle(promptStrings);
    defineWins(wins,
               savedFileStrings,
               log);
    outputStrings = createSFOutputStrings(wins,
                                          savedFileStrings,
                                          currThemes,
                                          log);
    drawBoxes(wins,
              log);
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
    printSFStringWins(wins,
                      outputStrings,
                      0,
                      0,
                      log);
    // printSavedThemesWin(wins,
    //                     savedThemesStrings,
    //                     mouseLine,
    //                     mouseCol,
    //                     log);
  }
#endif // _CURSES

  while(true)
    {
#if _CURSES
      // get user input from mouse or keyboard
      input = wgetch(wins.at(_MAINWIN)->getWindow());

      if(input == 'q')
        {
          break;
        }

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
          outputStrings.clear();
          outputStrings = createSFOutputStrings(wins,
                                                savedFileStrings,
                                                currThemes,
                                                log);
          drawBoxes(wins,
                    log);

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
          printSFStringWins(wins,
                      outputStrings,
                      0,
                      0,
                      log);
          // printSavedThemesWin(wins,
          //                     savedThemesStrings,
          //                     mouseLine,
          //                     mouseCol,
          //                     log);
        }

      // while this works it seems like a waste of resources to do this check for
      if(mouseLine != -1 || mouseCol != -1)
        {
          if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
             !outputStrings.empty())
            {
              const int minLineOffset = 3;
              const int maxLineOffset = 3;
              const int minColOffset = 5;
              const int maxColOffset = 4;
              int maxLines = wins.at(_SAVEDFILESWIN)->getNumLines();
              int maxCols = wins.at(_SAVEDFILESWIN)->getNumCols();
              const int startY = wins.at(_SAVEDFILESWIN)->getStartY();
              const int startX = wins.at(_SAVEDFILESWIN)->getStartX();

              // only enter if the mouse click is within a file clicking range of
              // the window
              if((mouseLine >= (startY + minLineOffset &&
                 mouseLine <= startY + maxLines - minColOffset - maxColOffset)) &&
                 ((mouseCol >= startX + minColOffset) &&
                  (mouseCol <= startX + maxCols - maxColOffset)))
                {
                  int offSet = 3;
                  int j = 0;
                  int i = 0;
                  for(i = _SFWINSINDEX, j = 0 ; i < _SFWINSINDEX + _SAVEDFILESWINSTARTY +
                        wins.at(_SAVEDFILESWIN)->getNumLines() - offSet; i++, j++)
                    {
                      // make sure not to test values outside of the maximum printed lines
                      if(j >= outputStrings.size())
                        {
                          break;
                        }

                      // check which window was clicked on and highlight it if clicked
                      if(mouseLine == wins.at(i)->getStartY() &&
                         (mouseCol >= wins.at(i)->getStartX() &&
                          mouseCol <= wins.at(i)->getNumCols() + wins.at(i)->getStartX()))
                        {
                          wattron(wins.at(i)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
                          mvwaddstr(wins.at(i)->getWindow(),
                                    0,
                                    0,
                                    outputStrings.at(j).c_str());
                        }
                      // a window was not clicked so print the default color scheme
                      else
                        {
                          wattron(wins.at(i)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
                          mvwaddstr(wins.at(i)->getWindow(),
                                    0,
                                    0,
                                    outputStrings.at(j).c_str());
                        }
                    }
                }
            }
        }

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
