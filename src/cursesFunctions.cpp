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
   mainWins                 - A reference to an unordered map <int, CursesWindow*>
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
void initializeStartingWindows(std::unordered_map<int, CursesWindow*>& mainWins)
{
  for(int i = _MAINWIN; i <= _SAVEDTHEMESWIN; i++)
    {
      CursesWindow* newWindow = new CursesWindow();
      mainWins.insert(std::make_pair(i, newWindow));
    }

  int numLines = 0;
  int numCols = 0;
  int startY = 0;
  int startX = 0;

  // _MAINWIN
  getmaxyx(stdscr, numLines, numCols);
  mainWins.at(_MAINWIN)->defineWindow(stdscr,
                                      "_MAINWIN",
                                      numLines,
                                      numCols,
                                      startY,
                                      startX);
  // _HELPWIN
  numLines = (mainWins.at(_MAINWIN)->getNumLines() / 2) - 3;
  numCols = 60;
  startY = 2;
  startX =  mainWins.at(_MAINWIN)->getNumCols() - numCols - 3;
  mainWins.at(_HELPWIN)->defineWindow(newwin(numLines,
                                             numCols,
                                             startY,
                                             startX),
                                      "_HELPWIN",
                                      numLines,
                                      numCols,
                                      startY,
                                      startX);
  // _PROGRAMSWIN
  numLines = (mainWins.at(_MAINWIN)->getNumLines() / 2) - 2;
  numCols = 60;
  startY = mainWins.at(_HELPWIN)->getNumLines() + 3;
  startX =  mainWins.at(_MAINWIN)->getNumCols() - numCols - 3;
  mainWins.at(_PROGRAMSWIN)->defineWindow(newwin(numLines,
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
  numCols = mainWins.at(_MAINWIN)->getNumCols() -
    mainWins.at(_HELPWIN)->getNumCols() - 8;
  startY = 2;
  startX = 3;
  mainWins.at(_PROMPTWIN)->defineWindow(newwin(numLines,
                                               numCols,
                                               startY,
                                               startX),
                                        "_PROMPTWIN",
                                        numLines,
                                        numCols,
                                        startY,
                                        startX);
  // _SAVEDFILESWIN
  numLines = ((mainWins.at(_MAINWIN)->getNumLines() -
               mainWins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  numCols = mainWins.at(_MAINWIN)->getNumCols() -
    mainWins.at(_HELPWIN)->getNumCols() - 8;
  startY = mainWins.at(_PROMPTWIN)->getStartY() +
    mainWins.at(_PROMPTWIN)->getNumLines() + 1;
  startX = 3;
  mainWins.at(_SAVEDFILESWIN)->defineWindow(newwin(numLines,
                                                   numCols,
                                                   startY,
                                                   startX),
                                            "_SAVEDFILESWIN",
                                            numLines,
                                            numCols,
                                            startY,
                                            startX);
  // _SAVEDTHEMESWIN
  numLines = ((mainWins.at(_MAINWIN)->getNumLines() -
               mainWins.at(_PROMPTWIN)->getNumLines()) / 2) - 3;
  numCols = mainWins.at(_MAINWIN)->getNumCols() -
    mainWins.at(_HELPWIN)->getNumCols() - 8;
  startY = mainWins.at(_SAVEDFILESWIN)->getStartY() +
    mainWins.at(_SAVEDFILESWIN)->getNumLines() + 1;
  startX = 3;
  mainWins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(numLines,
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
   refreshAllMainWins

  Description:
   Refreshes all CursesWindow objects member variables that point to a
   currently allocated WINDOW type (values that are not nullptr). They are
   sorted before refreshing to ensure the proper write order.

  Input/Output:
   mainWins                 - A reference to a const unordered map
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
void refreshAllMainWins(const std::unordered_map<int, CursesWindow*>& mainWins)
{
  std::unordered_map<int, CursesWindow*>::const_iterator it = mainWins.begin();
  std::vector<int> tempMainWins;

  // store all currently initialized window indexes
  for(it = mainWins.begin(); it != mainWins.end(); it++)
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
      wnoutrefresh(mainWins.at(*vecIt)->getWindow());
    }
} // end of "refreshAllMainWins"



/*
  Function:
   clearAllMainWins

  Description:
   Clears all currently active and defined CursesWindow object screens. All
   "erased" screens are stored in the screen buffer waiting for a call to
   refresh() to write the changes.

  Input/Output:
   NONE

  Input:
   mainWins             - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Output:
   NONE

  Returns:
   NONE
*/
void clearAllMainWins(const std::unordered_map<int, CursesWindow*>& mainWins)
{
  std::unordered_map<int, CursesWindow*>::const_iterator it;
  for(it = mainWins.begin(); it != mainWins.end(); it++)
    {
      werase(it->second->getWindow());
    }
} // end of "clearAllMainWins"



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
   mainWins             - A reference to a const unordered map
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
void updatePromptWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                               const int& numLines,
                               const int& numCols)
{
  if(mainWins.at(_PROMPTWIN)->getNumCols() + mainWins.at(_PROMPTWIN)->getStartX() > numCols ||
     mainWins.at(_PROMPTWIN)->getStartY() +  mainWins.at(_PROMPTWIN)->getNumLines() >= numLines)
    {
      mainWins.at(_PROMPTWIN)->deleteWindow();
      mainWins.at(_PROMPTWIN)->setWindow(nullptr);
    }
  else
    {
      if(mainWins.at(_PROMPTWIN)->getWindow() == nullptr)
        {
          mainWins.at(_PROMPTWIN)->defineWindow(newwin(mainWins.at(_PROMPTWIN)->getNumLines(),
                                                   mainWins.at(_PROMPTWIN)->getNumCols(),
                                                   mainWins.at(_PROMPTWIN)->getStartY(),
                                                   mainWins.at(_PROMPTWIN)->getStartX()),
                                            mainWins.at(_PROMPTWIN)->getWindowName(),
                                            mainWins.at(_PROMPTWIN)->getNumLines(),
                                            mainWins.at(_PROMPTWIN)->getNumCols(),
                                            mainWins.at(_PROMPTWIN)->getStartY(),
                                            mainWins.at(_PROMPTWIN)->getStartX());
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
   mainWins             - A reference to a const unordered map
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
void updateHelpWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                               const int& numLines,
                               const int& numCols)
{
  if(mainWins.at(_HELPWIN)->getNumCols() + mainWins.at(_HELPWIN)->getStartX() > numCols ||
     mainWins.at(_HELPWIN)->getStartY() + mainWins.at(_HELPWIN)->getNumLines() >= numLines)
    {
      mainWins.at(_HELPWIN)->deleteWindow();
      mainWins.at(_HELPWIN)->setWindow(nullptr);
    }
  else
    {
      if(mainWins.at(_HELPWIN)->getWindow() == nullptr)
        {
          mainWins.at(_HELPWIN)->defineWindow(newwin(mainWins.at(_HELPWIN)->getNumLines(),
                                                   mainWins.at(_HELPWIN)->getNumCols(),
                                                   mainWins.at(_HELPWIN)->getStartY(),
                                                   mainWins.at(_HELPWIN)->getStartX()),
                                            mainWins.at(_HELPWIN)->getWindowName(),
                                            mainWins.at(_HELPWIN)->getNumLines(),
                                            mainWins.at(_HELPWIN)->getNumCols(),
                                            mainWins.at(_HELPWIN)->getStartY(),
                                            mainWins.at(_HELPWIN)->getStartX());
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
   mainWins             - A reference to a const unordered map
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
void updateProgramsWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                                 const int& numLines,
                                 const int& numCols)
{
  if(mainWins.at(_PROGRAMSWIN)->getNumCols() + mainWins.at(_PROGRAMSWIN)->getStartX() > numCols ||
     mainWins.at(_PROGRAMSWIN)->getStartY() + mainWins.at(_PROGRAMSWIN)->getNumLines() >= numLines)
    {
      mainWins.at(_PROGRAMSWIN)->deleteWindow();
      mainWins.at(_PROGRAMSWIN)->setWindow(nullptr);
    }
  else
    {
      if(mainWins.at(_PROGRAMSWIN)->getWindow() == nullptr)
        {
          mainWins.at(_PROGRAMSWIN)->defineWindow(newwin(mainWins.at(_PROGRAMSWIN)->getNumLines(),
                                                   mainWins.at(_PROGRAMSWIN)->getNumCols(),
                                                   mainWins.at(_PROGRAMSWIN)->getStartY(),
                                                   mainWins.at(_PROGRAMSWIN)->getStartX()),
                                            mainWins.at(_PROGRAMSWIN)->getWindowName(),
                                            mainWins.at(_PROGRAMSWIN)->getNumLines(),
                                            mainWins.at(_PROGRAMSWIN)->getNumCols(),
                                            mainWins.at(_PROGRAMSWIN)->getStartY(),
                                            mainWins.at(_PROGRAMSWIN)->getStartX());
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
   mainWins             - A reference to a const unordered map
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
void updateSavedFilesWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                                   const int& numLines,
                                   const int& numCols)
{
  if(mainWins.at(_SAVEDFILESWIN)->getNumCols() + mainWins.at(_SAVEDFILESWIN)->getStartX() > numCols ||
     mainWins.at(_SAVEDFILESWIN)->getStartY() + mainWins.at(_SAVEDFILESWIN)->getNumLines() >= numLines)
    {
      mainWins.at(_SAVEDFILESWIN)->deleteWindow();
      mainWins.at(_SAVEDFILESWIN)->setWindow(nullptr);
    }
  else
    {
      if(mainWins.at(_SAVEDFILESWIN)->getWindow() == nullptr)
        {
          mainWins.at(_SAVEDFILESWIN)->defineWindow(newwin(mainWins.at(_SAVEDFILESWIN)->getNumLines(),
                                                   mainWins.at(_SAVEDFILESWIN)->getNumCols(),
                                                   mainWins.at(_SAVEDFILESWIN)->getStartY(),
                                                   mainWins.at(_SAVEDFILESWIN)->getStartX()),
                                            mainWins.at(_SAVEDFILESWIN)->getWindowName(),
                                            mainWins.at(_SAVEDFILESWIN)->getNumLines(),
                                            mainWins.at(_SAVEDFILESWIN)->getNumCols(),
                                            mainWins.at(_SAVEDFILESWIN)->getStartY(),
                                            mainWins.at(_SAVEDFILESWIN)->getStartX());
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
   mainWins             - A reference to a const unordered map
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
void updateSavedThemesWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins,
                                    const int& numLines,
                                    const int& numCols)
{
  if(mainWins.at(_SAVEDTHEMESWIN)->getNumCols() + mainWins.at(_SAVEDTHEMESWIN)->getStartX() > numCols ||
     mainWins.at(_SAVEDTHEMESWIN)->getStartY() + mainWins.at(_SAVEDTHEMESWIN)->getNumLines() >= numLines)
    {
      mainWins.at(_SAVEDTHEMESWIN)->deleteWindow();
      mainWins.at(_SAVEDTHEMESWIN)->setWindow(nullptr);
    }
  else
    {
      if(mainWins.at(_SAVEDTHEMESWIN)->getWindow() == nullptr)
        {
          mainWins.at(_SAVEDTHEMESWIN)->defineWindow(newwin(mainWins.at(_SAVEDTHEMESWIN)->getNumLines(),
                                                   mainWins.at(_SAVEDTHEMESWIN)->getNumCols(),
                                                   mainWins.at(_SAVEDTHEMESWIN)->getStartY(),
                                                   mainWins.at(_SAVEDTHEMESWIN)->getStartX()),
                                            mainWins.at(_SAVEDTHEMESWIN)->getWindowName(),
                                            mainWins.at(_SAVEDTHEMESWIN)->getNumLines(),
                                            mainWins.at(_SAVEDTHEMESWIN)->getNumCols(),
                                            mainWins.at(_SAVEDTHEMESWIN)->getStartY(),
                                            mainWins.at(_SAVEDTHEMESWIN)->getStartX());
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
   mainWins             - A reference to a const unordered map
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
void updateWinDimensions(const std::unordered_map<int, CursesWindow*>& mainWins)
{
  int numLines = 0;
  int numCols = 0;

  getmaxyx(stdscr, numLines, numCols);
  mainWins.at(_MAINWIN)->setNumLines(numLines);
  mainWins.at(_MAINWIN)->setNumCols(numCols);
  updatePromptWinDimensions(mainWins,
                            numLines,
                            numCols);
  updateHelpWinDimensions(mainWins,
                          numLines,
                          numCols);
  updateSavedFilesWinDimensions(mainWins,
                                numLines,
                                numCols);
  updateProgramsWinDimensions(mainWins,
                              numLines,
                              numCols);
  updateSavedThemesWinDimensions(mainWins,
                                 numLines,
                                 numCols);
  refreshAllMainWins(mainWins);
} // end of "updateWinDimensions"



/*
  Function:
   drawBoxes

  Description:
   Draws a box for every "WINDOW" that is currently initialized and stored
   in the "mainWins" object.

  Input/Output:
   mainWins             - A reference to a const unordered map
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
void drawBoxes(const std::unordered_map<int, CursesWindow*>& mainWins)
{
  char val = 'A';
  std::unordered_map<int, CursesWindow*>::const_iterator it;

  for(it = mainWins.begin(); it != mainWins.end(); it++)
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
