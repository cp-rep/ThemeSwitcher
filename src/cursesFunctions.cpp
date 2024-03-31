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
  for(int i = _MAINWIN; i <= _RARROWSAVEDTHEMESWIN; i++)
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
  promptStrings.clear();
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
  int numLines = _PROMPTWINMAXLINES;
  int numCols = maxCols - _HELPWINMINCOLS - _PROMPTWINCOLOFFSET;
  int startY = _PROMPTWINSTARTY;
  int startX = _PROMPTWINSTARTX;
  bool define = true;

  if(maxLines - _PROMPTWINLINEOFFSET <= _PROMPTWINMAXLINES)
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
                    const int mainWin,
                    const int arrowWin,
                    std::string winName,
                    const int startY,
                    const int startX,
                    const int numLines,
                    const int numCols,
                    std::ofstream& log)
{
  if(wins.at(mainWin)->getWindow() != nullptr)
    {
      // delete the current window if exists before creating a new one
      if(wins.at(arrowWin)->getWindow() != nullptr)
        {
          wins.at(arrowWin)->deleteWindow();
          wins.at(arrowWin)->setWindow(nullptr);
        }

      // create the new window
      wins.at(arrowWin)->defineWindow(newwin(numLines,
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
      // if for any reason the mainWin isnt allocated and an arrow is, delete it
      if(wins.at(arrowWin)->getWindow() != nullptr)
        {
          wins.at(arrowWin)->deleteWindow();
          wins.at(arrowWin)->setWindow(nullptr);
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
   maxLines             - a reference to a constant integer containing the current
                          maximum number of lines of the main curses window STDSCR.

   maxCols              - a reference to a constant integer containing the current
                          maximum number of columns of the main curses window STDSCR.

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

  if(numCols > _SAVEDFILESWINMINCOLS)
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
                     _SAVEDFILESWIN,
                     _LARROWSAVEDFILESWIN,
                     sfLeftArrow,
                     _SAVEDFILESWINSTARTY + 2,
                     _SAVEDFILESWINSTARTX + sfTitle.length() + 8,
                     1,
                     3,
                     log);

      // create the new _RARROWSAVEDFILESWIN
      defineArrowWin(wins,
                     _SAVEDFILESWIN,
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



void defineSFStringWins(const std::unordered_map<int, CursesWindow*>& wins,
                        std::vector<CursesWindow*>& sfStringWins,
                        const std::vector<std::string>& savedFileStrings,
                        const int& outputStringPos,
                        std::ofstream& log)
{
  // delete any windows if they exist
  for(int i = 0; i < sfStringWins.size(); i++)
    {
      if(sfStringWins.at(i)->getWindow() != nullptr)
        {
          werase(sfStringWins.at(i)->getWindow());
          sfStringWins.at(i)->deleteWindow();
          sfStringWins.at(i)->setWindow(nullptr);
          delete sfStringWins.at(i);
        }
    }

  sfStringWins.clear();

  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      int maxLines = wins.at(_SAVEDFILESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDFILESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDFILESWIN)->getStartY();
      const int startX = wins.at(_SAVEDFILESWIN)->getStartX();

      // get number of printable file windows
      int val = maxLines - _SFSWINMINLINEOFFSET - _SFSWINMAXLINEOFFSET;

      // allocate the new set of windows for the scrolled output strings
      int j = 0;
      int i = 0;
      for(i = 0, j = outputStringPos; i < val && j < savedFileStrings.size(); i++, j++)
        {
          CursesWindow* newWindow = new CursesWindow();
          sfStringWins.push_back(newWindow);

          int numLines = 1;
          int numCols = maxCols - _SFWINMINCOLOFFSET - _SFWINMAXCOLOFFSET;
          int startY = i + wins.at(_SAVEDFILESWIN)->getStartY() + _SFSWINMINLINEOFFSET;
          int startX = wins.at(_SAVEDFILESWIN)->getStartX() + _SFWINMINCOLOFFSET;

          sfStringWins.at(i)->defineWindow(newwin(numLines,
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
   maxLines             - a reference to a constant integer containing the current
                          maximum number of lines of the main curses window STDSCR.

   maxCols              - a reference to a constant integer containing the current
                          maximum number of columns of the main curses window STDSCR.

  Output:
   NONE

  Returns:
   NONE
*/
void defineSavedThemesWin(std::unordered_map<int, CursesWindow*>& wins,
                          const int& maxLines,
                          const int& maxCols,
                          std::ofstream& log)
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

  if(numCols > _SAVEDTHEMESWINMINCOLS)
    {
      colsCheck= true;
    }

  if(_SAVEDTHEMESWINMINLINES < numLines)
    {
      if(halfedLines > _SAVEDFILESWINMINLINES - 1)
        {
          linesCheck = true;
          numLines = halfedLines;
          if(numLines + startY == maxLines - 1)
            {
              numLines--;
            }
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

      // create the new _LARROWSAVEDFILESWIN
      defineArrowWin(wins,
                     _SAVEDTHEMESWIN,
                     _LARROWSAVEDTHEMESWIN,
                     stLeftArrow,
                     wins.at(_SAVEDTHEMESWIN)->getStartY() + 2,
                     wins.at(_SAVEDTHEMESWIN)->getStartX() + stTitle.length() + 8,
                     1,
                     3,
                     log);

      // create the new _RARROWSAVEDFILESWIN
      defineArrowWin(wins,
                     _SAVEDTHEMESWIN,
                     _RARROWSAVEDTHEMESWIN,
                     stRightArrow,
                     wins.at(_SAVEDTHEMESWIN)->getStartY() + 2,
                     wins.at(_LARROWSAVEDTHEMESWIN)->getStartX() + leftArrow.length() + 1,
                     1,
                     3,
                     log);
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

      if(wins.at(_LARROWSAVEDTHEMESWIN)->getWindow() != nullptr)
        {
          wins.at(_LARROWSAVEDTHEMESWIN)->deleteWindow();
          wins.at(_LARROWSAVEDTHEMESWIN)->setWindow(nullptr);
        }

      if(wins.at(_RARROWSAVEDTHEMESWIN)->getWindow() != nullptr)
        {
          wins.at(_RARROWSAVEDTHEMESWIN)->deleteWindow();
          wins.at(_RARROWSAVEDTHEMESWIN)->setWindow(nullptr);
        }
    }
} // end of "defineSavedThemesWin"



void defineSTStringWins(const std::unordered_map<int, CursesWindow*>& wins,
                        std::vector<CursesWindow*>& stStringWins,
                        const std::vector<std::string>& stStrings,
                        const int& stStringPos,
                        std::ofstream& log)
{
  // delete any stStringWins if they exist
  for(int i = 0; i < stStringWins.size(); i++)
    {
      if(stStringWins.at(i)->getWindow() != nullptr)
        {
          werase(stStringWins.at(i)->getWindow());
          stStringWins.at(i)->deleteWindow();
          stStringWins.at(i)->setWindow(nullptr);
          delete stStringWins.at(i);
        }
    }

  stStringWins.clear();

  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      int maxLines;
      int maxCols;

      getmaxyx(wins.at(_SAVEDTHEMESWIN)->getWindow(),
               maxLines,
               maxCols);

      int printableLines = maxLines - _STWINMINLINEOFFSET - _STWINMAXLINEOFFSET;
      int numLines = 1;
      int numMaxCols = _STWINMAXCOLS;
      int printColOffset = 0;
      int printLineOffset = 0;
      const int titleLineOffset = 4;

      for(int i = 0, j = stStringPos; j < stStrings.size(); i++, j++, printLineOffset++)
        {
          int numCols = stStrings.at(j).length();

          // reset the output line position if max printable line is reached
          if(printLineOffset == printableLines)
            {
              printColOffset += numMaxCols + 2;
              printLineOffset = 0;
            }

          // make sure not to print or create windows out of the max window range
          if(printColOffset > maxCols  - _STWINMAXCOLOFFSET - _STWINMINCOLOFFSET - numMaxCols)
            {
              break;
            }

          // create the window
          const int startY = wins.at(_SAVEDTHEMESWIN)->getStartY() + titleLineOffset +
            printLineOffset;
          const int startX = wins.at(_SAVEDTHEMESWIN)->getStartX() + printColOffset +
            _STWINMINCOLOFFSET;

          CursesWindow* newWindow = new CursesWindow();

          stStringWins.push_back(newWindow);
          stStringWins.at(i)->defineWindow(newwin(numLines,
                                                  numCols,
                                                  startY,
                                                  startX),
                                           "SAVEDTHEME",
                                           numLines,
                                           numCols,
                                           startY,
                                           startX);
        }
    }
} // end of "defineSTStringWins"



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
   maxLines             - a reference to a constant integer containing the current
                          maximum number of lines of the main curses window STDSCR.

   maxCols              - a reference to a constant integer containing the current
                          maximum number of columns of the main curses STDSCR.

  Output:
   NONE

  Returns:
   NONE
*/
void defineHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                   const int& maxLines,
                   const int& maxCols)
{
  int numLines = (maxLines - _HELPWINSTARTY) - _HELPWINLINEOFFSET;
  int numCols = _HELPWINMINCOLS;
  int startY = _HELPWINSTARTY;
  int startX =  maxCols - _HELPWINMINCOLS - _HELPWINCOLOFFSET;
  bool colsCheck = false;
  bool linesCheck = false;

  if(_HELPWINSTARTY + _HELPWINMINLINES < maxLines - _HELPWINLINEOFFSET)
    {
      numLines = maxLines - _HELPWINLINEOFFSET - startY;
      linesCheck = true;
    }

  if(maxCols > _HELPWINMINCOLS + _HELPWINCOLOFFSET)
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
  defineHelpWin(wins,
                numLines,
                numCols);
  definePromptWin(wins,
                  numLines,
                  numCols);
  defineSavedFilesWin(wins,
                      numLines,
                      numCols,
                      log);
  defineSavedThemesWin(wins,
                       numLines,
                       numCols,
                       log);
} // end of "defineWins"



std::vector<std::string> createSFOutputStrings(const std::unordered_map<int, CursesWindow*>& wins,
                                               std::vector<CursesWindow*>& sfStringWins,
                                               const std::vector<std::string>& sfStrings,
                                               const std::vector<std::string>& currThemes,
                                               std::ofstream& log)
{
  std::vector<std::string> outputStrings;

  if(sfStrings.empty() || currThemes.empty())
    {
      return outputStrings;
    }

  std::string dots = "...";
  int maxLines = 0;
  int maxCols = 0;

  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      outputStrings.clear();
      if(sfStringWins.at(0)->getWindow() != nullptr)
        {
          int maxPossible = maxCols - 6;
          std::string tempString;
          std::string fileString;
          std::string themeString;
          std::string countString;

          getmaxyx(sfStringWins.at(0)->getWindow(), maxLines, maxCols);
          int i = 0;

          for(i = 0; i < sfStrings.size(); i++)
            {
              countString.clear();
              fileString.clear();
              themeString.clear();
              tempString.clear();
              countString = intToStr(i+1);
              countString.append(". ");
              fileString = sfStrings.at(i);
              themeString = currThemes.at(i);
              int totalFileLength = fileString.length() + dots.length() +
                themeString.length() + countString.length();

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

                  while(dotCount < maxCols - themeString.length() - countString.length())
                    {
                      fileString.push_back('.');
                      dotCount++;
                    }
                  fileString.append(themeString);
                }
              countString.append(fileString);
              outputStrings.push_back(countString);
            }
        }
    }

  return outputStrings;
} // end of "createSFOutputStrings"



std::vector<std::string> createSTOutputStrings(const std::unordered_map<int, CursesWindow*>& wins,
                                               const std::vector<std::string>& stStrings,
                                               const int& stStringPos,
                                               std::ofstream& log)
{
  std::vector<std::string> outputStrings;

  if(stStrings.empty())
    {
      return outputStrings;
    }

  std::string dots = "...";
  int maxLines = 0;
  int maxCols = 30;

  std::string tempString;
  std::string fileString;
  int i = 0;
  int j = 0;
  for(j = stStringPos; j < stStrings.size(); j++)
    {
      fileString.clear();
      tempString.clear();
      fileString = intToStr(j+1);
      fileString.append(". ");
      fileString.append(stStrings.at(j));

      if(maxCols < fileString.length())
        {
          while( (maxCols - fileString.length()) != 3)
            {
              fileString.pop_back();
            }
          fileString.append(dots);
        }
      outputStrings.push_back(fileString);
    }

  return outputStrings;
} // end of "createSTOutputStrings"



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
      for(int i = 0; i < maxWinLines - _SFWINMAXLINEOFFSET - _SFWINMINLINEOFFSET; i++)
        {
          fileCount = intToStr(i + 1);
          fileCount.append(". ");

          mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                    i + _SFWINMINLINEOFFSET + 2,
                    _SFWINMINCOLOFFSET,
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
                        std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(_SAVEDFILESWIN)->getWindow(),
               maxWinLines,
               maxWinCols);

      int printColPosition;
      std::string filesCount;

      int linePosition = wins.at(_SAVEDFILESWIN)->getStartY() + 2;

      std::vector<std::string>::const_iterator it;
      std::string outString;
      int i = 0;

      // print win title
      outString = sfTitle;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + _SFWINMINLINEOFFSET,
                _SFWINMINCOLOFFSET,
                outString.c_str());

      // print current theme title
      wattron(wins.at(_SAVEDFILESWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
      outString = sfThemeTitle;
      printColPosition = maxWinCols - outString.length() - _SFWINMINCOLOFFSET;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + _SFWINMINLINEOFFSET,
                maxWinCols - outString.length() - _SFWINMINCOLOFFSET,
                outString.c_str());

      // print the arrow windows for _SAVEDFILESWIN
      printArrowWin(wins,
                    _LARROWSAVEDFILESWIN,
                    leftArrow,
                    _BLACK_TEXT,
                    log);

      printArrowWin(wins,
                    _RARROWSAVEDFILESWIN,
                    rightArrow,
                    _BLACK_TEXT,
                    log);
    }
} // end of "printSavedFilesWin"



/*
  Function:
   printSavedFilesStrings

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
void printSavedFilesStrings(std::unordered_map<int, CursesWindow*>& wins,
                            std::vector<CursesWindow*>& sfStringWins,
                            std::vector<std::string> sfStrings,
                            const int& sfStringPos,
                            const int& currStartWin,
                            const int& highlightWinNum,
                            std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      int j = sfStringPos;
      for(int i = 0; i < sfStringWins.size() && j < sfStrings.size(); i++, j++)
        {
          if(sfStringWins.at(i)->getWindow() != nullptr)
            {
              if(highlightWinNum == i)
                {
                  wattron(sfStringWins.at(i)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
                }
              else
                {
                  wattron(sfStringWins.at(i)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
                }

              mvwaddstr(sfStringWins.at(i)->getWindow(),
                        0,
                        0,
                        sfStrings.at(j).c_str());
            }
        }
    }
} // end of "printSavedFilesStrings"



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
                             std::vector<CursesWindow*>& stStringWins,
                             const std::vector<std::string>& stStrings,
                             const int& stStringPos,
                             const int& stHighlightNum,
                             std::ofstream& log)
{
  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      int j = stStringPos;
      for(int i = 0; i < stStringWins.size() && j < stStrings.size(); i++, j++)
        {
          if(stStringWins.at(i)->getWindow() != nullptr)
            {
              if(stHighlightNum == i)
                {
                  wattron(stStringWins.at(i)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
                }
              else
                {
                  wattron(stStringWins.at(i)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
                }

              mvwaddstr(stStringWins.at(i)->getWindow(),
                        0,
                        0,
                        stStrings.at(j).c_str());
            }
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
                         std::ofstream& log)
{
  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      const int maxStringSize = 31;
      const int lineCount = 0;
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(_SAVEDTHEMESWIN)->getWindow(),
               maxWinLines,
               maxWinCols);

      int linePosition = wins.at(_SAVEDTHEMESWIN)->getStartY() + 2 + lineCount;
      std::vector<std::string>::const_iterator it;
      std::string outString;

      outString = stTitle;
      mvwaddstr(wins.at(_SAVEDTHEMESWIN)->getWindow(),
                _STWINMINLINEOFFSET,
                _STWINMINCOLOFFSET,
                outString.c_str());
      printArrowWin(wins,
                    _LARROWSAVEDTHEMESWIN,
                    leftArrow,
                    _BLACK_TEXT,
                    log);

      printArrowWin(wins,
                    _RARROWSAVEDTHEMESWIN,
                    rightArrow,
                    _BLACK_TEXT,
                    log);
    }
} // end of "printSavedThemesWin"



void shiftSFRight(const std::unordered_map<int, CursesWindow*>& wins,
                     std::vector<CursesWindow*>& sfStringWins,
                     const std::vector<std::string>& outputStrings,
                     int& sfStringPos,
                     std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     !outputStrings.empty())
    {
      int maxLines = wins.at(_SAVEDFILESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDFILESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDFILESWIN)->getStartY();
      const int startX = wins.at(_SAVEDFILESWIN)->getStartX();

      // get number of printable file windows
      int val = maxLines - _SFSWINMINLINEOFFSET - _SFSWINMAXLINEOFFSET;

      // check if there is another list to 'scroll' to
      if(sfStringPos + val < outputStrings.size())
        {
          defineSFStringWins(wins,
                             sfStringWins,
                             outputStrings,
                             sfStringPos,
                             log);
          sfStringPos += val;
        }
    }
} // end of "shiftSFRight"



void shiftSFLeft(const std::unordered_map<int, CursesWindow*>& wins,
                    std::vector<CursesWindow*>& sfStringWins,
                    const std::vector<std::string>& outputStrings,
                    int& sfStringPos,
                    std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     !outputStrings.empty())
    {
      int maxLines = wins.at(_SAVEDFILESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDFILESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDFILESWIN)->getStartY();
      const int startX = wins.at(_SAVEDFILESWIN)->getStartX();

      // get number of printable file windows
      int val = maxLines - _SFSWINMINLINEOFFSET - _SFSWINMAXLINEOFFSET;

      // check if there is another list to 'scroll' to
      if(sfStringPos - val >= 0)
        {
          sfStringPos -= val;
          defineSFStringWins(wins,
                             sfStringWins,
                             outputStrings,
                             sfStringPos,
                             log);
        }
      else
        {
          sfStringPos = 0;
          defineSFStringWins(wins,
                             sfStringWins,
                             outputStrings,
                             sfStringPos,
                             log);
        }
    }
}// end of "shiftSFLeft"



void shiftSTLeft(std::unordered_map<int, CursesWindow*>& wins,
                 std::vector<CursesWindow*>& stStringWins,
                 const std::vector<std::string>& outputStrings,
                 int& stStringPos,
                 std::ofstream& log)
{
  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr &&
     !outputStrings.empty())
    {
      int maxLines = wins.at(_SAVEDTHEMESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDTHEMESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDTHEMESWIN)->getStartY();
      const int startX = wins.at(_SAVEDTHEMESWIN)->getStartX();

      // get number of printable file windows
      int val = maxLines - _STWINMINLINEOFFSET - _STWINMAXLINEOFFSET;

      defineSavedThemesWin(wins,
                           wins.at(_MAINWIN)->getNumLines(),
                           wins.at(_MAINWIN)->getNumCols(),
                           log);
      wattron(wins.at(_SAVEDTHEMESWIN)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
      box(wins.at(_SAVEDTHEMESWIN)->getWindow(), ' ', ' ');
      wattron(wins.at(_SAVEDTHEMESWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
      printSavedThemesWin(wins,
                          log);

      // check if there is another list to 'scroll' to
      if(stStringPos - val >= 0)
        {
          stStringPos -= val;
          defineSTStringWins(wins,
                             stStringWins,
                             outputStrings,
                             stStringPos,
                             log);
        }
      else
        {
          stStringPos = 0;
          defineSTStringWins(wins,
                             stStringWins,
                             outputStrings,
                             stStringPos,
                             log);
        }
    }
}// end of "shiftSFLeft"


void shiftSTRight(std::unordered_map<int, CursesWindow*>& wins,
                  std::vector<CursesWindow*>& stStringWins,
                  const std::vector<std::string>& outputStrings,
                  int& outputStringPos,
                  std::ofstream& log)
{
  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr &&
     !outputStrings.empty())
    {
      int maxLines = wins.at(_SAVEDTHEMESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDTHEMESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDTHEMESWIN)->getStartY();
      const int startX = wins.at(_SAVEDTHEMESWIN)->getStartX();

      // get number of printable file windows
      int val = maxLines - _STWINMINLINEOFFSET - _STWINMAXLINEOFFSET;

      // check if there is another list to 'scroll' to
      if(outputStringPos + val < outputStrings.size())
        {
          defineSavedThemesWin(wins,
                               wins.at(_MAINWIN)->getNumLines(),
                               wins.at(_MAINWIN)->getNumCols(),
                               log);
          wattron(wins.at(_SAVEDTHEMESWIN)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
          box(wins.at(_SAVEDTHEMESWIN)->getWindow(), ' ', ' ');
          wattron(wins.at(_SAVEDTHEMESWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
          printSavedThemesWin(wins,
                              log);
          outputStringPos += val;
          defineSTStringWins(wins,
                             stStringWins,
                             outputStrings,
                             outputStringPos,
                             log);
        }
    }
} // end of "shiftSTRight"



void printArrowWin(const std::unordered_map<int, CursesWindow*>& wins,
                     const int win,
                     std::string outString,
                     const int colorPair,
                     std::ofstream& log)
{
  wattron(wins.at(win)->getWindow(), COLOR_PAIR(colorPair));
  mvwaddstr(wins.at(win)->getWindow(),
            0,
            0,
            outString.c_str());
} // end of "printArrowWin"



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
void checkArrowClick(std::unordered_map<int, CursesWindow*>& wins,
                     std::vector<CursesWindow*>& stringWins,
                     const int mainWin,
                     const int arrowWin,
                     const std::vector<std::string>& outputStrings,
                     int& outputStringPos,
                     const int& mouseLine,
                     const int& mouseCol,
                     std::string outString,
                     std::ofstream& log)
{
  if(wins.at(mainWin)->getWindow() != nullptr &&
     wins.at(arrowWin)->getWindow() != nullptr)
    {
      // flash window if mouse click deteceted in range
      if((mouseLine == wins.at(arrowWin)->getStartY()) &&
         (mouseCol >= wins.at(arrowWin)->getStartX() &&
          mouseCol <= wins.at(arrowWin)->getStartX() + outString.length() - 1))
        {
          // give the arrow button that was clicked the 'click effect'
          printArrowWin(wins,
                        arrowWin,
                        outString,
                        _WHITE_TEXT,
                        log);
          wnoutrefresh(wins.at(arrowWin)->getWindow());
          doupdate();
          usleep(40000);

          // 'shift'  saved file win list left
          if(arrowWin == _LARROWSAVEDFILESWIN)
            {
              shiftSFLeft(wins,
                             stringWins,
                             outputStrings,
                             outputStringPos,
                             log);
            }
          // 'shift' saved file win list right
          else if (arrowWin == _RARROWSAVEDFILESWIN)
            {
              shiftSFRight(wins,
                           stringWins,
                           outputStrings,
                           outputStringPos,
                           log);
            }
          else if (arrowWin == _LARROWSAVEDTHEMESWIN)
            {
              shiftSTLeft(wins,
                          stringWins,
                          outputStrings,
                          outputStringPos,
                          log);
            }
          else if(arrowWin == _RARROWSAVEDTHEMESWIN)
            {
              shiftSTRight(wins,
                           stringWins,
                           outputStrings,
                           outputStringPos,
                           log);
            }

          printArrowWin(wins,
                        arrowWin,
                        outString,
                        _BLACK_TEXT,
                        log);
        }
    }
} // end of "checkArrowClick"



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
void checkSFClick(const std::unordered_map<int, CursesWindow*>& wins,
                    const std::vector<std::string>& outputStrings,
                    const int& outputStringPos,
                    const int& mouseLine,
                    const int& mouseCol,
                    int& highlightWinNum,
                    std::ofstream& log)
{
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     !outputStrings.empty())
    {
      int maxLines = wins.at(_SAVEDFILESWIN)->getNumLines();
      int maxCols = wins.at(_SAVEDFILESWIN)->getNumCols();
      const int startY = wins.at(_SAVEDFILESWIN)->getStartY();
      const int startX = wins.at(_SAVEDFILESWIN)->getStartX();

      // enter iff the mouse click is in file clicking range offsets
      if(((mouseLine >= startY + _SFSWINMINLINEOFFSET) &&
                        (mouseLine < startY + maxLines - _SFSWINMAXLINEOFFSET)) &&
         ((mouseCol >= startX + _SFWINMINCOLOFFSET) &&
          (mouseCol < startX + maxCols - _SFWINMAXCOLOFFSET)))
        {
          highlightWinNum = mouseLine - (wins.at(_SAVEDFILESWIN)->getStartY()
                                       + _SFSWINMINLINEOFFSET);
        }
      else
        {
          highlightWinNum = -1;
        }
    }
} // end of "checkFileClick"



void checkSTClick(const std::unordered_map<int, CursesWindow*>& wins,
                  const std::vector<CursesWindow*>& stStringWins,
                  const int& mouseLine,
                  const int& mouseCol,
                  int& highlightWinNum,
                  std::ofstream& log)
{
  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr && !stStringWins.empty())
    {
      for(int i = 0; i < stStringWins.size(); i ++)
        {
          int maxLines = stStringWins.at(i)->getNumLines();
          int maxCols = stStringWins.at(i)->getNumCols();
          getmaxyx(stStringWins.at(i)->getWindow(), maxLines, maxCols);
          const int startY = stStringWins.at(i)->getStartY();
          const int startX = stStringWins.at(i)->getStartX();

          if((mouseLine == startY) && ((mouseCol >= startX) &&
                                       (mouseCol < startX + maxCols)))
            {
              highlightWinNum = i;
            }
          else
            {
              highlightWinNum = -1;
            }

          if(highlightWinNum != -1)
            {
              break;
            }
        }
    }
} // end of "checkFileClick"



void refreshSFStringWins(const std::vector<CursesWindow*>& sfStringWins,
                         std::ofstream& log)
{
  for(int i = 0; i < sfStringWins.size(); i++)
    {
      if(sfStringWins.at(i)->getWindow() != nullptr)
        {
          wnoutrefresh(sfStringWins.at(i)->getWindow());
        }
    }
} // end of "refreshSFStringWins"



void refreshSTStringWins(const std::vector<CursesWindow*>& stStringWins,
                         std::ofstream& log)
{
  for(int i = 0; i < stStringWins.size(); i++)
    {
      if(stStringWins.at(i)->getWindow() != nullptr)
        {
          wnoutrefresh(stStringWins.at(i)->getWindow());
        }
    }
} // end of "refreshSFStringWins"



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



void clearSFStringWins(const std::vector<CursesWindow*>& sfStringWins)
{
  for(int i = 0; i < sfStringWins.size(); i++)
    {
      if(sfStringWins.at(i)->getWindow() != nullptr)
        {
          werase(sfStringWins.at(i)->getWindow());
        }
    }
} // end of "clearWins"




void clearSTStringWins(const std::vector<CursesWindow*>& stStringWins)
{
  for(int i = 0; i < stStringWins.size(); i++)
    {
      if(stStringWins.at(i)->getWindow() != nullptr)
        {
          werase(stStringWins.at(i)->getWindow());
        }
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
      wattron(it->second->getWindow(), COLOR_PAIR(_BLACK_TEXT));
      if((it->second->getWindowName() != "SAVEDFILE") &&
         (it->second->getWindowName() != "_PROMPTWIN")&&
         (it->second->getWindowName() != "_LARROWSAVEDFILESWIN") &&
         (it->second->getWindowName() != "_RARROWSAVEDFILESWIN") &&
         (it->second->getWindowName() != "_LARROWSAVEDTHEMESWIN") &&
         (it->second->getWindowName() != "_RARROWSAVEDTHEMESWIN"))
        {
          // if(val == '[')
          //   {
          //     val = 'A';
          //   }

          val++;

          if(it->second->getWindow() != nullptr)
            {
              box(it->second->getWindow(), ' ', ' ');
            }
      }
      wattron(it->second->getWindow(), COLOR_PAIR(_WHITE_TEXT));
    }
} // end of "drawBoxes"



void drawSFStringBoxes(const std::unordered_map<int, CursesWindow*>& wins,
                       const std::vector<CursesWindow*> & sfStringWins,
                       std::ofstream& log)
{
  char val = '.';

  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
    {
      for(int i = 0; i < sfStringWins.size(); i++)
        {
          if(sfStringWins.at(i)->getWindow() != nullptr)
            {
              box(sfStringWins.at(i)->getWindow(), val, val);
            }
        }
    }
} // end of "drawBoxes"



void drawSTStringBoxes(const std::unordered_map<int, CursesWindow*>& wins,
                       const std::vector<CursesWindow*> & stStringWins,
                       std::ofstream& log)
{
  char val = '.';


  if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      for(int i = 0; i < stStringWins.size(); i++)
        {
          if(stStringWins.at(i)->getWindow() != nullptr)
            {
              box(stStringWins.at(i)->getWindow(), val, val);
            }
        }
    }
} // end of "drawBoxes"
