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
void initializeWins(std::unordered_map<int, CursesWindow*>& wins)
{
  for(int i = _MAINWIN; i <= _HELPWIN; i++)
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
  log << "startY: " << startY << std::endl;
//  int startY = wins.at(_SAVEDFILESWIN)->getStartY();
//  int startX = wins.at(_SAVEDFILESWIN)->getStartY();
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
      wins.at(_SAVEDFILESWIN)->setStartX(startX);
      wins.at(_SAVEDFILESWIN)->setStartY(startY);

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
  defineSavedThemesWin(wins,
                       numLines,
                       numCols);
  defineHelpWin(wins,
                numLines,
                numCols);
} // end of "defineWins"



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
void printNumberedStrings(const std::unordered_map<int, CursesWindow*>& wins,
                          const int win,
                          const std::vector<std::string>& fileStrings,
                          const std::vector<std::string>& themeStrings,
                          const int& lineMaxOffset,
                          const int& colMaxOffset,
                          const int& lineMinOffset,
                          const int& colMinOffset,
                          const int& mouseLine,
                          const int& mouseCol,
                          const int& numToPrint,
                          std::ofstream& log)
{
  if(wins.at(win)->getWindow() != nullptr)
    {
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(win)->getWindow(),
               maxWinLines,
               maxWinCols);

      std::string fileString;
      std::string themeString;
      std::string fileCount;
      std::string tempString;
      int maxPossible = maxWinCols - colMaxOffset - 3;

      // print list of the saved files
      for(int i = 0; i < numToPrint; i++)
        {
          tempString.clear();
          fileCount = intToStr(i + 1);
          fileCount.append(". ");
          fileString = fileStrings.at(i);
          themeString = themeStrings.at(i);
          maxPossible = maxWinCols - colMaxOffset - 6; // extension

          // enter if the filestring + the theme string wont fit in the window
          if( (fileString.length() + fileCount.length() + themeString.length())
              >= maxPossible)
            {
              int difference = (fileString.length() + fileCount.length() +
                                themeString.length()) - maxPossible;
              tempString = "...";

              for(int j = difference; j < fileString.length(); j++)
                {
                  char c = fileString.at(j);
                  tempString.push_back(c);
                }

              tempString.append("...");
              tempString.append(themeString);
              fileString = tempString;
            }
          // there was room for the strings. print dots between them
          else
            {
              int dots = fileCount.length() + fileString.length();

              while(dots < maxWinCols - colMaxOffset - themeString.length())
                {
                  fileString.push_back('.');
                  dots++;
                }

              fileString.append(themeString);
            }

          // do not print if the string count exceeds the acceptable printing range
          if(i + lineMinOffset >= maxWinLines - lineMaxOffset)
            {
              break;
            }
          else
            {
              mvwaddstr(wins.at(win)->getWindow(),
                        i + lineMinOffset + 2,
                        colMinOffset,
                        fileCount.c_str());

              // check if incoming mouse coordinates are on a file line
              if((mouseLine - wins.at(win)->getStartY()) ==
                 (i + lineMinOffset + 2))
                {
                  wattron(wins.at(win)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
                }

              mvwaddstr(wins.at(win)->getWindow(),
                        i + lineMinOffset + 2,
                        colMinOffset + fileCount.length(),
                        fileString.c_str());
              wattron(wins.at(win)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
            }
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
void printSavedFilesWin(const std::unordered_map<int, CursesWindow*>& wins,
                        const std::vector<std::string>& savedFilesStrings,
                        const std::vector<std::string>& currThemesStrings,
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

      outString = sfTitle;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + lineMinOffset,
                colMinOffset,
                outString.c_str());
      outString = sfThemeTitle;
      printColPosition = maxWinCols - outString.length() - colMinOffset;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + lineMinOffset,
                maxWinCols - outString.length() - colMinOffset,
                outString.c_str());
      printNumberedStrings(wins,
                           _SAVEDFILESWIN,
                           savedFilesStrings,
                           currThemesStrings,
                           lineMaxOffset,
                           colMaxOffset,
                           lineMinOffset,
                           colMinOffset,
                           mouseLine,
                           mouseCol,
                           savedFilesStrings.size(),
                           log);
    }
} // end of "printSavedFilesWin"



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
   NONE
*/
void printSavedThemesWin(const std::unordered_map<int, CursesWindow*>& wins,
                         const std::vector<std::string>& savedThemesStrings,
                         const int& mouseLine,
                         const int& mouseCol,
                         std::ofstream& log)
{
  const int maxStringSize = 31;
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
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
  int i = 0;
  for(it = wins.begin(); it != wins.end(); it++, i++)
    {
      if(i == 3)
        {

          continue;
        }

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
