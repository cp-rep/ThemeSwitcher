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
  NcursesTextEditor* textWin = new NcursesTextEditor(newwin(numLines,
                                                            numCols,
                                                            startY,
                                                            startX),
                                                     "_USERINPUTWIN",
                                                     numLines,
                                                     numCols,
                                                     startY,
                                                     startX);



  // get user input, dynamically print it, and store in string object
  bool isInWindow = false;
  int userInput = 0;
  std::string prefixString = "> ";
  std::string fullPath = "";
  std::string outputString = "";
  int cursorPosition = 0;
  bool exitLoop = false;
  int currLines;
  int currCols;
  int actualCurrIndex = 0;

  textWin->defineTextData(prefixString,
                          fullPath,
                          outputString,
                          actualCurrIndex,
                          cursorPosition);

  curs_set(1);
  while(true)
    {
      getmaxyx(stdscr, currLines, currCols);

      // check for window resize event
      if((currLines != wins.at(_MAINWIN)->getNumLines()) ||
         (currCols != wins.at(_MAINWIN)->getNumCols()))
        {
          break;
        }

      // check if user clicked outside the _SFPROMPTWIN window parameters
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
      exitLoop = textWin->editText();

      // update the window buffer
      werase(textWin->getWindow());
      std::string temp = textWin->getOutString();
      mvwaddstr(textWin->getWindow(),
                0,
                0,
                textWin->getOutString().c_str());
      wmove(textWin->getWindow(), 0, textWin->getIndexOutstring());

      if(exitLoop == true)
        {
          break;
        }

      // print the window buffer
      wrefresh(textWin->getWindow());
      doupdate();
      usleep(15000);
    }

  // delete _USERINPUTWIN and return to starting program state
  textWin->deleteWindow();
  curs_set(0);
  printSavedFilesWin(wins,
                     log);
  refreshWins(wins);
  doupdate();
} // end of "enterHWSFAddFileState"
