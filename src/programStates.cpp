#include "programStates.hpp"

void enterHWSFAddFileState(std::unordered_map<int, CursesWindow*>& wins,
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
  int numCols = wins.at(_SFPROMPTWIN)->getNumCols() - xOffset - xOffset;
  CursesWindow* userInputWindow = new CursesWindow();

  wins.insert(std::make_pair(_USERINPUTWIN, userInputWindow));
  wins.at(_USERINPUTWIN)->defineWindow(newwin(1,
                                              numCols,
                                              startY,
                                              startX),
                                       "_USERINPUTWIN",
                                       1,
                                       numCols,
                                       startY,
                                       startX);

  // get user input, dynamically print it, and store in string object
  int userInput = 0;
  std::string inputString;
  xOffset = 0;
  curs_set(1);
  while(userInput != 10 && userInput != KEY_ENTER)
    {
      userInput = getch();
      flushinp();

      printUserInput(wins,
                     _USERINPUTWIN,
                     userInput,
                     inputString,
                     startY,
                     xOffset);
      refreshwins(wins);
      doupdate();
      usleep(15000);
    }

  curs_set(0);
} // end of "enterHWSFAddFileState"
