/*
  File:
   cursesFunctions.cpp

  Description:
   Function implementations for the cursesFunctions.hpp header file.
*/
#include <algorithm>
#include <vector>
#include "cursesFunctions.hpp"
#include <unistd.h>


/*
  Function:
   initializeCurses

  Description:
   Initializes the curses stdscr and curses datastructures.

  Input/Output:
   NONE

  Input:
   NONE

  Output:
   NONE
*/
void initializeCurses()
{
  initscr();

  if(has_colors())
    {
      start_color();
      init_pair(_WHITE_TEXT, COLOR_WHITE, COLOR_BLACK);
      init_pair(_BLACK_TEXT, COLOR_BLACK, COLOR_WHITE);
    }

  curs_set(0);
  timeout(0);
  noecho();
  cbreak();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);

} // end of "initializeCurses"



/*
  Function:
   initializeWins

  Description:
   This function creates and initializes all the necessary startup windows via
   dynamic allocation and stores them in an unordered_map for later use.

  Input/Output:
   wins                     - A reference to an unordered map <int, CursesWindow*>
                              object type that will be used to store each
                              CursesWindow object initialized in this function.  The
                              keys are from _cursesWinConsts.hpp and match the
                              corresponding CursesWindow objects they are pointing
                              to.
   NONE

  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void initializeWins(std::unordered_map<int, CursesWindow*>& wins,
                    const int& numSavedFileWins,
                    std::ofstream& log)
{
  for(int i = _MAINWIN; i <= _RARROWSAVEDFILESWIN; i++)
    {
      CursesWindow* newWindow = new CursesWindow();
      wins.insert(std::make_pair(i, newWindow));
    }

  for(int i = _SFWINSINDEX; i < numSavedFileWins + _SFWINSINDEX; i++)
    {
      CursesWindow* newWindow = new CursesWindow();
      wins.insert(std::make_pair(i, newWindow));
    }
} // end of "initializeWins"



/*
  Function:
   definePromptTitle

  Description:
   Defines the graphical display program title for _PROMPTWIN.

  Input/Output:
   promptStrings            -

  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void definePromptTitle(std::vector<std::string>& promptStrings)
{
  std::string line0;
  std::string line1;
  std::string line2;
  std::string line3;
  std::string line4;

  line0 = { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_',
            '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_',
            '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', ' ', ' ',
            '_', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_',
            '_' };

  line1 = { '\\', '_', '_', ' ', ' ', ' ', ' ', '_', '_', '_', '/', '|', ' ',
            ' ', '|', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', ' ', ' ',
            ' ', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_',
            ' ', ' ', ' ', ' ', '/', ' ', ' ', ' ', '_', '_', '_', '_', '_',
            '/', '_', ' ', ' ', '_', ' ', ' ', '_', '|', '_', '_', '|', '/',
            ' ', ' ', '|', '_', ' ', ' ', '_', '_', '_', '_', ' ', '|', ' ',
            ' ', '|', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_',
            '_', '_', '_', '_', '_' };

  line2 = { ' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ',
            ' ', '|', ' ', ' ', '\\', '_', '/', ' ', '_', '_', ' ', '\\', ' ',
            '/', ' ', ' ', ' ', ' ', ' ', '\\', '_', '/', ' ', '_', '_', ' ',
            '\\', ' ', ' ', ' ', '\\', '_', '_', '_', '_', '_', ' ', ' ', '\\',
            '\\', ' ', '\\', '/', ' ', '\\', '/', ' ', '/', ' ', ' ', '\\', ' ',
            ' ', ' ', '_', '_', '\\', '/', ' ', '_', '_', '_', '\\', '|', ' ',
            ' ', '|', ' ', ' ', '\\', '_', '/', ' ', '_', '_', ' ', '\\', '_',
            ' ', ' ', '_', '_', ' ', '\\' };

  line3 = { ' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ',
            ' ', ' ', 'Y', ' ', ' ', '\\', ' ', ' ', '_', '_', '_', '/', '|',
            ' ', ' ', 'Y', ' ', 'Y', ' ', ' ', '\\', ' ', ' ', '_', '_', '_',
            '/', ' ', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            '\\', '\\', ' ', ' ', ' ', ' ', ' ', '/', '|', ' ', ' ', '|', '|',
            ' ', ' ', '|', ' ', '\\', ' ', ' ', '\\', '_', '_', '_', '|', ' ',
            ' ', ' ', 'Y', ' ', ' ', '\\', ' ', ' ', '_', '_', '_', '/', '|',
            ' ', ' ', '|', ' ', '\\', '/'};

  line4 = { ' ', ' ', '|', '_', '_', '_', '_', '|', ' ', ' ', ' ', '|', '_',
            '_', '_', '|', '_', '_', '/', '\\', '_', '_', '_', '_', '\\', '|',
            '_', '_', '|', '_', '|', '_', '_', '/', '\\', '_', '_', '_', '_',
            '\\', ' ', ' ', '/', '_', '_', '_', '_', '_', '_', '_', '_', '_',
            '/', ' ', '\\', '/', '\\', '_', '/', ' ', '|', '_', '_', '|', '|',
            '_', '_', '|', ' ', ' ', '\\', '_', '_', '_', '_', '_', '|', '_',
            '_', '_', '|', '_', '_', '/', '\\', '_', '_', '_', '_', '\\', '|',
            '_', '_', '|' };

  promptStrings.push_back(line0);
  promptStrings.push_back(line1);
  promptStrings.push_back(line2);
  promptStrings.push_back(line3);
  promptStrings.push_back(line4);
} // end of "definePromptTitle"



/*
  Function:
   definePromptWin

  Description:
   Uses the incoming numLines and numCols variable values, which contain
   the current max number and columns of STDSCR, to determine if the
   window being tested should be deleted or created.  This is to allow
   dynamic window creation/deletion for any window resizing operations
   done in the terminal.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   numLines             - a reference to a constant integer containing the current
                          maximum number of lines of the main curses window.

   numCols              - a reference to a constant integer containing the current
                          maximum number of columns of the main curses window.

  Output:
   NONE

  Returns:
   NONE
*/
void definePromptWin(std::unordered_map<int, CursesWindow*>& wins,
                     const int& maxLines,
                     const int& maxCols)
{
  const int colOffset = 9;
  const int lineOffset = 2;
  int numLines = _PROMPTWINMAXLINES;
  int numCols = maxCols - _HELPWINMINCOLS - colOffset;;
  int startY = _PROMPTWINSTARTY;
  int startX = _PROMPTWINSTARTX;
  bool define = true;

  if(maxLines - lineOffset <= _PROMPTWINMAXLINES)
    {
      define = false;
    }

  if(define == true)
    {
      // delete the current window if exists before creating a new one
      if(wins.at(_PROMPTWIN)->getWindow() != nullptr)
        {
          wins.at(_PROMPTWIN)->deleteWindow();
          wins.at(_PROMPTWIN)->setWindow(nullptr);
        }

      // create the new window
      wins.at(_PROMPTWIN)->defineWindow(newwin(numLines,
                                               numCols,
                                               startY,
                                               startX),
                                        "_PROMPTWIN",
                                        numLines,
                                        numCols,
                                        startY,
                                        startX);
    }
  // the window has been resized to a bad dimension. delete it
  else
    {
      if(wins.at(_PROMPTWIN)->getWindow() != nullptr)
        {
          wins.at(_PROMPTWIN)->deleteWindow();
          wins.at(_PROMPTWIN)->setWindow(nullptr);
        }
    }
} // end of "definePromptWin"




