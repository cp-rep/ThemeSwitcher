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
   checkButtonClick

  Description:
   Prints the incoming "win" to STDSCR representing a click on a "button".

  Input/Output:
   wins                 - A reference to a const unordered map
                          <int, CursesWindow*> type that contains pointers
                          to all currently allocated CursesWindow objects
                          that can be indexed by key values in the file
                          _cursesWinConsts.hpp.
  Input:
   win                  - a const integer containing a value representing a window
                          from _cursesWinConsts.hpp that should be for an "button"
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
int checkButtonClick(std::unordered_map<int, CursesWindow*>& wins,
                     const int& mouseLine,
                     const int& mouseCol,
                     std::ofstream& log)
{
  int buttonNum = -1;
  if(wins.at(_MAINWIN)->getWindow() == nullptr ||
     wins.at(_SAVEDFILESWIN)->getWindow() == nullptr ||
     wins.at(_SAVEDTHEMESWIN)->getWindow() == nullptr ||
     wins.at(_HELPWIN)->getWindow() == nullptr)
    {
      return buttonNum;
    }

  // check if click is in _SAVEDFILESWIN
  if((mouseLine >= wins.at(_SAVEDFILESWIN)->getStartY()) &&
     (mouseLine < wins.at(_SAVEDFILESWIN)->getStartY() +
      wins.at(_SAVEDFILESWIN)->getNumLines()) &&
     (mouseCol >= wins.at(_SAVEDFILESWIN)->getStartX() &&
      mouseCol < wins.at(_SAVEDFILESWIN)->getStartX() +
      wins.at(_SAVEDFILESWIN)->getNumCols()))
    {
      if((mouseLine == wins.at(_LARROWSAVEDFILESWIN)->getStartY()) &&
         (mouseCol >= wins.at(_LARROWSAVEDFILESWIN)->getStartX() &&
          mouseCol < wins.at(_LARROWSAVEDFILESWIN)->getStartX() +
          wins.at(_LARROWSAVEDFILESWIN)->getNumCols()))
        {
          buttonNum = _LARROWSAVEDFILESWIN;
        }
      else if((mouseLine == wins.at(_RARROWSAVEDFILESWIN)->getStartY()) &&
              (mouseCol >= wins.at(_RARROWSAVEDFILESWIN)->getStartX() &&
               mouseCol < wins.at(_RARROWSAVEDFILESWIN)->getStartX() +
               wins.at(_RARROWSAVEDFILESWIN)->getNumCols()))
        {
          buttonNum = _RARROWSAVEDFILESWIN;
        }
    }

  // check if click is in _SAVEDTHEMESWIN
  if((mouseLine >= wins.at(_SAVEDTHEMESWIN)->getStartY()) &&
     (mouseLine < wins.at(_SAVEDTHEMESWIN)->getStartY() +
      wins.at(_SAVEDTHEMESWIN)->getNumLines()) &&
     (mouseCol >= wins.at(_SAVEDTHEMESWIN)->getStartX() &&
      mouseCol < wins.at(_SAVEDTHEMESWIN)->getStartX() +
      wins.at(_SAVEDTHEMESWIN)->getNumCols()))
    {
      if((mouseLine == wins.at(_RARROWSAVEDTHEMESWIN)->getStartY()) &&
         (mouseCol >= wins.at(_RARROWSAVEDTHEMESWIN)->getStartX() &&
          mouseCol < wins.at(_RARROWSAVEDTHEMESWIN)->getStartX() +
          wins.at(_RARROWSAVEDTHEMESWIN)->getNumCols()))
        {
          buttonNum = _RARROWSAVEDTHEMESWIN;
        }
      else if((mouseLine == wins.at(_LARROWSAVEDTHEMESWIN)->getStartY()) &&
              (mouseCol >= wins.at(_LARROWSAVEDTHEMESWIN)->getStartX() &&
               mouseCol < wins.at(_LARROWSAVEDTHEMESWIN)->getStartX() +
               wins.at(_LARROWSAVEDTHEMESWIN)->getNumCols()))
        {
          buttonNum = _LARROWSAVEDTHEMESWIN;
        }
    }

  // check if click is in _HELPWIN
  if((mouseLine >= wins.at(_HELPWIN)->getStartY()) &&
     (mouseLine < wins.at(_HELPWIN)->getStartY() +
      wins.at(_HELPWIN)->getNumLines()) &&
     (mouseCol >= wins.at(_HELPWIN)->getStartX() &&
      mouseCol < wins.at(_HELPWIN)->getStartX() +
      wins.at(_HELPWIN)->getNumCols()))
    {
      if((mouseLine == wins.at(_HWSFADDFILE)->getStartY()) &&
         (mouseCol >= wins.at(_HWSFADDFILE)->getStartX() &&
          mouseCol < wins.at(_HWSFADDFILE)->getStartX() +
          wins.at(_HWSFADDFILE)->getNumCols()))
        {
          buttonNum = _HWSFADDFILE;
        }
      else if((mouseLine == wins.at(_HWSFEDITFILEPATH)->getStartY()) &&
              (mouseCol >= wins.at(_HWSFEDITFILEPATH)->getStartX() &&
               mouseCol < wins.at(_HWSFEDITFILEPATH)->getStartX() +
               wins.at(_HWSFEDITFILEPATH)->getNumCols()))
        {
          buttonNum = _HWSFEDITFILEPATH;
        }
      else if((mouseLine == wins.at(_HWSFVIEWFILEPATH)->getStartY()) &&
              (mouseCol >= wins.at(_HWSFVIEWFILEPATH)->getStartX() &&
               mouseCol < wins.at(_HWSFVIEWFILEPATH)->getStartX() +
               wins.at(_HWSFVIEWFILEPATH)->getNumCols()))
        {
          buttonNum = _HWSFVIEWFILEPATH;
        }
      else if((mouseLine == wins.at(_HWSFREMOVEFILE)->getStartY()) &&
              (mouseCol >= wins.at(_HWSFREMOVEFILE)->getStartX() &&
               mouseCol < wins.at(_HWSFREMOVEFILE)->getStartX() +
               wins.at(_HWSFREMOVEFILE)->getNumCols()))
        {
          buttonNum = _HWSFREMOVEFILE;
        }
      else if((mouseLine == wins.at(_HWSFADDTHEME)->getStartY()) &&
              (mouseCol >= wins.at(_HWSFADDTHEME)->getStartX() &&
               mouseCol < wins.at(_HWSFADDTHEME)->getStartX() +
               wins.at(_HWSFADDTHEME)->getNumCols()))
        {
          buttonNum = _HWSFADDTHEME;
        }
      else if((mouseLine == wins.at(_HWSFEDITTHEME)->getStartY()) &&
              (mouseCol >= wins.at(_HWSFEDITTHEME)->getStartX() &&
               mouseCol < wins.at(_HWSFEDITTHEME)->getStartX() +
               wins.at(_HWSFEDITTHEME)->getNumCols()))
        {
          buttonNum = _HWSFEDITTHEME;
        }
      else if((mouseLine == wins.at(_HWSFREMOVETHEME)->getStartY()) &&
              (mouseCol >= wins.at(_HWSFREMOVETHEME)->getStartX() &&
               mouseCol < wins.at(_HWSFREMOVETHEME)->getStartX() +
               wins.at(_HWSFREMOVETHEME)->getNumCols()))
        {
          buttonNum = _HWSFREMOVETHEME;
        }
      else if((mouseLine == wins.at(_HWSTADDTHEME)->getStartY()) &&
              (mouseCol >= wins.at(_HWSTADDTHEME)->getStartX() &&
               mouseCol < wins.at(_HWSTADDTHEME)->getStartX() +
               wins.at(_HWSTADDTHEME)->getNumCols()))
        {
          buttonNum = _HWSTADDTHEME;
        }
      else if((mouseLine == wins.at(_HWSTREMOVETHEME)->getStartY()) &&
              (mouseCol >= wins.at(_HWSTREMOVETHEME)->getStartX() &&
               mouseCol < wins.at(_HWSTREMOVETHEME)->getStartX() +
               wins.at(_HWSTREMOVETHEME)->getNumCols()))
        {
          buttonNum = _HWSTREMOVETHEME;
        }
      else if((mouseLine == wins.at(_HWSTEDITTHEME)->getStartY()) &&
              (mouseCol >= wins.at(_HWSTEDITTHEME)->getStartX() &&
               mouseCol < wins.at(_HWSTEDITTHEME)->getStartX() +
               wins.at(_HWSTEDITTHEME)->getNumCols()))
        {
          buttonNum = _HWSTEDITTHEME;
        }
      else if((mouseLine == wins.at(_HWSTVIEWTHEME)->getStartY()) &&
              (mouseCol >= wins.at(_HWSTVIEWTHEME)->getStartX() &&
               mouseCol < wins.at(_HWSTVIEWTHEME)->getStartX() +
               wins.at(_HWSTVIEWTHEME)->getNumCols()))
        {
          buttonNum = _HWSTVIEWTHEME;
        }
    }

  return buttonNum;
} // end of "checkButtonClick"



