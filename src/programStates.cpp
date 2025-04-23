#include "programStates.hpp"

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
                     numCols);

  // get user input, dynamically print it, and store in string object
  bool isInWindow = false;
  int userInput = 0;
  std::string inputString;
  xOffset = 0;
  curs_set(1);

  while(true)
    {
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

      if(isInWindow == false)
        {
          break;
        }

      // get user input
      userInput = getch();
      flushinp();

      // check if user finished entering the file name
      if((userInput == 10) || userInput == KEY_ENTER)
        {
          break;
        }

      else  //output latest received character and store in string
        {
          printUserInput(wins,
                         _USERINPUTWIN,
                         userInput,
                         inputString,
                         startY,
                         xOffset);
          refreshWins(wins);
          doupdate();
        }
      usleep(15000);
    }

  // delete _USERINPUTWIN and return to starting program state
  wins.at(_USERINPUTWIN)->deleteWindow();
  curs_set(0);
  werase(wins.at(_SAVEDFILESWIN)->getWindow());
  printSavedFilesWin(wins,
                     log);
  refreshWins(wins);
  doupdate();
} // end of "enterHWSFAddFileState"
