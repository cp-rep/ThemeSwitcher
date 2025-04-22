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
  int mouseLine = -1;
  int mouseCol = -1;
  std::string inputString;
  MEVENT mouse;
  xOffset = 0;
  curs_set(1);

  while(true)
    {
      // reset stored mouse position
      mouseCol = -1;
      mouseLine = -1;

      if(getmouse(&mouse) == OK)
        {
          // check if a mouse click is detected and operate depending click location
          if(mouse.bstate & BUTTON1_PRESSED)
            {
              mouseLine = mouse.y;
              mouseCol = mouse.x;

              // return to previous state if user clicked out of the _SFPROMPTWIN
              if((mouseLine <= wins.at(_SFPROMPTWIN)->getStartY() - 1) ||
                 (mouseLine > wins.at(_SFPROMPTWIN)->getStartY() +
                  wins.at(_SFPROMPTWIN)->getNumLines()  - 1) ||
                 ((mouseCol <= wins.at(_SFPROMPTWIN)->getStartX()  - 1) ||
                  (mouseCol > wins.at(_SFPROMPTWIN)->getStartX() +
                  wins.at(_SFPROMPTWIN)->getNumCols() - 1)))
                {
                  break;
                }
            }
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
          refreshwins(wins);
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
  refreshwins(wins);
  doupdate();
} // end of "enterHWSFAddFileState"