/*
  Function:
   checkSFClick

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
} // end of "checkSFClick"



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
} // end of "checkSTClick"



bool checkWindowClick(std::unordered_map<int, CursesWindow*>& wins,
                      const int win,
                      MEVENT& mouse,
                      int& mouseLine,
                      int& mouseCol,
                      const int yOffsetStart,
                      const int yOffsetEnd,
                      const int xOffsetStart,
                      const int xOffsetEnd,
                      std::ofstream& log)
{
  mouseLine = -1;
  mouseCol = -1;

  if(getmouse(&mouse) == OK)
    {
      // check if a mouse click is detected and operate depending click location
      if(mouse.bstate & BUTTON1_PRESSED)
        {
          mouseLine = mouse.y;
          mouseCol = mouse.x;

          // return to previous state if user clicked out of the _SFPROMPTWIN
          if((mouseLine <= wins.at(win)->getStartY() - yOffsetStart) ||
             (mouseLine > wins.at(win)->getStartY() +
              wins.at(win)->getNumLines()  - yOffsetEnd) ||
             ((mouseCol <= wins.at(win)->getStartX()  - xOffsetStart) ||
              (mouseCol > wins.at(win)->getStartX() +
               wins.at(win)->getNumCols() - xOffsetEnd)))
            {
              return false;
            }
        }
    }

    return true;
} // end of "checkWindowClick"




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
  int numCols = maxCols - _PROMPTWINCOLOFFSET + 3;
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

  if(_SAVEDFILESWINMINLINES < numLines - 1)
    {
      if(halfedLines - 1 > _SAVEDFILESWINMINLINES)
        {
          linesCheck = true;
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
      if(wins.at(_SFPROMPTWIN)->getWindow() != nullptr)
        {
          wins.at(_SFPROMPTWIN)->deleteWindow();
          wins.at(_SFPROMPTWIN)->setWindow(nullptr);
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
      if(wins.at(_SFPROMPTWIN)->getWindow() != nullptr)
        {
          wins.at(_SFPROMPTWIN)->deleteWindow();
          wins.at(_SFPROMPTWIN)->setWindow(nullptr);
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

  if(_SAVEDTHEMESWINMINLINES < numLines - 1)
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



void define_HWButtons(std::unordered_map<int, CursesWindow*>& wins)
{
  // delete any button windows if they exist
  for(int i = _HWSFADDFILE; i <= _HWSTVIEWTHEME; i++)
    {
      if(wins.at(i)->getWindow() != nullptr)
        {
          werase(wins.at(i)->getWindow());
          wins.at(i)->deleteWindow();
          wins.at(i)->setWindow(nullptr);
        }
    }

  if(wins.at(_HELPWIN)->getWindow() != nullptr)
    {
      int numLines = _HWBUTTONLINES;
      int numCols = _HWBUTTONCOLS;
      int startY = wins.at(_HELPWIN)->getStartY() + 4;
      int startX = wins.at(_HELPWIN)->getStartX() + 4;

      // add file
      wins.at(_HWSFADDFILE)->defineWindow(newwin(numLines,
                                             numCols,
                                             startY,
                                             startX),
                                          _hwSFAddFile,
                                          numLines,
                                          numCols,
                                          startY,
                                          startX);
      // edd file path
      startY += 2;
      wins.at(_HWSFEDITFILEPATH)->defineWindow(newwin(numLines,
                                                      numCols,
                                                      startY,
                                                      startX),
                                               _hwSFEditFilePath,
                                               numLines,
                                               numCols,
                                               startY,
                                               startX);
      // view file path
      startY +=2;
      wins.at(_HWSFVIEWFILEPATH)->defineWindow(newwin(numLines,
                                                      numCols,
                                                      startY,
                                                      startX),
                                             _hwSFViewFilePath,
                                             numLines,
                                             numCols,
                                             startY,
                                             startX);
      // remove file
      startY +=2;
      wins.at(_HWSFREMOVEFILE)->defineWindow(newwin(numLines,
                                                      numCols,
                                                      startY,
                                                      startX),
                                             _hwSFRemoveFile,
                                             numLines,
                                             numCols,
                                             startY,
                                             startX);
      // add theme
      startY = wins.at(_HELPWIN)->getStartY() + 4;
      startX = wins.at(_HWSFADDFILE)->getStartX() + wins.at(_HWSFADDFILE)->getNumCols() + 2;
      wins.at(_HWSFADDTHEME)->defineWindow(newwin(numLines,
                                                      numCols,
                                                      startY,
                                                      startX),
                                             _hwSFAddTheme,
                                             numLines,
                                             numCols,
                                             startY,
                                             startX);
      // edit theme
      startY += 2;
      wins.at(_HWSFEDITTHEME)->defineWindow(newwin(numLines,
                                                  numCols,
                                                  startY,
                                                  startX),
                                           _hwSFEditTheme,
                                           numLines,
                                           numCols,
                                           startY,
                                           startX);
      // remove theme
      startY += 2;
      wins.at(_HWSFREMOVETHEME)->defineWindow(newwin(numLines,
                                                   numCols,
                                                   startY,
                                                   startX),
                                            _hwSFRemoveTheme,
                                            numLines,
                                            numCols,
                                            startY,
                                            startX);
      // curr theme buttons
      // add theme
      startY = wins.at(_SAVEDTHEMESWIN)->getStartY() + 4;
      startX = wins.at(_HELPWIN)->getStartX() + 4;
      wins.at(_HWSTADDTHEME)->defineWindow(newwin(numLines,
                                                   numCols,
                                                   startY,
                                                   startX),
                                           _hwSTAddTheme,
                                           numLines,
                                           numCols,
                                           startY,
                                           startX);
      // edit theme
      startY += 2;
      wins.at(_HWSTEDITTHEME)->defineWindow(newwin(numLines,
                                                  numCols,
                                                  startY,
                                                  startX),
                                           _hwSTEditTheme,
                                           numLines,
                                           numCols,
                                           startY,
                                           startX);
      // remove theme
      startY = wins.at(_SAVEDTHEMESWIN)->getStartY() + 4;
      startX = wins.at(_HWSFADDFILE)->getStartX() + wins.at(_HWSFADDFILE)->getNumCols() + 2;
      wins.at(_HWSTREMOVETHEME)->defineWindow(newwin(numLines,
                                                     numCols,
                                                     startY,
                                                     startX),
                                              _hwSTRemoveTheme,
                                              numLines,
                                              numCols,
                                              startY,
                                              startX);
      // view theme
      startY += 2;
      wins.at(_HWSTVIEWTHEME)->defineWindow(newwin(numLines,
                                                     numCols,
                                                     startY,
                                                     startX),
                                              _hwSTViewTheme,
                                              numLines,
                                              numCols,
                                              startY,
                                              startX);
  }
} // end of "define_HWButtons"



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

  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      if(_HELPWINSTARTY + _HELPWINMINLINES < maxLines - _HELPWINLINEOFFSET)
        {
          numLines = maxLines - _HELPWINLINEOFFSET - startY;
          linesCheck = true;
        }

      if(maxCols > _HELPWINMINCOLS + _HELPWINCOLOFFSET)
        {
          colsCheck = true;
        }
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

      // create the window buttons
      define_HWButtons(wins);
    }
  // the window has been resized to a bad dimension. delete it
  else
    {
      // update _HELPWIN start positions so other functions can utilize them
      wins.at(_HELPWIN)->setStartX(startX);
      wins.at(_HELPWIN)->setStartY(startY);

      if(wins.at(_HELPWIN)->getWindow() != nullptr)
        {
          wins.at(_HELPWIN)->deleteWindow();
          wins.at(_HELPWIN)->setWindow(nullptr);
        }
      if(wins.at(_HWSFADDFILE)->getWindow() != nullptr)
        {
          wins.at(_HWSFADDFILE)->deleteWindow();
          wins.at(_HWSFADDFILE)->setWindow(nullptr);
        }
      if(wins.at(_HWSFEDITFILEPATH)->getWindow() != nullptr)
        {
          wins.at(_HWSFEDITFILEPATH)->deleteWindow();
          wins.at(_HWSFEDITFILEPATH)->setWindow(nullptr);
        }
      if(wins.at(_HWSFVIEWFILEPATH)->getWindow() != nullptr)
        {
          wins.at(_HWSFVIEWFILEPATH)->deleteWindow();
          wins.at(_HWSFVIEWFILEPATH)->setWindow(nullptr);
        }
      if(wins.at(_HWSFREMOVEFILE)->getWindow() != nullptr)
        {
          wins.at(_HWSFREMOVEFILE)->deleteWindow();
          wins.at(_HWSFREMOVEFILE)->setWindow(nullptr);
        }
      if(wins.at(_HWSFADDTHEME)->getWindow() != nullptr)
        {
          wins.at(_HWSFADDTHEME)->deleteWindow();
          wins.at(_HWSFADDTHEME)->setWindow(nullptr);
        }
      if(wins.at(_HWSFEDITTHEME)->getWindow() != nullptr)
        {
          wins.at(_HWSFEDITTHEME)->deleteWindow();
          wins.at(_HWSFEDITTHEME)->setWindow(nullptr);
        }
      if(wins.at(_HWSFREMOVETHEME)->getWindow() != nullptr)
        {
          wins.at(_HWSFREMOVETHEME)->deleteWindow();
          wins.at(_HWSFREMOVETHEME)->setWindow(nullptr);
        }
      if(wins.at(_HWSTADDTHEME)->getWindow() != nullptr)
        {
          wins.at(_HWSTADDTHEME)->deleteWindow();
          wins.at(_HWSTADDTHEME)->setWindow(nullptr);
        }
      if(wins.at(_HWSTREMOVETHEME)->getWindow() != nullptr)
        {
          wins.at(_HWSTREMOVETHEME)->deleteWindow();
          wins.at(_HWSTREMOVETHEME)->setWindow(nullptr);
        }
      if(wins.at(_HWSTEDITTHEME)->getWindow() != nullptr)
        {
          wins.at(_HWSTEDITTHEME)->deleteWindow();
          wins.at(_HWSTEDITTHEME)->setWindow(nullptr);
        }
      if(wins.at(_HWSTVIEWTHEME)->getWindow() != nullptr)
        {
          wins.at(_HWSTVIEWTHEME)->deleteWindow();
          wins.at(_HWSTVIEWTHEME)->setWindow(nullptr);
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
  wattron(wins.at(_MAINWIN)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
  box(wins.at(_MAINWIN)->getWindow(), ' ', ' ');
  wattron(wins.at(_MAINWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));

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
  defineHelpWin(wins,
                numLines,
                numCols);
}  // end of "defineWins"



void defineSFPromptWin(std::unordered_map<int, CursesWindow*>& wins,
                       std::ofstream& log)
{
  // check that the main windows are initialized
  if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr &&
     wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
    {
      int numLines = 4;
      int numCols = wins.at(_SAVEDFILESWIN)->getNumCols() - 4;
      int startY = wins.at(_SAVEDFILESWIN)->getStartY() + numLines;
      int startX = _SAVEDFILESWINSTARTX + 2;
      
      wins.at(_SFPROMPTWIN)->defineWindow(newwin(numLines,
                                                    numCols,
                                                    startY,
                                                    startX),
                                             "_SFPROMPTWIN",
                                             numLines,
                                             numCols,
                                             startY,
                                             startX);
    }
  else 
    {
      // ensure the window doesn't exist if the main windows dont exist
      if(wins.at(_SFPROMPTWIN)->getWindow() != nullptr)
        {
          wins.at(_SFPROMPTWIN)->deleteWindow();
          wins.at(_SFPROMPTWIN)->setWindow(nullptr);
        }
    }

} // end of "defineHWSFAddFileWin"




void flashButton(const std::unordered_map<int, CursesWindow*>& wins,
                 const int win,
                 std::string outString,
                 const int colorStart,
                 const int colorFlash,
                 std::ofstream& log)
{
  printButtonWin(wins,
                 win,
                 outString,
                 colorFlash,
                 log);
  wnoutrefresh(wins.at(win)->getWindow());
  doupdate();
  usleep(40000);
  printButtonWin(wins,
                 win,
                 outString,
                 colorStart,
                 log);
} // "end of FlashButton"


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
                    std::ofstream& log)
{
  for(int i = _MAINWIN; i <= _STPROMPTWIN; i++)
    {
      CursesWindow* newWindow = new CursesWindow();
      wins.insert(std::make_pair(i, newWindow));
    }
} // end of "initializeWins"



void printButtonWin(const std::unordered_map<int, CursesWindow*>& wins,
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
} // end of "printButtonWin"



void printHelpWin(std::unordered_map<int, CursesWindow*>& wins,
                  std::ofstream& log)
{
  if(wins.at(_HELPWIN)->getWindow() != nullptr)
    {
      wattron(wins.at(_HELPWIN)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
      box(wins.at(_HELPWIN)->getWindow(), ' ', ' ');
      wattron(wins.at(_HELPWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
      int maxWinLines;
      int maxWinCols;
      getmaxyx(wins.at(_HELPWIN)->getWindow(),
               maxWinLines,
               maxWinCols);

      int printColPosition;
      std::string filesCount;

      int linePosition = wins.at(_HELPWIN)->getStartY() + 2;

      std::vector<std::string>::const_iterator it;
      std::string outString;

      // print win title
      if(wins.at(_SAVEDFILESWIN)->getWindow() != nullptr)
        {
          int sfLineOffset = 2;
          int sfColOffset = 3;

          // sf titles
          wattron(wins.at(_HELPWIN)->getWindow(), A_BOLD);
          outString = sfTitle;
          mvwaddstr(wins.at(_HELPWIN)->getWindow(),
                    sfLineOffset,
                    sfColOffset,
                    outString.c_str());
          outString = sfThemeTitle;
          sfColOffset += _HWBUTTONCOLS + 2;
          mvwaddstr(wins.at(_HELPWIN)->getWindow(),
                    sfLineOffset,
                    sfColOffset,
                    outString.c_str());
          wattroff(wins.at(_HELPWIN)->getWindow(), A_BOLD);

          // sf buttons
          printButtonWin(wins,
                         _HWSFADDFILE,
                         _hwSFAddFile,
                         _BLACK_TEXT,
                         log);

          printButtonWin(wins,
                         _HWSFEDITFILEPATH,
                         _hwSFEditFilePath,
                         _BLACK_TEXT,
                         log);
          printButtonWin(wins,
                         _HWSFVIEWFILEPATH,
                         _hwSFViewFilePath,
                         _BLACK_TEXT,
                         log);
          printButtonWin(wins,
                         _HWSFREMOVEFILE,
                         _hwSFRemoveFile,
                         _BLACK_TEXT,
                         log);

          printButtonWin(wins,
                         _HWSFADDTHEME,
                         _hwSFAddTheme,
                         _BLACK_TEXT,
                         log);
          printButtonWin(wins,
                         _HWSFEDITTHEME,
                         _hwSFEditTheme,
                         _BLACK_TEXT,
                         log);
          printButtonWin(wins,
                         _HWSFREMOVETHEME,
                         _hwSFRemoveTheme,
                         _BLACK_TEXT,
                         log);
      }

      if(wins.at(_SAVEDTHEMESWIN)->getWindow() != nullptr)
        {
          int stLineOffset = wins.at(_SAVEDTHEMESWIN)->getStartY() - _HELPWINSTARTY + 2;
          int stColOffset = 3;
          // saved theme
          wattron(wins.at(_HELPWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
          wattron(wins.at(_HELPWIN)->getWindow(), A_BOLD);
          outString = stTitle;
          mvwaddstr(wins.at(_HELPWIN)->getWindow(),
                    stLineOffset,
                    stColOffset,
                    outString.c_str());
          wattroff(wins.at(_HELPWIN)->getWindow(), A_BOLD);
          printButtonWin(wins,
                         _HWSTADDTHEME,
                         _hwSTAddTheme,
                         _BLACK_TEXT,
                         log);
          printButtonWin(wins,
                         _HWSTREMOVETHEME,
                         _hwSTRemoveTheme,
                         _BLACK_TEXT,
                         log);
          printButtonWin(wins,
                         _HWSTEDITTHEME,
                         _hwSTEditTheme,
                         _BLACK_TEXT,
                         log);
          printButtonWin(wins,
                         _HWSTVIEWTHEME,
                         _hwSTViewTheme,
                         _BLACK_TEXT,
                         log);
        }
    }
} // end of "printHelpWin"



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



void printPrompt(std::unordered_map<int, CursesWindow*>& wins,
                 const int win,
                 const std::string& prompt,
                 std::ofstream& log)
{
  wattron(wins.at(win)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
  box(wins.at(win)->getWindow(), ' ', ' ');
  wattron(wins.at(win)->getWindow(), COLOR_PAIR(_WHITE_TEXT));

  mvwaddstr(wins.at(win)->getWindow(),
            1,
            1,
            prompt.c_str());
  wrefresh(wins.at(win)->getWindow());
  doupdate;
} // end of "printPrompt"


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

      wattron(wins.at(_PROMPTWIN)->getWindow(), A_BOLD);
      for(it = promptStrings.begin(); it != promptStrings.end(); i++, it++)
        {
          outString = *it;
          const int temp = wins.at(_MAINWIN)->getStartX();

          if(outString.length() >= currCols - offset)
            {
              outString.resize(currCols - offset);
            }

          mvwaddstr(wins.at(_PROMPTWIN)->getWindow(),
                    i,
                    0,
                    outString.c_str());
        }
      wattroff(wins.at(_PROMPTWIN)->getWindow(), A_BOLD);
    }
} // end of "printPromptWin"



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
      wattron(wins.at(_SAVEDFILESWIN)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
      box(wins.at(_SAVEDFILESWIN)->getWindow(), ' ', ' ');
      wattron(wins.at(_SAVEDFILESWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
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
      wattron(wins.at(_SAVEDFILESWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));
      wattron(wins.at(_SAVEDFILESWIN)->getWindow(), A_BOLD);
      outString = sfTitle;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + _SFWINMINLINEOFFSET,
                _SFWINMINCOLOFFSET,
                outString.c_str());

      // print current theme title
      outString = sfThemeTitle;
      printColPosition = maxWinCols - outString.length() - _SFWINMINCOLOFFSET;
      mvwaddstr(wins.at(_SAVEDFILESWIN)->getWindow(),
                i + _SFWINMINLINEOFFSET,
                maxWinCols - outString.length() - _SFWINMINCOLOFFSET,
                outString.c_str());
      wattroff(wins.at(_SAVEDFILESWIN)->getWindow(), A_BOLD);

      // print the arrow windows for _SAVEDFILESWIN
      printButtonWin(wins,
                    _LARROWSAVEDFILESWIN,
                    leftArrow,
                    _BLACK_TEXT,
                    log);

      printButtonWin(wins,
                    _RARROWSAVEDFILESWIN,
                    rightArrow,
                    _BLACK_TEXT,
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
      wattron(wins.at(_SAVEDTHEMESWIN)->getWindow(), COLOR_PAIR(_BLACK_TEXT));
      box(wins.at(_SAVEDTHEMESWIN)->getWindow(), ' ', ' ');
      wattron(wins.at(_SAVEDTHEMESWIN)->getWindow(), COLOR_PAIR(_WHITE_TEXT));

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

      wattron(wins.at(_SAVEDTHEMESWIN)->getWindow(), A_BOLD);
      outString = stTitle;
      mvwaddstr(wins.at(_SAVEDTHEMESWIN)->getWindow(),
                _STWINMINLINEOFFSET,
                _STWINMINCOLOFFSET,
                outString.c_str());
      wattroff(wins.at(_SAVEDTHEMESWIN)->getWindow(), A_BOLD);
      printButtonWin(wins,
                     _LARROWSAVEDTHEMESWIN,
                     leftArrow,
                     _BLACK_TEXT,
                     log);

      printButtonWin(wins,
                     _RARROWSAVEDTHEMESWIN,
                     rightArrow,
                     _BLACK_TEXT,
                     log);
    }
} // end of "printSavedThemesWin"



void printUserInput(const std::unordered_map<int, CursesWindow*>& wins,
                    const int winIndex,
                    const int& userInput,
                    std::string& inputString,
                    const int& yOffset,
                    int& xOffset)
{
  if((userInput >= 32) &&
     (userInput <= 126) &&
     (userInput != KEY_ENTER || userInput != 10) &&
     (xOffset < wins.at(winIndex)->getNumCols()))
    {
      inputString.push_back(userInput);
      mvwaddch(wins.at(winIndex)->getWindow(),
               0,
               xOffset,
               userInput);
      xOffset++;
    }
  else if(userInput == KEY_BACKSPACE && xOffset > 0)
    {
      inputString.pop_back();
      xOffset--;
      mvwaddch(wins.at(winIndex)->getWindow(),
               0,
               xOffset,
               ' ');
      wmove(wins.at(winIndex)->getWindow(),
            0,
            xOffset);
    }
} // end of "printUserInput"



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
   refreshwins

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
void refreshwins(const std::unordered_map<int, CursesWindow*>& wins)
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

} // end of "refreshwins"



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
