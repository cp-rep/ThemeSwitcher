#include "typeConversions.hpp"



/*
  Function:
   intToStr

  Description:

  Input:

  Output:

*/
std::string intToStr(int value)
{
  char buffer[64];

  std::sprintf(buffer, "%d", value);

  return std::string(buffer);
} // end of "intToStr"
