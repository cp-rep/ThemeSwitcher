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
   initializeStartingWindows

  Description:
   This function creates and initializes all the necessary startup windows via
   dynamic allocation and stores them in an unordered_map for later use.

  Input/Output:
   NONE

  Input:
   NONE

  Output:
   wins                 - A reference to an unordered map <int, CursesWindow*>
                          object type that will be used to store each
                          CursesWindow object initialized in this function.  The
                          keys are from _cursesWinConsts.hpp and match the
                          corresponding CursesWindow objects they are pointing
                          to.
  Returns:
   NONE
*/
void initializeStartingWindows(std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _MAINWIN; i <= _SAVEDTHEMESWIN; i++)
    {
      CursesWindow* newWindow = new CursesWindow();
      wins.insert(std::make_pair(i, newWindow));
    }

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
  numCols = 60;
  startY = 2;
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
  numCols = 60;
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
  numLines = 6;
  numCols = wins.at(_MAINWIN)->getNumCols() -
    wins.at(_HELPWIN)->getNumCols() - 8;
  startY = 2;
  startX = 3;
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
  startX = 3;
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
  startX = 3;
  wins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(numLines,
                                                numCols,
                                                startY,
                                                startX),
                                         "_SAVEDTHEMESWIN",
                                         numLines,
                                         numCols,
                                         startY,
                                         startX);

} // end of "initializeStartingWindows"



/*
  Function:
   refreshAllWins

  Description:
   Refreshes all CursesWindow objects member variables that point to a
   currently allocated WINDOW type (values that are not nullptr). They are
   sorted before refreshing to ensure the proper write order.

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
void refreshAllWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::unordered_map<int, CursesWindow*>::const_iterator it = wins.begin();
  std::vector<int> tempWins;

  // store all currently initialized window indexes
  for(it = wins.begin(); it != wins.end(); it++)
    {
      if(it->second->getWindow() != nullptr)
        {
          tempWins.push_back(it->first);
        }
    }

  // sort them in ascending order
  std::sort(tempWins.begin(), tempWins.end());

  // refresh the initialized windows
  for(std::vector<int>::iterator vecIt = tempWins.begin();
      vecIt != tempWins.end();
      vecIt++)
    {
      wnoutrefresh(wins.at(*vecIt)->getWindow());
    }
} // end of "refreshAllWins"



/*
  Function:
   clearAllWins

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
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins)
{
  std::unordered_map<int, CursesWindow*>::const_iterator it;
  for(it = wins.begin(); it != wins.end(); it++)
    {
      werase(it->second->getWindow());
    }
} // end of "clearAllWins"



/*
  Function:
   updatePromptWinDimensions

  Description:
   Determines the current screen size of the standard screen and deletes or
   creates top windows dependent on those values.  For example, if the
   current screen size is too small to fit the contents any window being
   checked, that specific window will delete itself until otherwise.

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
void updatePromptWinDimensions(const std::unordered_map<int, CursesWindow*>& wins,
                               const int& numLines,
                               const int& numCols,
                               const int& startY,
                               const int& startX)
{

} // end of "updatePromptWinDimensions"



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
  int numLines;
  int numCols;
  int startY;
  int startX;

  getmaxyx(stdscr, numLines, numCols);
  wins.at(_MAINWIN)->setNumLines(numLines);
  wins.at(_MAINWIN)->setNumCols(numCols);
  updatePromptWinDimensions(wins,
                            numLines,
                            numCols,
                            startY,
                            startX);

  refreshAllWins(wins);
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