/*
  Function:
   defineArrowWin

  Description:
   Creates windows that will function as a clickable buttons and in this case
   will output a string that looks like a left or right arrow.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   win                  - a const integer containing a string to set as the
                          name of the objects window name variable.

   startY               - a const int containing the starting line of the arrow
                          window in respect to STDSCR.

   startY               - a const int containing the starting column of the arrow
                          window in respect to STDSCR.

   numLines             - a reference to a constant integer containing the number
                          of lines the button window should be created as.

   numCols              - a reference to a constant integer containing the number
                          of columns the button window should be crated as.


  Output:
   NONE

  Returns:
   NONE
*/
void defineArrowWin(std::unordered_map<int, CursesWindow*>& wins,
                    const int win,
                    std::string winName,
                    const int startY,
                    const int startX,
                    const int numLines,
                    const int numCols,
                    std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      // delete the current window if exists before creating a new one
      if(wins.at(win)->getWindow() != nullptr)
        {
          wins.at(win)->deleteWindow();
          wins.at(win)->setWindow(nullptr);
        }

      // create the new window
      wins.at(win)->defineWindow(newwin(numLines,
                                        numCols,
                                        startY,
                                        startX),
                                 winName,
                                 numLines,
                                 numCols,
                                 startY,
                                 startX);
    }
  else
    {
      // if for any reason _SAVEDFILESWIN isnt allocated and an arrow is, delete it
      if(wins.at(win)->getWindow() != nullptr)
        {
          wins.at(win)->deleteWindow();
          wins.at(win)->setWindow(nullptr);
        }
    }
} // end of "defineArrowWin"



/*
  Function:
   defineSavedFilesWin

  Description:
   Uses the incoming numLines and numCols variable values, which contain
   the current max number and columns of STDSCR, to determine if the
   window being tested should be deleted or created.  This is to allow
   dynamic window creation/deletion for any window resizing operations
   done in the terminal.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   numLines             - a reference to a constant integer containing the current
                          maximum number of lines of the main curses window.

   numCols              - a reference to a constant integer containing the current
                          maximum number of columns of the main curses window.

  Output:
   NONE

  Returns:
   NONE
*/
void defineSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                         const int& maxLines,
                         const int& maxCols,
                         std::ofstream& log)
{
  const int colOffset = 9;
  const int lineOffset = 9;
  int halfedLines = ((maxLines - _SAVEDFILESWINSTARTY) / 2) - 1;
  int numLines = (maxLines - _PROMPTWINSTARTY) - lineOffset;
  int startY = _SAVEDFILESWINSTARTY;
  int startX = _SAVEDFILESWINSTARTX;
  int numCols = maxCols - _HELPWINMINCOLS - colOffset;
  bool colsCheck = false;
  bool linesCheck = false;

  if(numCols > _PROMPTWINMINCOLS)
    {
      colsCheck= true;
    }

  if(_SAVEDFILESWINMINLINES < numLines)
    {
      linesCheck = true;
      if(halfedLines > _SAVEDFILESWINMINLINES)
        {
          numLines = halfedLines;
        }
    }

  // the window is within desired dimensions. allocate it
  if((colsCheck == true) && (linesCheck == true))
    {
      // delete the current window if exists before creating a new one
      if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
        {
          wins.at(_SAVEDFILESWIN)->deleteWindow();
          wins.at(_SAVEDFILESWIN)->setWindow(nullptr);
        }

      // create the new window _SAVEDFILESWIN
      wins.at(_SAVEDFILESWIN)->defineWindow(newwin(numLines,
                                               numCols,
                                               startY,
                                               startX),
                                        "_SAVEDFILESWIN",
                                        numLines,
                                        numCols,
                                        startY,
                                        startX);

      // create the new _LARROWSAVEDFILESWIN
      defineArrowWin(wins,
                     _LARROWSAVEDFILESWIN,
                     sfLeftArrow,
                     _SAVEDFILESWINSTARTY + 2,
                     _SAVEDFILESWINSTARTX + sfTitle.length() + 8,
                     1,
                     3,
                     log);

      // create the new _RARROWSAVEDFILESWIN
      defineArrowWin(wins,
                     _RARROWSAVEDFILESWIN,
                     sfRightArrow,
                     _SAVEDFILESWINSTARTY + 2,
                     wins.at(_LARROWSAVEDFILESWIN)->getStartX() + leftArrow.length() + 1,
                     1,
                     3,
                     log);
    }
  // the window has been resized to a bad dimension. delete it
  else
    {
      wins.at(_SAVEDFILESWIN)->setStartX(startX);
      wins.at(_SAVEDFILESWIN)->setStartY(startY);

      if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
        {
          wins.at(_SAVEDFILESWIN)->deleteWindow();
          wins.at(_SAVEDFILESWIN)->setWindow(nullptr);
        }

      if(wins.at(_LARROWSAVEDFILESWIN)->getWindow() != nullptr)
        {
          wins.at(_LARROWSAVEDFILESWIN)->deleteWindow();
          wins.at(_LARROWSAVEDFILESWIN)->setWindow(nullptr);
        }

      if(wins.at(_RARROWSAVEDFILESWIN)->getWindow() != nullptr)
        {
          wins.at(_RARROWSAVEDFILESWIN)->deleteWindow();
          wins.at(_RARROWSAVEDFILESWIN)->setWindow(nullptr);
        }
    }
} // end of "defineSavedFilesWin"



