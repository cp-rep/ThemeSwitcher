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
    case KEY_LEFT:
      if(m_indexFullString  > m_prefixStringLen)
        {
          m_indexFullString--;

          if(m_indexOutString == m_prefixStringLen)
            {
              if(m_indexFullString >= m_prefixStringLen)
                {
                  m_outString.clear();
                  m_outString = m_prefixString;
                  int i, j;
                  for(i = 0, j = m_indexFullString; i < getNumCols() - 3; i++, j++)
                    {
                      m_outString.push_back(m_fullString.at(j));
                    }
                }
            }
        }
      if(m_indexOutString > m_prefixStringLen)
        {
          m_indexOutString--;
        }
      break;
    case KEY_RIGHT:
      // enter if the actual index is not at the end of the full file string
      if(m_indexFullString < m_fullString.length())
        {
          m_indexFullString++;
        }

        // enter if the cursor is at the end of the printable window and
        // our actual m_fullString index is at the final index (technically 1 after)
        if((m_indexOutString == getNumCols() - 1) &&
           (m_indexFullString <= m_fullString.length()))
          {
            int i, j;
            m_outString.clear();
            for(i = 0, j = (m_indexFullString - getNumCols()) + 1; i < getNumCols() - 1; i++,j++)
              {
                m_outString.push_back(m_fullString.at(j));
              }
            m_outString.replace(0, 2, "> ");
          }

      // enter if the cursor is not at the end of the printable window
      // and keep it within bounds of the printable file string
      if((m_indexOutString < getNumCols() - 1) &&
         m_indexOutString < m_outString.length())
        {
          m_indexOutString++;
        }
    //   break;
    // case KEY_BACKSPACE:
    //   // case: index at the end of the m_fullString, full path shorter than window size
    //   if((m_indexFullString == m_fullString.length()) &&
    //      (m_fullString.length() < getNumCols() - 1) &&
    //      (m_indexFullString > 2))
    //     {
    //       m_outString.pop_back();
    //       m_fullString.pop_back();
    //       m_indexOutString--;
    //       m_indexFullString--;
    //     }
    //   // case: index not at end of m_fullString, m_fullString shorter than window size
    //   else if((m_indexFullString < m_fullString.length()) &&
    //           (m_fullString.length() < getNumCols() - 1) &&
    //           (m_indexFullString > 2))
    //     {
    //       m_indexOutString--;
    //       m_indexFullString--;
    //       m_outString.erase(m_indexOutString, 1);
    //       m_fullString.erase(m_indexFullString, 1);
    //     }
    //   // case: index at end of full path path, full path larger than window size
    //   else if((m_indexFullString == m_fullString.length()) &&
    //           (m_fullString.length() >= getNumCols() - 1) &&
    //           (m_indexOutString == getNumCols() - 1))
    //     {
    //       m_fullString.pop_back();
    //       m_indexFullString--;

    //       if(m_fullString.length() >= getNumCols() - 1)
    //         {
    //           m_outString.clear();
    //           int i, j;
    //           for(i = 0, j = (m_indexFullString - getNumCols()) + 1; i < getNumCols() - 1; i++,j++)
    //             {
    //               m_outString.push_back(m_fullString.at(j));
    //             }
    //           m_outString.replace(0, 2, "> ");
    //         }
    //       else
    //         {
    //           m_outString.pop_back();
    //         }

    //       if(m_fullString.length() < getNumCols() - 1)
    //         {
    //           m_indexOutString--;
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
      // if(m_indexFullString == m_fullString.length())
      if(m_indexFullString  == m_fullString.length())
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
      else
        {
          // case: full path shorter than window size
          if(m_fullString.length() < getNumCols() - 1)
            {
              m_outString.clear();
              m_fullString.insert(m_indexFullString, 1, (char)userInput);
              m_outString = m_fullString;
              m_indexFullString++;

              if(m_indexOutString < getNumCols() - 1)
                {
                  m_indexOutString++;
                }
            }
          // case: full path  greater than the window size
          // else
          //   {
          //     // case: cursor not at end of user input window
          //     if(m_indexOutString != getNumCols() -1)
          //       {
          //         m_fullString.insert(m_indexFullString, 1, (char)userInput);
          //         m_outString.insert(m_indexOutString, 1, (char)userInput);
          //         m_outString.pop_back();
          //         m_indexOutString++;
          //         m_indexFullString++;
          //       }
          //     // case: cursor at end of user input window
          //     else
          //       {
          //         m_outString.erase(3, 1);
          //         m_outString.push_back(userInput);
          //         m_fullString.insert(m_indexFullString, 1, (char)userInput);
          //         m_indexFullString++;
          //       }
          //   }
        }
    }

  return endFunction;
}
// end of "editText"
