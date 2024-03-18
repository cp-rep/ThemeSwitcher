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
  // _HELPWIN
  numLines = (wins.at(_MAINWIN)->getNumLines() / 2) - 3;
  numCols = _HELPWINSTARTCOLS;
  startY = _HELPWINSTARTY;
  startX =  wins.at(_MAINWIN)->getNumCols() - numCols - 3;
  wins.at(_HELPWIN)->defineWindow(newwin(numLines,
                                             numCols,
                                             startY,
                                             startX),
                                      "_HELPWIN",
                                      numLines,
                                      numCols,
                                      startY,
                                      startX);
  // _PROGRAMSWIN
  numLines = (wins.at(_MAINWIN)->getNumLines() / 2) - 2;
  numCols = _PROGRAMSWINSTARTCOLS;
  startY = wins.at(_HELPWIN)->getNumLines() + 3;
  startX =  wins.at(_MAINWIN)->getNumCols() - numCols - 3;
  wins.at(_PROGRAMSWIN)->defineWindow(newwin(numLines,
                                                 numCols,
                                                 startY,
                                                 startX),
                                          "_PROGRAMSWIN",
                                          numLines,
                                          numCols,
                                          startY,
                                          startX);
  // _PROMPTWIN
  numLines = _PROMPTWINMINLINES;
  numCols = wins.at(_MAINWIN)->getNumCols() -
    wins.at(_HELPWIN)->getNumCols() - 8;
  startY = _PROMPTWINSTARTY;
  startX = _PROMPTWINSTARTX;
  wins.at(_PROMPTWIN)->defineWindow(newwin(numLines,
                                               numCols,
                                               startY,
                                               startX),
                                        "_PROMPTWIN",
                                        numLines,
                                        numCols,
                                        startY,
                                        startX);
  // _SAVEDFILESWIN
  numLines = ((wins.at(_MAINWIN)->getNumLines() -
               wins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  numCols = wins.at(_MAINWIN)->getNumCols() -
    wins.at(_HELPWIN)->getNumCols() - 8;
  startY = wins.at(_PROMPTWIN)->getStartY() +
    wins.at(_PROMPTWIN)->getNumLines() + 1;
  startX = _SAVEDFILESWINSTARTX;
  wins.at(_SAVEDFILESWIN)->defineWindow(newwin(numLines,
                                                   numCols,
                                                   startY,
                                                   startX),
                                            "_SAVEDFILESWIN",
                                            numLines,
                                            numCols,
                                            startY,
                                            startX);
  // _SAVEDTHEMESWIN
  numLines = ((wins.at(_MAINWIN)->getNumLines() -
               wins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  numCols = wins.at(_MAINWIN)->getNumCols() -
    wins.at(_HELPWIN)->getNumCols() - 8;
  startY = wins.at(_SAVEDFILESWIN)->getStartY() +
    wins.at(_SAVEDFILESWIN)->getNumLines() + 1;
  startX = _SAVEDTHEMESWINSTARTX;
  wins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(numLines,
                                                    numCols,
                                                    startY,
                                                    startX),
                                             "_SAVEDTHEMESWIN",
                                             numLines,
                                             numCols,
                                             startY,
                                             startX);
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
   updatePromptWinDimensions

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
void updatePromptWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                               const int& numLines,
                               const int& numCols)
{
  const int promptWinCols = wins.at(_PROMPTWIN)->getNumCols();
  const int promptWinLines = wins.at(_PROMPTWIN)->getNumLines();
  const int promptWinStartX = wins.at(_PROMPTWIN)->getStartX();
  const int promptWinStartY = wins.at(_PROMPTWIN)->getStartY();


  if(promptWinCols + promptWinStartX > numCols ||
     promptWinStartY + promptWinLines >= numLines)
    {
      wins.at(_HELPWIN)->deleteWindow();
      wins.at(_HELPWIN)->setWindow(nullptr);
    }
  else
    {
      if(wins.at(_HELPWIN)->getWindow() == nullptr)
        {
          wins.at(_HELPWIN)->defineWindow(newwin(promptWinLines,
                                                 promptWinCols,
                                                 promptWinStartY,
                                                 promptWinStartX),
                                          wins.at(_HELPWIN)->getWindowName(),
                                          promptWinLines,
                                          promptWinCols,
                                          promptWinStartY,
                                          promptWinStartX);
        }
    }
} // end of "updatePromptWinDimensions"



/*
  Function:
   updateHelpWinWinDimensions

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
void updateHelpWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                               const int& numLines,
                               const int& numCols)
{
  const int helpWinCols = wins.at(_HELPWIN)->getNumCols();
  const int helpWinLines = wins.at(_HELPWIN)->getNumLines();
  const int helpWinStartX = wins.at(_HELPWIN)->getStartX();
  const int helpWinStartY = wins.at(_HELPWIN)->getStartY();

  if(helpWinCols + helpWinStartX > numCols ||
     helpWinStartY + helpWinLines >= numLines)
    {
      wins.at(_HELPWIN)->deleteWindow();
      wins.at(_HELPWIN)->setWindow(nullptr);
    }
  else
    {
      if(wins.at(_HELPWIN)->getWindow() == nullptr)
        {
          wins.at(_HELPWIN)->defineWindow(newwin(helpWinLines,
                                                 helpWinCols,
                                                 helpWinStartY,
                                                 helpWinStartX),
                                          wins.at(_HELPWIN)->getWindowName(),
                                          helpWinLines,
                                          helpWinCols,
                                          helpWinStartY,
                                          helpWinStartX);
        }
    }
} // end of "updateHelpWinWinDimensions"



/*
  Function:
   updateProgramsWinDimensions

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
void updateProgramsWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                                 const int& numLines,
                                 const int& numCols)
{
  const int programsWinCols = wins.at(_PROGRAMSWIN)->getNumCols();
  const int programsWinLines = wins.at(_PROGRAMSWIN)->getNumLines();
  const int programsWinStartX = wins.at(_PROGRAMSWIN)->getStartX();
  const int programsWinStartY = wins.at(_PROGRAMSWIN)->getStartY();

  if(programsWinCols + programsWinStartX > numCols ||
     programsWinStartY + programsWinLines >= numLines)
    {
      wins.at(_PROGRAMSWIN)->deleteWindow();
      wins.at(_PROGRAMSWIN)->setWindow(nullptr);
    }
  else
    {
      if(wins.at(_PROGRAMSWIN)->getWindow() == nullptr)
        {
          wins.at(_PROGRAMSWIN)->defineWindow(newwin(programsWinLines,
                                                     programsWinCols,
                                                     programsWinStartY,
                                                     programsWinStartX),
                                              wins.at(_PROGRAMSWIN)->getWindowName(),
                                              programsWinLines,
                                              programsWinCols,
                                              programsWinStartY,
                                              programsWinStartX);
        }
    }
} // end of "updateProgramsWinDimensions"



/*
  Function:
   updateSavedFilesWinDimensions

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
void updateSavedFilesWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                                   const int& numLines,
                                   const int& numCols)
{
  if(wins.at(_SAVEDFILESWIN)->getNumCols() + wins.at(_SAVEDFILESWIN)->getStartX() > numCols ||
     wins.at(_SAVEDFILESWIN)->getStartY() + wins.at(_SAVEDFILESWIN)->getNumLines() >= numLines)
    {
      wins.at(_SAVEDFILESWIN)->deleteWindow();
      wins.at(_SAVEDFILESWIN)->setWindow(nullptr);
    }
  else
    {
      if(wins.at(_SAVEDFILESWIN)->getWindow() == nullptr)
        {
          wins.at(_SAVEDFILESWIN)->defineWindow(newwin(wins.at(_SAVEDFILESWIN)->getNumLines(),
                                                   wins.at(_SAVEDFILESWIN)->getNumCols(),
                                                   wins.at(_SAVEDFILESWIN)->getStartY(),
                                                   wins.at(_SAVEDFILESWIN)->getStartX()),
                                            wins.at(_SAVEDFILESWIN)->getWindowName(),
                                            wins.at(_SAVEDFILESWIN)->getNumLines(),
                                            wins.at(_SAVEDFILESWIN)->getNumCols(),
                                            wins.at(_SAVEDFILESWIN)->getStartY(),
                                            wins.at(_SAVEDFILESWIN)->getStartX());
        }
    }
} // end of "updateSavedFilesWinDimensions"



/*
  Function:
   updateSavedThemesWinDimensions

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
void updateSavedThemesWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                                    const int& numLines,
                                    const int& numCols)
{
  if(wins.at(_SAVEDTHEMESWIN)->getNumCols() + wins.at(_SAVEDTHEMESWIN)->getStartX() > numCols ||
     wins.at(_SAVEDTHEMESWIN)->getStartY() + wins.at(_SAVEDTHEMESWIN)->getNumLines() >= numLines)
    {
      wins.at(_SAVEDTHEMESWIN)->deleteWindow();
      wins.at(_SAVEDTHEMESWIN)->setWindow(nullptr);
    }
  else
    {
      if(wins.at(_SAVEDTHEMESWIN)->getWindow() == nullptr)
        {
          wins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(wins.at(_SAVEDTHEMESWIN)->getNumLines(),
                                                   wins.at(_SAVEDTHEMESWIN)->getNumCols(),
                                                   wins.at(_SAVEDTHEMESWIN)->getStartY(),
                                                   wins.at(_SAVEDTHEMESWIN)->getStartX()),
                                            wins.at(_SAVEDTHEMESWIN)->getWindowName(),
                                            wins.at(_SAVEDTHEMESWIN)->getNumLines(),
                                            wins.at(_SAVEDTHEMESWIN)->getNumCols(),
                                            wins.at(_SAVEDTHEMESWIN)->getStartY(),
                                            wins.at(_SAVEDTHEMESWIN)->getStartX());
        }
    }
} // end of "updateSavedThemesWinDimensions"



/*
  Function:
   updateWinDimensions

  Description:
   A major function that gets the current dimensions of the standard screen
   and determines if any allocated window fits within those dimensions. Minor
   functions are called to assist with this determination.

  Input/Output:
   wins                 - A reference to a const unordered map
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
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& wins)
{
  int numLines = 0;
  int numCols = 0;

  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);
  updatePromptWinDimensions(wins,
                            numLines,
                            numCols);
  updateHelpWinDimensions(wins,
                          numLines,
                          numCols);
  updateSavedFilesWinDimensions(wins,
                                numLines,
                                numCols);
  updateProgramsWinDimensions(wins,
                              numLines,
                              numCols);
  updateSavedThemesWinDimensions(wins,
                                 numLines,
                                 numCols);
  refreshWins(wins);
} // end of "updateWinDimensions"



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