void defineSFStringWins(std::unordered_map<int, CursesWindow*>& wins,
                        const std::vector<std::string>& savedFileStrings,
                        std::ofstream& log)
{

  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr && !savedFileStrings.empty())
    {
      int sfWinLines = 0;
      int sfWinCols = 0;
      getmaxyx(wins.at(_SAVEDFILESWIN)->getWindow(), sfWinLines, sfWinCols);

      const int lineMinOffset = 2;
      const int colMinOffset = 3;
      const int lineMaxOffset = 4;
      const int colMaxOffset = colMinOffset + 3;

      for(int i = _SFWINSINDEX; i < savedFileStrings.size() + _SFWINSINDEX; i++)
        {
          if(wins.at(i)->getWindow() != nullptr)
            {
              wins.at(i)->deleteWindow();
              wins.at(i)->setWindow(nullptr);
            }
        }

      int upperBound = 0;
      if((sfWinLines - colMaxOffset) > savedFileStrings.size())
        {
          upperBound = savedFileStrings.size();
        }
      else
        {
          upperBound = sfWinLines - colMaxOffset;
        }

      //int j = 0;
      for(int i = _SFWINSINDEX, j = 0; i < (upperBound + _SFWINSINDEX); i++)// j++)
        {
          int numLines = 1;
          int numCols = sfWinCols - colMinOffset - colMaxOffset - 1; // file count
          int startY = (i - _SFWINSINDEX) + wins.at(_SAVEDFILESWIN)->getStartY() +
            lineMinOffset + 2;
          int startX = wins.at(_SAVEDFILESWIN)->getStartX() + colMinOffset + 4;

          wins.at(i)->defineWindow(newwin(numLines,
                                          numCols,
                                          startY,
                                          startX),
                                   "SAVEDFILE",
                                   numLines,
                                   numCols,
                                   startY,
                                   startX);
        }
    }
  else
    {
      if(!savedFileStrings.empty())
        {
          // the _SAVEDFILESWIN is not currently allocated. delete file string windows
          for(int i = _SFWINSINDEX; i < savedFileStrings.size() + _SFWINSINDEX; i++)
            {
              if(wins.at(i)->getWindow() != nullptr)
                {
                  wins.at(i)->deleteWindow();
                  wins.at(i)->setWindow(nullptr);
                }
            }
        }
    }
} // end of "defineSFStringWins"



