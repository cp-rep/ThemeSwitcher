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
                     numCols,
                     log);

  // get user input, dynamically print it, and store in string object
  bool isInWindow = false;
  int userInput = 0;
  std::string outputString;
  int stringIndex = 0;
  int stringLen = 0;
  int cursorPosition = 0;
  xOffset = 0;
  curs_set(1);
  bool exitLoop = false;
  int currLines;
  int currCols;

  std::string tempOutputString = "";
  std::string dots = "...";
  int totalStringLength = 0;

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

      log << "before outputstring.length(): " << outputString.length() << std::endl;

      // resize output string to fit window if it's greater than num cols
      if(outputString.length() > numCols - 1)
        {
          log << "outputstring.length(): " << outputString.length() << std::endl;
          log << "numCols: " << numCols << std::endl;

          tempOutputString.clear();
          int difference = outputString.length() - numCols;
          log << "difference: " << difference << std::endl;
          tempOutputString.append(dots);

          for(int i = difference + dots.length() + 1; i < outputString.length(); i++)
            {
              char c = outputString.at(i);
              tempOutputString.push_back(c);
            }
        }
      else
        {
          tempOutputString = outputString;
        }


      // // ## basic endless scroll
      // // resize output string to fit window if it's greater than num cols
      // if(outputString.length() > numCols - 1)
      //   {
      //     log << "outputstring.length(): " << outputString.length() << std::endl;
      //     log << "numCols: " << numCols << std::endl;

      //     tempOutputString.clear();
      //     int difference = outputString.length() - numCols;
      //     log << "difference: " << difference << std::endl;
      //     tempOutputString.append(dots);

      //     for(int i = difference + dots.length() + 1; i < outputString.length(); i++)
      //       {
      //         char c = outputString.at(i);
      //         tempOutputString.push_back(c);
      //       }
      //   }
      // else
      //   {
      //     tempOutputString = outputString;
      //   }

      switch(userInput)
        {
        case '\n':
          exitLoop = true;
          break;
        case KEY_ENTER:
          exitLoop = true;
          break;
        case KEY_LEFT: // shift the cursor left on the output string
          stringLen = outputString.length() + stringIndex - 1;
          if(stringLen >= 0)
            {
              // update the offsets of the cursor and index and move the cursor
              stringIndex--;
              cursorPosition--;
              wmove(wins.at(_USERINPUTWIN)->getWindow(), 0, cursorPosition);
            }
          break;
        case KEY_RIGHT: // shift the cursor right on the outputstring
          stringLen = outputString.length() + stringIndex + 1;
          if((stringLen < outputString.length() + 1) &&
             outputString.length() < numCols)
            {
              // update the offsets of the cursor and index and move the cursor
              stringIndex++;
              cursorPosition++;
              wmove(wins.at(_USERINPUTWIN)->getWindow(), 0, cursorPosition);
            }
          break;
        default:
          break;
        }

      if(exitLoop == true)
        {
          break;
        }

      printUserInput(wins,
                     _USERINPUTWIN,
                     userInput,
                     outputString,
                     tempOutputString,
                     stringIndex,
                     startY,
                     xOffset,
                     log);
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
