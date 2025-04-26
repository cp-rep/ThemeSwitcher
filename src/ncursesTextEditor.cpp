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
} // end of "Default Constructor"


bool NcursesTextEditor::editText()
{
  // do nothing
}

// } // end of "editText"