/*
  Function:
   defineSavedThemesWin

  Description:
   Uses the incoming numLines and numCols variable values, which contain
   the current max number and columns of STDSCR, to determine if the
   window being tested should be deleted or created.  This is to allow
   dynamic window creation/deletion for any window resizing operations
   done in the terminal.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   numLines             - a reference to a constant integer containing the current
                          maximum number of lines of the main curses window.

   numCols              - a reference to a constant integer containing the current
                          maximum number of columns of the main curses window.

  Output:
   NONE

  Returns:
   NONE
*/
void defineSavedThemesWin(std::unordered_map<int, CursesWindow*>& wins,
                          const int& maxLines,
                          const int& maxCols)
{
  const int colOffset = 9;
  const int lineOffset = 9;
  int halfedLines = ((maxLines - _SAVEDFILESWINSTARTY) / 2) - 1;
  int numLines = ((maxLines - _SAVEDFILESWINSTARTY) / 2) - 1;
  int startY = ((maxLines - _SAVEDFILESWINSTARTY)/2) + lineOffset;
  int startX = _SAVEDFILESWINSTARTX;
  int numCols = maxCols - _HELPWINMINCOLS - colOffset;;
  bool colsCheck = false;
  bool linesCheck = false;

  if(numCols > _PROMPTWINMINCOLS)
    {
      colsCheck= true;
    }

  if(_SAVEDTHEMESWINMINLINES < numLines + 1)
    {
      if(halfedLines > _SAVEDFILESWINMINLINES)
        {
          linesCheck = true;
          numLines = halfedLines;
        }
    }

  // the window is within desired dimensions. allocate it
  if((colsCheck == true) && (linesCheck == true))
    {
      // delete the current window if exists before creating a new one
      if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
        {
          wins.at(_SAVEDTHEMESWIN)->deleteWindow();
          wins.at(_SAVEDTHEMESWIN)->setWindow(nullptr);
        }

      // create the new window
      wins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(numLines,
                                               numCols,
                                               startY,
                                               startX),
                                        "_SAVEDTHEMESWIN",
                                        numLines,
                                        numCols,
                                        startY,
                                        startX);
    }
  // the window has been resized to a bad dimension. delete it
  else
    {
      // update the new start positions anyway so other functions can utilize them
      wins.at(_SAVEDTHEMESWIN)->setStartX(startX);
      wins.at(_SAVEDTHEMESWIN)->setStartY(startY);

      if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
        {
          wins.at(_SAVEDTHEMESWIN)->deleteWindow();
          wins.at(_SAVEDTHEMESWIN)->setWindow(nullptr);
        }
    }
} // end of "defineSavedThemesWin"



/*
  Function:
   defineHelpWin

  Description:
   Uses the incoming numLines and numCols variable values, which contain
   the current max number and columns of STDSCR, to determine if the
   window being tested should be deleted or created.  This is to allow
   dynamic window creation/deletion for any window resizing operations
   done in the terminal.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   numLines             - a reference to a constant integer containing the current
                          maximum number of lines of the main curses window.

   numCols              - a reference to a constant integer containing the current
                          maximum number of columns of the main curses window.

  Output:
   NONE

  Returns:
   NONE
*/
void defineHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                   const int& maxLines,
                   const int& maxCols)
{
  const int colOffset = 3;
  const int lineOffset = 2;
  int numLines = (maxLines - _HELPWINSTARTY) - lineOffset;
  int numCols = _HELPWINMINCOLS;
  int startY = _HELPWINSTARTY;
  int startX =  maxCols - _HELPWINMINCOLS - 3;
  bool colsCheck = false;
  bool linesCheck = false;

  if(_HELPWINSTARTY + _HELPWINMINLINES < maxLines - lineOffset)
    {
      numLines = maxLines - lineOffset - startY;
      linesCheck = true;
    }


  if(maxCols > _HELPWINMINCOLS + colOffset)
    {
      colsCheck = true;
    }

  // the window is within desired dimensions. allocate it
  if((linesCheck == true) && (colsCheck == true))
    {
      // delete the current window if exists before creating a new one
      if(wins.at(_HELPWIN)->getWindow() != nullptr)
        {
          wins.at(_HELPWIN)->deleteWindow();
          wins.at(_HELPWIN)->setWindow(nullptr);
        }

      // create the new window
      wins.at(_HELPWIN)->defineWindow(newwin(numLines,
                                             numCols,
                                             startY,
                                             startX),
                                      "_HELPWIN",
                                      numLines,
                                      numCols,
                                      startY,
                                      startX);
    }
  // the window has been resized to a bad dimension. delete it
  else
    {
      // update the new start positions anyway so other functions can utilize them
      wins.at(_HELPWIN)->setStartX(startX);
      wins.at(_HELPWIN)->setStartY(startY);

      if(wins.at(_HELPWIN)->getWindow() != nullptr)
        {
          wins.at(_HELPWIN)->deleteWindow();
          wins.at(_HELPWIN)->setWindow(nullptr);
        }
    }
} // end of "defineHelpWin"



