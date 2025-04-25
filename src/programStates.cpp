#include "programStates.hpp"
#include <cmath>

void enterHWSFAddFileState(std::unordered_map<int, CursesWindow*>& wins,
                           MEVENT& mouse,
                           int& mouseLine,
                           int& mouseCol,
                           std::ofstream& log)
{
  flashButton(wins,
              _HWSFADDFILE,
              _hwSFAddFile,
              _BLACK_TEXT,
              _WHITE_TEXT,
              log);
  defineSFPromptWin(wins,
                    log);
  printPrompt(wins,
              _SFPROMPTWIN,
              _hwSFAddFileWin,
              log);

  // create user input window
  int yOffset = 2;
  int xOffset = 2;
  int startY = wins.at(_SFPROMPTWIN)->getStartY() + yOffset;
  int startX = wins.at(_SFPROMPTWIN)->getStartX() + xOffset;
  int numLines = 1;
  int numCols = wins.at(_SFPROMPTWIN)->getNumCols() - xOffset - xOffset;
  createUserInputWin(wins,
                     startY,
                     startX,
                     numLines,
                     numCols,
                     log);

  // get user input, dynamically print it, and store in string object
  bool isInWindow = false;
  int userInput = 0;
  std::string fullPath = "> ";
  int stringIndex = 0;
  int stringLen = 0;
  int cursorPosition = 2;
  xOffset = 0;
  curs_set(1);
  bool exitLoop = false;
  int currLines;
  int currCols;
  std::string outputString = "> ";
  int totalStringLength = 0;
  int scrollCount = 0;
  int actualCurrIndex = 2;

  while(true)
    {
      getmaxyx(stdscr, currLines, currCols);

      // check for window resize event
      if((currLines != wins.at(_MAINWIN)->getNumLines()) ||
         (currCols != wins.at(_MAINWIN)->getNumCols()))
        {
          break;
        }

      isInWindow = checkWindowClick(wins,
                                    _SFPROMPTWIN,
                                    mouse,
                                    mouseLine,
                                    mouseCol,
                                    1,
                                    1,
                                    1,
                                    1,
                                    log);

      // exit state if user clicked outside of _SFPROMTWIN
      if(isInWindow == false)
        {
          break;
        }

      // get user input
      userInput = getch();
      flushinp();
      exitLoop = printUserInput(wins,
                                userInput,
                                fullPath,
                                outputString,
                                stringIndex,
                                startY,
                                cursorPosition,
                                stringLen,
                                actualCurrIndex,
                                log);

      if(exitLoop == true)
        {
          break;
        }

      wrefresh(wins.at(_USERINPUTWIN)->getWindow());
      doupdate();
      usleep(15000);
    }

  // delete _USERINPUTWIN and return to starting program state
  wins.at(_USERINPUTWIN)->deleteWindow();
  curs_set(0);
  printSavedFilesWin(wins,
                     log);
  refreshWins(wins);
  doupdate();
} // end of "enterHWSFAddFileState"
