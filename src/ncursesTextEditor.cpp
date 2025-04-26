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
} // end of "Constructor"



void NcursesTextEditor::defineTextData(const std::string& fullString,
                                       const std::string& outString,
                                       const std::string& prefixString,
                                       const int& indexFullString,
                                       const int& indexOutString)
{
  m_fullString = fullString;
  m_outString = outString;
  m_prefixString = prefixString;
  m_indexFullString = indexFullString;
  m_indexOutString = indexOutString;
} // end of "defineTextData"



bool NcursesTextEditor::editText()
{
  // do nothing
}

// } // end of "editText"