/*
  Function:
   defineWins

  Description:
   Defines the incoming wins object with starting dimension values.  This is
   intended to be used strictly with the "Main Wins" constants from the _WINS
   enumeration structure from the _cursesWinConsts.hpp file.

  Input/Output:
   wins                     - A reference to an unordered map <int, CursesWindow*>
                              object type that will be used to store each
                              CursesWindow object initialized in this function.  The
                              keys are from _cursesWinConsts.hpp and match the
                              corresponding CursesWindow objects they are pointing
                              to.
   NONE

  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void defineWins(std::unordered_map<int, CursesWindow*>& wins,
                const std::vector<std::string>& savedFileStrings,
                std::ofstream& log)
{
  int numLines = 0;
  int numCols = 0;
  int startY = 0;
  int startX = 0;

  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->defineWindow(stdscr,
                                  "_MAINWIN",
                                  numLines,
                                  numCols,
                                  startY,
                                  startX);
  definePromptWin(wins,
                  numLines,
                  numCols);
  defineSavedFilesWin(wins,
                      numLines,
                      numCols,
                      log);
  defineSFStringWins(wins,
                     savedFileStrings,
                     log);
  defineSavedThemesWin(wins,
                       numLines,
                       numCols);
  defineHelpWin(wins,
                numLines,
                numCols);
} // end of "defineWins"



std::vector<std::string> createSFOutputStrings(std::unordered_map<int, CursesWindow*>& wins,
                                               const std::vector<std::string>& savedFileStrings,
                                               const std::vector<std::string>& currThemes,
                                               std::ofstream& log)
{
  std::vector<std::string> outputStrings;

  if(savedFileStrings.empty() || currThemes.empty())
    {
      return outputStrings;
    }

  std::string dots = "...";
  int maxLines = 0;
  int maxCols = 0;

  if(wins.at(_SFWINSINDEX)->getWindow() != nullptr)
    {
      int maxPossible = maxCols - 6;
      std::string tempString;
      std::string fileString;
      std::string themeString;

      getmaxyx(wins.at(_SFWINSINDEX)->getWindow(), maxLines, maxCols);
      int i = 0;

      for(i = 0; i < savedFileStrings.size(); i++)
        {
          fileString.clear();
          themeString.clear();
          tempString.clear();
          fileString = savedFileStrings.at(i);
          themeString = currThemes.at(i);
          int totalFileLength = fileString.length() + dots.length() + themeString.length();


          if(totalFileLength > maxCols)
            {
              int difference = totalFileLength - maxCols;
              tempString.append(dots);

              for(int j = difference + dots.length(); j < fileString.length(); j++)
                {
                  char c = fileString.at(j);
                  tempString.push_back(c);
                }

              tempString.append(dots);
              tempString.append(themeString);
              fileString = tempString;
            }
          else
            {
              int dotCount = fileString.length();

              while(dotCount < maxCols - themeString.length())
                {
                  fileString.push_back('.');
                  dotCount++;
                }
              fileString.append(themeString);
            }
          outputStrings.push_back(fileString);
        }
    }

  return outputStrings;
} // end of "createSFOutputStrings"



/*
  Function:
   printPromptWin

  Description:
   Prints the program title to _PROMPTWIN

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
   title                    - a reference to to a constant vector of strings
                              containing characters that make up a graphical
                              depiction of the title of the program when
                              printed in correct order.

  currLines                 - a reference to a constant integer that contains
                              the current max lines of the STDSCR(_MAINWIN).

  currCols                  - a reference to a constant integer that contains
                              the current max columns of the STDSCR(_MAINWIN).

  Output:
   NONE

  Returns:
   NONE
*/
void printPromptWin(const std::unordered_map<int, CursesWindow*>& wins,
                    const std::vector<std::string>& promptStrings,
                    const int& currLines,
                    const int& currCols,
                    const int& mouseLine,
                    const int& mouseCol,
                    std::ofstream& log)
{
  if(wins.at(_PROMPTWIN)->getWindow() != nullptr)
    {
      int i = 0;
      std::vector<std::string>::const_iterator it;
      std::string outString;
      const int offset = 6;

      for(it = promptStrings.begin(); it != promptStrings.end(); i++, it++)
        {
          outString = *it;
          const int temp = wins.at(_HELPWIN)->getStartX();

          if(outString.length() >= temp - offset)
            {
              outString.resize(temp - offset);
            }

          mvwaddstr(wins.at(_PROMPTWIN)->getWindow(),
                    i,
                    0,
                    outString.c_str());
        }
    }
} // end of "printPromptWin"



/*
  Function:
   printNumberedStrings

  Description:
   Prints the incoming vector of strings as a numbered list to the window buffer
   based on the provided incoming offset values.

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
  strings                   - a reference to to a constant vector of strings
                              to be printed to the window buffer in numbered
                              ascending order.

  lineMaxOffest             - a reference to a constant int type that contains
                              a value used as a offset to subtract from the
                              current windows maximum number of lines
                              available.

  colMaxOffest              - a reference to a constant int type that contains
                              a value used as a offset to subtract from the
                              current windows maximum number of columns
                              available.

  lineMinOffest             - a reference to a constant int type that contains
                              a value used as an offset to the starting line
                              of the window (which should be zero).

  colMinOffset              - a reference to a constant int type that contains
                              a value used as an offset to the starting column
                              of the window (which should be zero).

  Output:
   NONE

  Returns:
   NONE
*/
void printNumberedStrings(std::unordered_map<int, CursesWindow*>& wins,
                          const int& lineMaxOffset,
                          const int& colMaxOffset,
                          const int& lineMinOffset,
                          const int& colMinOffset,
                          std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(_SAVEDFILESWIN)->getWindow(),
               maxWinLines,
               maxWinCols);

      std::string fileCount;

      // print list of the saved files
      for(int i = 0; i < maxWinLines - lineMaxOffset - lineMinOffset; i++)
        {
          fileCount = intToStr(i + 1);
          fileCount.append(". ");

          mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                    i + lineMinOffset + 2,
                    colMinOffset,
                    fileCount.c_str());
        }
    }
} // end of "printNumberedStrings"



/*
  Function:
   printSavedFilesWin

  Description:
   Prints the saved files data to the buffer for the _SAVEDFILESWIN window.

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
  savedFilesStrings         - a reference to to a constant vector of strings
                              containing the paths for the files that have/can
                              be modified by ThemesSwitcher for changing
                              the color theme.
  Output:
   NONE

  Returns:
   NONE
*/
void printSavedFilesWin(std::unordered_map<int, CursesWindow*>& wins,
                        const int& mouseLine,
                        const int& mouseCol,
                        std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(_SAVEDFILESWIN)->getWindow(),
               maxWinLines,
               maxWinCols);

      const int lineMinOffset = 2;
      const int colMinOffset = 3;
      const int lineMaxOffset = 4;
      const int colMaxOffset = colMinOffset + 3;
      int printColPosition;
      std::string filesCount;

      int linePosition = wins.at(_SAVEDFILESWIN)->getStartY() + 2;

      std::vector<std::string>::const_iterator it;
      std::string outString;
      int i = 0;

      // print win title
      outString = sfTitle;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + lineMinOffset,
                colMinOffset,
                outString.c_str());

      // print current theme title
      wattron(wins.at(_SAVEDFILESWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
      outString = sfThemeTitle;
      printColPosition = maxWinCols - outString.length() - colMinOffset;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + lineMinOffset,
                maxWinCols - outString.length() - colMinOffset,
                outString.c_str());

      // print the arrow windows for _SAVEDFILESWIN
      int arrowVal = 0;

      // print the file paths and current theme
      printNumberedStrings(wins,
                           lineMaxOffset,
                           colMaxOffset,
                           lineMinOffset,
                           colMinOffset,
                           log);
    }
} // end of "printSavedFilesWin"




