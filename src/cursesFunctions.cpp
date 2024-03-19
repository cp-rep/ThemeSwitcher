/*
  File:
   cursesFunctions.cpp

  Description:
   Function implementations for the cursesFunctions.hpp header file.
*/
#include <algorithm>
#include <vector>
#include "cursesFunctions.hpp"



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
void initializeWins(std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _MAINWIN; i <= _SAVEDTHEMESWIN; i++)
    {
      CursesWindow* newWindow = new CursesWindow();
      wins.insert(std::make_pair(i, newWindow));
    }
} // end of "initializeWins"



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
  const int colOffset = 7;
  const int lineOffset = 3;
  int numLines = _PROMPTWINMAXLINES;
  int numCols = _PROMPTWINMAXCOLS;
  int startY = _PROMPTWINSTARTY;
  int startX = _PROMPTWINSTARTX;
  bool define = false;

  // check if the current total columns and lines will fit desired win dimensions
  if( ((_PROMPTWINMAXCOLS < maxCols - colOffset) ||
       (_PROMPTWINMINCOLS < maxCols - colOffset)) &&
      (_PROMPTWINMAXLINES < maxLines - lineOffset))
    {
      define = true;

      // make sure not to set size bigger than the maximum for that window
      if(_PROMPTWINMAXCOLS + colOffset < maxCols)
        {
          numCols = _PROMPTWINMAXCOLS;
        }
      // else, the size is somewhere between the min and max
      else
        {
          numCols = maxCols - colOffset;
        }
    }
  // program was opened in too small of window. update to the minimum size for
  // when resize is in correct parameters
  else
    {
      numCols = _PROMPTWINMINCOLS;
    }

  // the window is within desired dimensions. allocate it
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
                         const int& maxCols)
{
  const int colOffset = 7;
  const int lineOffset = 15;

  int maxFileLines = (maxLines - _SAVEDFILESWINSTARTY) / 2;
  int numLines = (maxLines - _SAVEDFILESWINSTARTY) / 2;
  int numCols = _SAVEDFILESWINMAXCOLS;
  int startY = _SAVEDFILESWINSTARTY;
  int startX = _SAVEDFILESWINSTARTX;
  bool colsCheck = false;
  bool linesCheck = false;

  // check if the current total columns and lines will fit desired win dimensions
  if( ((_SAVEDFILESWINMAXCOLS < maxCols - colOffset) ||
       (_SAVEDFILESWINMINCOLS < maxCols - colOffset)))
    {
      colsCheck= true;

      // make sure not to set size bigger than the maximum for that window
      if(_SAVEDFILESWINMAXCOLS + colOffset < maxCols)
        {
          numCols = _SAVEDFILESWINMAXCOLS;
        }
      // else, the size is somewhere between the min and max
      else
        {
          numCols = maxCols - colOffset;

        }
    }

  if((_SAVEDFILESWINMINLINES < maxFileLines) &&
      (_SAVEDFILESWINMINLINES < maxFileLines))

    {
      linesCheck= true;
      numLines = ((maxLines - _SAVEDFILESWINSTARTY) / 2) - 3;
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

      // create the new window
      wins.at(_SAVEDFILESWIN)->defineWindow(newwin(numLines,
                                               numCols,
                                               startY,
                                               startX),
                                        "_SAVEDFILESWIN",
                                        numLines,
                                        numCols,
                                        startY,
                                        startX);
    }
  // the window has been resized to a bad dimension. delete it
  else
    {
      if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
        {
          wins.at(_SAVEDFILESWIN)->deleteWindow();
          wins.at(_SAVEDFILESWIN)->setWindow(nullptr);
        }
    }
} // end of "defineSavedFilesWin"



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
  const int colOffset = 7;
  const int lineOffset = 15;

  int maxFileLines = (maxLines - _SAVEDFILESWINSTARTY) / 2;
  int numLines = (maxLines - _SAVEDFILESWINSTARTY) / 2;
  int numCols = _SAVEDTHEMESWINMAXCOLS;
  int startY = _SAVEDTHEMESWINSTARTY;
  int startX = _SAVEDTHEMESWINSTARTX;
  bool colsCheck = false;
  bool linesCheck = false;

  // check if the current total columns and lines will fit desired win dimensions
  if( ((_SAVEDTHEMESWINMAXCOLS < maxCols - colOffset) ||
       (_SAVEDTHEMESWINMINCOLS < maxCols - colOffset)) )
    {
      colsCheck= true;

      // make sure not to set size bigger than the maximum for that window
      if(_SAVEDTHEMESWINMAXCOLS + colOffset < maxCols)
        {
          numCols = _SAVEDTHEMESWINMAXCOLS;
        }
      // else, the size is somewhere between the min and max
      else
        {
          numCols = maxCols - colOffset;
        }
    }

  if((_SAVEDTHEMESWINMINLINES < maxFileLines) &&
     (_SAVEDTHEMESWINMINLINES < maxFileLines))

    {
      linesCheck= true;
      numLines = ((maxLines - _SAVEDFILESWINSTARTY) / 2) - 3;
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
      if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
        {
          wins.at(_SAVEDTHEMESWIN)->deleteWindow();
          wins.at(_SAVEDTHEMESWIN)->setWindow(nullptr);
        }
    }
} // end of "defineSavedThemesWin"



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
void defineWins(std::unordered_map<int, CursesWindow*>& wins)
{
  int numLines = 0;
  int numCols = 0;
  int startY = 0;
  int startX = 0;

  // _MAINWIN
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
                      numCols);
  defineSavedThemesWin(wins,
                       numLines,
                       numCols);


  // // _HELPWIN
  // numLines = (wins.at(_MAINWIN)->getNumLines() / 2) - 3;
  // numCols = _HELPWINSTARTCOLS;
  // startY = _HELPWINSTARTY;
  // startX =  wins.at(_MAINWIN)->getNumCols() - numCols - 3;
  // wins.at(_HELPWIN)->defineWindow(newwin(numLines,
  //                                            numCols,
  //                                            startY,
  //                                            startX),
  //                                     "_HELPWIN",
  //                                     numLines,
  //                                     numCols,
  //                                     startY,
  //                                     startX);
  // // _PROGRAMSWIN
  // numLines = (wins.at(_MAINWIN)->getNumLines() / 2) - 2;
  // numCols = _PROGRAMSWINSTARTCOLS;
  // startY = wins.at(_HELPWIN)->getNumLines() + 3;
  // startX =  wins.at(_MAINWIN)->getNumCols() - numCols - 3;
  // wins.at(_PROGRAMSWIN)->defineWindow(newwin(numLines,
  //                                                numCols,
  //                                                startY,
  //                                                startX),
  //                                         "_PROGRAMSWIN",
  //                                         numLines,
  //                                         numCols,
  //                                         startY,
  //                                         startX);
  // // _PROMPTWIN
  // numLines = _PROMPTWINMINLINES;
  // numCols = wins.at(_MAINWIN)->getNumCols() -
  //   wins.at(_HELPWIN)->getNumCols() - 8;
  // startY = _PROMPTWINSTARTY;
  // startX = _PROMPTWINSTARTX;
  // wins.at(_PROMPTWIN)->defineWindow(newwin(numLines,
  //                                              numCols,
  //                                              startY,
  //                                              startX),
  //                                       "_PROMPTWIN",
  //                                       numLines,
  //                                       numCols,
  //                                       startY,
  //                                       startX);
  // // _SAVEDFILESWIN
  // numLines = ((wins.at(_MAINWIN)->getNumLines() -
  //              wins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  // numCols = wins.at(_MAINWIN)->getNumCols() -
  //   wins.at(_HELPWIN)->getNumCols() - 8;
  // startY = wins.at(_PROMPTWIN)->getStartY() +
  //   wins.at(_PROMPTWIN)->getNumLines() + 1;
  // startX = _SAVEDFILESWINSTARTX;
  // wins.at(_SAVEDFILESWIN)->defineWindow(newwin(numLines,
  //                                                  numCols,
  //                                                  startY,
  //                                                  startX),
  //                                           "_SAVEDFILESWIN",
  //                                           numLines,
  //                                           numCols,
  //                                           startY,
  //                                           startX);
  // // _SAVEDTHEMESWIN
  // numLines = ((wins.at(_MAINWIN)->getNumLines() -
  //              wins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  // numCols = wins.at(_MAINWIN)->getNumCols() -
  //   wins.at(_HELPWIN)->getNumCols() - 8;
  // startY = wins.at(_SAVEDFILESWIN)->getStartY() +
  //   wins.at(_SAVEDFILESWIN)->getNumLines() + 1;
  // startX = _SAVEDTHEMESWINSTARTX;
  // wins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(numLines,
  //                                                   numCols,
  //                                                   startY,
  //                                                   startX),
  //                                            "_SAVEDTHEMESWIN",
  //                                            numLines,
  //                                            numCols,
  //                                            startY,
  //                                            startX);
} // end of "defineWins"



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
  std::unordered_map<int, CursesWindow*>::const_iterator it = wins.begin();
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
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins)
{
  char val = 'A';
  std::unordered_map<int, CursesWindow*>::const_iterator it;

  for(it = wins.begin(); it != wins.end(); it++)
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
} // end of "drawBoxes"
