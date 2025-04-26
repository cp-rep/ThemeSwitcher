#ifndef NCURSESTEXTEDITOR_HPP
#define NCURSESTEXTEDITOR_HPP
#include "cursesWindow.hpp"
#include "log.hpp"

class NcursesTextEditor : public CursesWindow
{
public:
  NcursesTextEditor(WINDOW* win,
                    const std::string& windowName,
                    const int& numLines,
                    const int& numCols,
                    const int& startY,
                    const int& startX); // inherit CursesWindow constructor

  // getters
  const std::string& getFullString() { return m_fullString; }
  const std::string& getOutString () { return m_outString; }
  const std::string& getPrefixString() { return m_prefixString; }
  const int& getIndexOutstring() { return m_indexOutString; }
  const int& getIndexFullString() { return m_indexFullString; }

  // setters
  void setFullString(const std::string& fullString) { m_fullString = fullString; }
  void setOutString(const std::string& outString) { m_outString = outString; }
  void setPrefixString(const std::string& prefixString) { m_prefixString = prefixString; }
  void setIndexOutString(const int& indexOutString) { m_indexOutString = indexOutString; }
  void setIndexFullString(const int& indexFullString) { m_indexFullString = indexFullString; }

  // member functions
  void defineTextData(const std::string& fullString,
                                       const std::string& outString,
                                       const std::string& prefixString,
                                       const int& indexFullString,
                                       const int& indexOutString);
  bool editText();

private:
  // member data
  std::string m_prefixString;
  std::string m_fullString;
  std::string m_outString;
  int m_indexFullString;
  int m_indexOutString;
  int m_prefixStringLen;
};

#endif // NCURSESTEXTEDITOR_HPP