/*
  Function:
   printSavedFilesWin

  Description:
   Prints the saved files data to the buffer for the _SAVEDFILESWIN window.

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
  savedFilesStrings         - a reference to to a constant vector of strings
                              containing the paths for the files that have/can
                              be modified by ThemesSwitcher for changing
                              the color theme.
  Output:
   NONE

  Returns:
   NONE
*/
void printSFStringWins(std::unordered_map<int, CursesWindow*>& wins,
                       std::vector<std::string> outputStrings,
                       const int& outputStringPos,
                       const int& mouseLine,
                       const int& mouseCol,
                       std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr && !outputStrings.empty())
    {
      const int offset = 3;
      int upperBound = 0;
      int maxLines = 0;
      int maxCols = 0;
      getmaxyx(wins.at(_SAVEDFILESWIN)->getWindow(), maxLines, maxCols);

      if((maxLines - offset) > outputStrings.size())
        {
          upperBound = outputStrings.size();
        }
      else
        {
          upperBound = maxLines - offset;
        }

      for(int i = 0; i < upperBound; i++)
        {
          mvwaddstr(wins.at(i + _SFWINSINDEX)->getWindow(),
                    0,
                    0,
                    outputStrings.at(i).c_str());
        }
    }
} // end of "printSFStringWins"



/*
  Function:
   printSavedThemeStrings

  Description:
   Prints the incoming vector of strings as a numbered list to the window buffer
   based on the provided incoming offset values. If the maximum window length is
   reached, the printing continues at a new column offset back at the starting
   line number.

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
   strings                  - a reference to to a constant vector of strings
                              to be printed to the window buffer in numbered
                              ascending order.

   lineMaxOffest            - a reference to a constant int type that contains
                              a value used as a offset to subtract from the
                              current windows maximum number of lines
                              available.

   colMaxOffest             - a reference to a constant int type that contains
                              a value used as a offset to subtract from the
                              current windows maximum number of columns
                              available.

   lineMinOffest            - a reference to a constant int type that contains
                              a value used as an offset to the starting line
                              of the window (which should be zero).

   colMinOffset             - a reference to a constant int type that contains
                              a value used as an offset to the starting column
                              of the window (which should be zero).

  Output:
   NONE

  Returns:
   NONE
*/
void printSavedThemesStrings(const std::unordered_map<int, CursesWindow*>& wins,
                             const std::vector<std::string>& strings,
                             const int& lineMaxOffset,
                             const int& colMaxOffset,
                             const int& lineMinOffset,
                             const int& colMinOffset,
                             const int& mouseLine,
                             const int& mouseCol,
                             std::ofstream& log)
{
  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(_SAVEDTHEMESWIN)->getWindow(),
               maxWinLines,
               maxWinCols);

      int currLine = 0;
      std::string themeCount;
      std::string outString;
      int maxPrintableLines = maxWinLines - lineMinOffset - lineMaxOffset - 1;
      int printColOffset = 0;

      // loop and print to _SAVEDTHEMESWIN
      for(int i = 1; i < strings.size(); i++, currLine++)
        {
          if((i % (maxPrintableLines + 1)) == 0)
            {
              printColOffset += 36;
              currLine = 0;
            }

          themeCount = intToStr(i);
          outString = strings.at(i);

          // append an extra space to the line number for values under 10
          if(i < 10)
            {
              themeCount.append(".  ");
            }
          else
            {
              themeCount.append(". ");
            }

          // make sure it stops printing before the columns print outside the window
          if((themeCount.length() + 3 + printColOffset + outString.length()) >
             (maxWinCols - colMaxOffset))
            {
              break;
            }

          // print the count
          mvwaddstr(wins.at(_SAVEDTHEMESWIN)->getWindow(),
                    currLine + 4,
                    3 + printColOffset,
                    themeCount.c_str());

          // print the saved theme
          mvwaddstr(wins.at(_SAVEDTHEMESWIN)->getWindow(),
                    currLine + 4,
                    themeCount.length() + 3 + printColOffset,
                    outString.c_str());
        }
    }
} // end of "printSavedThemesStrings"



/*
  Function:
   printSavedThemesWin

  Description:
   Prints the saved themes data to the buffer for the _SAVEDTHEMESWIN window.

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
  savedFilesStrings         - a reference to to a constant vector of strings
                              containing the 'saved' themes that can be used
                              to pick the color scheme to switch to.
  Output:
   NONE

  Returns:
   NONE
*/
void printSavedThemesWin(const std::unordered_map<int, CursesWindow*>& wins,
                         const std::vector<std::string>& savedThemesStrings,
                         const int& mouseLine,
                         const int& mouseCol,
                         std::ofstream& log)
{
  const int maxStringSize = 31;
  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(_SAVEDTHEMESWIN)->getWindow(),
               maxWinLines,
               maxWinCols);

      const int lineMinOffset = 2;
      const int colMinOffset = 3;
      const int lineMaxOffset = 4;
      const int colMaxOffset = colMinOffset + 3;

      int linePosition = wins.at(_SAVEDTHEMESWIN)->getStartY() + 2;

      std::vector<std::string>::const_iterator it;
      std::string outString;

      outString = stTitle;
      mvwaddstr(wins.at(_SAVEDTHEMESWIN)->getWindow(),
                lineMinOffset,
                colMinOffset,
                outString.c_str());

      for(int i = 0; i < savedThemesStrings.size(); i++)
        {
          if(i == colMaxOffset - maxStringSize)
            {
              break;
            }

          printSavedThemesStrings(wins,
                                  savedThemesStrings,
                                  lineMaxOffset,
                                  colMaxOffset,
                                  lineMinOffset,
                                  colMinOffset,
                                  mouseLine,
                                  mouseCol,
                                  log);
        }
    }
} // end of "printSavedThemesWin"



