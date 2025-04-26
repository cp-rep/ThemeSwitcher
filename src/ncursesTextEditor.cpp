#include "ncursesTextEditor.hpp"


NcursesTextEditor::NcursesTextEditor(WINDOW* win,
                                     const std::string& windowName,
                                     const int& numLines,
                                     const int& numCols,
                                     const int& startY,
                                     const int& startX) : CursesWindow(win,
                                                                       windowName,
                                                                       numLines,
                                                                       numCols,
                                                                       startY,
                                                                       startX)
{
  m_fullString = "";
  m_outString = "";
  m_prefixString = "";
  m_indexFullString = 0;
  m_indexOutString = 0;
  m_prefixStringLen = 0;
} // end of "Constructor"



void NcursesTextEditor::defineTextData(const std::string& prefixString,
                                       const std::string& fullString,
                                       const std::string& outString,
                                       const int& indexFullString,
                                       const int& indexOutString)
{
  m_prefixString = prefixString;
  m_fullString = prefixString + fullString;
  m_outString = prefixString + outString;

  if(!prefixString.empty())
    {
      m_prefixStringLen = prefixString.length();
      m_indexFullString = m_prefixStringLen;
      m_indexOutString = m_prefixStringLen;
    }
  else
    {
      m_prefixStringLen = 0;
      m_indexFullString = indexFullString;
      m_indexOutString = indexOutString;
    }
} // end of "defineTextData"



bool NcursesTextEditor::editText()
{
  bool endFunction = false;
  int userInput = getch();
  flushinp();

  switch(userInput)
    {
    case '\n':
      endFunction = true;
      break;
    case KEY_ENTER:
      endFunction = true;
      break;
    // case KEY_LEFT:
    //   if(actualCurrIndex > 2)
    //     {
    //       actualCurrIndex--;

    //       if(cursorPosition == _MINCURSOR)
    //         {
    //           if(actualCurrIndex >= 2)
    //             {
    //               outputString.clear();
    //               outputString = "> ";
    //               int i, j;
    //               for(i = 0, j = actualCurrIndex; i < numCols - 3; i++, j++)
    //                 {
    //                   outputString.push_back(fullPath.at(j));
    //                 }
    //             }
    //         }
    //     }
    //   if(cursorPosition > _MINCURSOR)
    //     {
    //       cursorPosition--;
    //     }
    //   break;
    // case KEY_RIGHT:
    //   // enter if the actual index is not at the end of the full file string
    //   if(actualCurrIndex < fullPath.length())
    //     {
    //       actualCurrIndex++;
    //     }
    //   p
    //     // enter if the cursor is at the end of the printable window and
    //     // our actual fullPath index is at the final index (technically 1 after)
    //     if((cursorPosition == numCols - 1) &&
    //        (actualCurrIndex <= fullPath.length()))
    //       {
    //         int i, j;
    //         outputString.clear();
    //         for(i = 0, j = (actualCurrIndex - numCols) + 1; i < numCols - 1; i++,j++)
    //           {
    //             outputString.push_back(fullPath.at(j));
    //           }
    //         outputString.replace(0, 2, "> ");
    //       }

    //   // enter if the cursor is not at the end of the printable window
    //   // and keep it within bounds of the printable file string
    //   if((cursorPosition < numCols - 1) &&
    //      cursorPosition < outputString.length())
    //     {
    //       cursorPosition++;
    //     }
    //   break;
    // case KEY_BACKSPACE:
    //   // case: index at the end of the fullPath, full path shorter than window size
    //   if((actualCurrIndex == fullPath.length()) &&
    //      (fullPath.length() < numCols - 1) &&
    //      (actualCurrIndex > 2))
    //     {
    //       outputString.pop_back();
    //       fullPath.pop_back();
    //       cursorPosition--;
    //       actualCurrIndex--;
    //     }
    //   // case: index not at end of fullPath, fullPath shorter than window size
    //   else if((actualCurrIndex < fullPath.length()) &&
    //           (fullPath.length() < numCols - 1) &&
    //           (actualCurrIndex > 2))
    //     {
    //       cursorPosition--;
    //       actualCurrIndex--;
    //       outputString.erase(cursorPosition, 1);
    //       fullPath.erase(actualCurrIndex, 1);
    //     }
    //   // case: index at end of full path path, full path larger than window size
    //   else if((actualCurrIndex == fullPath.length()) &&
    //           (fullPath.length() >= numCols - 1) &&
    //           (cursorPosition == numCols - 1))
    //     {
    //       fullPath.pop_back();
    //       actualCurrIndex--;

    //       if(fullPath.length() >= numCols - 1)
    //         {
    //           outputString.clear();
    //           int i, j;
    //           for(i = 0, j = (actualCurrIndex - numCols) + 1; i < numCols - 1; i++,j++)
    //             {
    //               outputString.push_back(fullPath.at(j));
    //             }
    //           outputString.replace(0, 2, "> ");
    //         }
    //       else
    //         {
    //           outputString.pop_back();
    //         }

    //       if(fullPath.length() < numCols - 1)
    //         {
    //           cursorPosition--;
    //         }
    //     }
    //   break;
    default:
      break;
    }

  // enter on ascii user input in range 32-126
  if((userInput >= 32) &&
     (userInput <= 126))
    {
      // case: cursor at end of full path string
      // if(actualCurrIndex == fullPath.length())
      {
        if(m_fullString.length() < getNumCols() - 1)
          {
            m_outString.clear();
            m_fullString.push_back(userInput);
            m_outString = m_fullString;
            m_indexOutString++;
            m_indexFullString++;
          }
        else if(m_fullString.length() >=  getNumCols() - 1)
          {
            m_fullString.push_back(userInput);
            m_outString.erase(2,1);
            m_outString.push_back(userInput);
            m_indexFullString++;
          }
      }
      // cursor not at end of full path cases
      // else
      //   {
      //     // case: full path shorter than window size
      //     if(fullPath.length() < numCols - 1)
      //       {
      //         outputString.clear();
      //         fullPath.insert(actualCurrIndex, 1, (char)userInput);
      //         outputString = fullPath;
      //         actualCurrIndex++;

      //         if(cursorPosition < numCols - 1)
      //           {
      //             cursorPosition++;
      //           }
      //       }
      //     // case: full path  greater than the window size
      //     else
      //       {
      //         // case: cursor not at end of user input window
      //         if(cursorPosition != numCols -1)
      //           {
      //             fullPath.insert(actualCurrIndex, 1, (char)userInput);
      //             outputString.insert(cursorPosition, 1, (char)userInput);
      //             outputString.pop_back();
      //             cursorPosition++;
      //             actualCurrIndex++;
      //           }
      //         // case: cursor at end of user input window
      //         else
      //           {
      //             outputString.erase(3, 1);
      //             outputString.push_back(userInput);
      //             fullPath.insert(actualCurrIndex, 1, (char)userInput);
      //             actualCurrIndex++;
      //           }
      //       }
      //   }
    }

  return endFunction;
}
// end of "editText"