/*
  Function:
   checkArrowClick

  Description:
   Prints the incoming "win" to STDSCR which looks like a left or right
   arrow.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   win                  - a const integer containing a value representing a window
                          from _cursesWinConsts.hpp that should be for an arrow
                          window.

  mouseLine             - A reference to a constant integer containing the 'y'
                          value or 'line number' in which a mouse click was
                          detected.

  mouseLine             - A reference to a constant integer containing the 'x'
                          value or 'column number' in which a mouse click was
                          detected.

  outString             - A string type containing a the string to print to
                          output to the incoming window buffer.

  Output:
   NONE

  Returns:
   NONE
*/
int checkArrowClick(const std::unordered_map<int, CursesWindow*>& wins,
                    const int win,
                    const std::vector<std::string>& outputStrings,
                    int& outputStringPos,
                    const int& mouseLine,
                    const int& mouseCol,
                    std::string outString,
                    std::ofstream& log)
{
  int returnVal = 0;

  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     wins.at(win)->getWindow() != nullptr)
    {
      // flash window if mouse click deteceted in range
      if((mouseLine == wins.at(win)->getStartY()) &&
         (mouseCol >= wins.at(win)->getStartX() &&
          mouseCol <= wins.at(win)->getStartX() + outString.length() - 1))
        {
          wattron(wins.at(win)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
          mvwaddstr(wins.at(win)->getWindow(),
                    0,
                    0,
                    outString.c_str());
          wnoutrefresh(wins.at(win)->getWindow());
          doupdate();
          usleep(40000);

          if(win == _LARROWSAVEDFILESWIN)
            {
              // shiftFilesRight(wins,
              //                 outputStrings,
              //                 outputStringPos,
              //                 log);
            }
          else
            {
              shiftFilesRight(wins,
                              outputStrings,
                              outputStringPos,
                              log);
            }
        }
      // print the regular window color
      wattron(wins.at(win)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
      mvwaddstr(wins.at(win)->getWindow(),
                0,
                0,
                outString.c_str());
      wattron(wins.at(win)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
    }

  return returnVal;
} // end of "checkArrowClick"



void shiftFilesRight(const std::unordered_map<int, CursesWindow*>& wins,
                     const std::vector<std::string>& outputStrings,
                     int& outputStringPos,
                     std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     !outputStrings.empty())
    {
      const int minLineOffset = 4;
      const int maxLineOffset = 2;
      const int minColOffset = 7;
      const int maxColOffset = 4;
      int maxLines = wins.at(_SAVEDFILESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDFILESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDFILESWIN)->getStartY();
      const int startX = wins.at(_SAVEDFILESWIN)->getStartX();

      // get number of printable file windows
      int val = maxLines - minLineOffset - maxLineOffset;

      // check if there is another list to 'scroll' to
      if(outputStringPos + val < outputStrings.size())
        {
          // delete the current set of windows
          int i = 0;
          for(i = outputStringPos + _SFWINSINDEX;
              (i < _SFWINSINDEX + val + outputStringPos) &&
                (i < outputStrings.size() + _SFWINSINDEX);
              i++)
            {
              if(wins.at(i)->getWindow() != nullptr)
                {
                  werase(wins.at(i)->getWindow());
                  wnoutrefresh(wins.at(i)->getWindow());
                  wins.at(i)->deleteWindow();
                  wins.at(i)->setWindow(nullptr);
                }
            }

          outputStringPos += val;

          // allocate the new set of windows for the scrolled output strings
          for(i = outputStringPos + _SFWINSINDEX; i < _SFWINSINDEX + outputStringPos + val; i++)
            {
              if((i - _SFWINSINDEX) < outputStrings.size())
                {
                  const int lineMinOffset = 2;
                  const int colMinOffset = 3;
                  const int lineMaxOffset = 4;
                  const int colMaxOffset = colMinOffset + 3;
                  const int fileCountOffset = 4;
                  int numLines = 1;
                  int numCols = maxCols - colMinOffset - colMaxOffset - 1;
                  int startY = (i  - _SFWINSINDEX - outputStringPos) + wins.at(_SAVEDFILESWIN)->getStartY() +
                    lineMinOffset + 2;
                  int startX = wins.at(_SAVEDFILESWIN)->getStartX() + colMinOffset + fileCountOffset;

                  wins.at(i)->defineWindow(newwin(numLines,
                                                  numCols,
                                                  startY,
                                                  startX),
                                           "SAVEDFILE",
                                           numLines,
                                           numCols,
                                           startY,
                                           startX);
                }
            }
        }
    }
}



/*
  Function:
   checkFileClick

  Description:
   Checks if the incoming mouse click Line and Col values match with a
   printed file line.  If they do, the matching file line coordinate file
   line is printed in the "highlighted" color scheme.

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
  outputStrings             - a reference to to a constant vector of strings
                              containing the formatted file string lines
                              that will be used for outputing to file line
                              windows.

  mouseLine                 - a reference to a constant integer that contains
                              the current Y(line) value of the just clicked
                              mouse click.

  mouseCol                  - a reference to a constant integer that contains
                              the current X(col) value of the just clicked
                              mouse click.
  Output:
   NONE

  Returns:
   NONE
*/
void checkFileClick(const std::unordered_map<int, CursesWindow*>& wins,
                    const std::vector<std::string>& outputStrings,
                    const int& mouseLine,
                    const int& mouseCol,
                    int& outputStringPos,
                    std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     !outputStrings.empty())
    {
      const int minLineOffset = 4;
      const int maxLineOffset = 2;
      const int minColOffset = 7;
      const int maxColOffset = 4;
      int maxLines = wins.at(_SAVEDFILESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDFILESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDFILESWIN)->getStartY();
      const int startX = wins.at(_SAVEDFILESWIN)->getStartX();

      // enter iff the mouse click is in file clicking range offsets
      if(((mouseLine >= startY + minLineOffset) &&
                        (mouseLine <= startY + maxLines - maxLineOffset - 1)) &&
         ((mouseCol >= startX + minColOffset) &&
          (mouseCol <= startX + maxCols - maxColOffset)))
        {
          int offSet = 3;
          int j = 0;
          int i = 0;

            for(i = _SFWINSINDEX + outputStringPos, j = outputStringPos;
                i < _SFWINSINDEX + _SAVEDFILESWINSTARTY +
                  wins.at(_SAVEDFILESWIN)->getNumLines() - offSet + outputStringPos; i++, j++)
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
      else
        {
          int offSet = 3;
          int j = 0;
          int i = 0;
          int val = maxLines - minLineOffset - maxLineOffset;

          // check not out of range of the input list before printing
          if(outputStringPos < outputStrings.size())
            {
              for(i = _SFWINSINDEX + outputStringPos, j = outputStringPos;
                  i < _SFWINSINDEX + startY + maxLines + outputStringPos - offSet; i++, j++)
                {
                  // stop printing when end of list is reached
                  if(j >= outputStrings.size())
                    {
                      break;
                    }

                  wattron(wins.at(i)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
                  mvwaddstr(wins.at(i)->getWindow(),
                            0,
                            0,
                            outputStrings.at(j).c_str());
                }
            }
        }
    }
} // end of "checkFileClick"



/*
  Function:
   refreshWins

  Description:
   Refreshes all CursesWindow objects member variables that point to a
   currently allocated WINDOW type (values that are not nullptr). They are
   sorted before refreshing to ensure the proper write order.

  Input/Output:
   wins                     - A reference to a const unordered map
                              <int, CursesWindow*> type that contains pointers
                              to all currently allocated CursesWindow objects
                              that can be indexed by key values in the file
                              _cursesWinConsts.hpp.
  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void refreshWins(const std::unordered_map<int, CursesWindow*>& wins)
{

  // ##
  std::unordered_map<int, CursesWindow*>::const_iterator it;
  std::vector<int> tempMainWins;

  // store all currently initialized window indexes
  for(it = wins.begin(); it != wins.end(); it++)
    {
      if(it->second->getWindow() != nullptr)
        {
          tempMainWins.push_back(it->first);
        }
    }

  // sort them in ascending order
  std::sort(tempMainWins.begin(), tempMainWins.end());

  // refresh the initialized windows
  for(std::vector<int>::iterator vecIt = tempMainWins.begin();
      vecIt != tempMainWins.end();
      vecIt++)
    {
      wnoutrefresh(wins.at(*vecIt)->getWindow());
    }

  // ##
  // for(int i = _MAINWIN; i <= _RARROWSAVEDFILESWIN; i++)
  //   {
  //     if(wins.at(i)->getWindow() != nullptr)
  //       {
  //         wnoutrefresh(wins.at(i)->getWindow());
  //         doupdate();
  //       }
  //   }

} // end of "refreshWins"



/*
  Function:
   clearWins

  Description:
   Clears all currently active and defined CursesWindow object screens. All
   "erased" screens are stored in the screen buffer waiting for a call to
   refresh() to write the changes.

  Input/Output:
   NONE

  Input:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
   NONE
*/
void clearWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::unordered_map<int, CursesWindow*>::const_iterator it;
  for(it = wins.begin(); it != wins.end(); it++)
    {
      werase(it->second->getWindow());
    }
} // end of "clearWins"



/*
  Function:
   drawBoxes

  Description:
   Draws a box for every "WINDOW" that is currently initialized and stored
   in the "wins" object.

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to CursesWindow objects that can be indexed by values
                          in the file _cursesWinConsts.hpp.
  Input:
   NONE

  Output:
   NONE

  Returns:
   NONE
*/
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins,
               std::ofstream& log)
{
  char val = 'A';
  std::unordered_map<int, CursesWindow*>::const_iterator it;

  for(it = wins.begin(); it != wins.end(); it++)
    {
      if((it->second->getWindowName() != "SAVEDFILE") &&
         (it->second->getWindowName() != "_PROMPTWIN")&&
         (it->second->getWindowName() != "_LARROWSAVEDFILESWIN") &&
         (it->second->getWindowName() != "_RARROWSAVEDFILESWIN"))
        {
          if(val == '[')
            {
              val = 'A';
            }

          val++;

          if(it->second->getWindow() != nullptr)
            {
              box(it->second->getWindow(), val, val);
            }
      }
    }
} // end of "drawBoxes"
