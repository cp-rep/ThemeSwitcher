#include "testingInterface.hpp"


void initTestStringVector(std::vector<std::string>& testStrings,
                          const int numStrings,
                          const int numChars,
                          std::ofstream& log)
{
  std::string tempString;
  bool adjusted = false;
  std::string extension = ".ext";

  for(int i = 0; i < numStrings; i++)
  {
    char temp = 'a';
    if(i < 9)
      {
        tempString.append(" ");
      }
    for(int j = 0; j < numChars; j++)
      {
        if(j >= numChars - extension.length())
          {
            tempString.append(extension);
          }
        else
          {
            tempString.push_back(temp);
            temp++;
            if(temp == 'z')
              {
                temp = 'a';
              }
          }
      }

    testStrings.push_back(tempString);
    tempString.clear();
  }
} // end of "initTestStringVector"



void printTestStringVectorToLog(const std::vector<std::string>& strings,
                                std::ofstream& log)
{
  std::vector<std::string>::const_iterator it;
  int i = 0;

  for(it = strings.begin(); it != strings.end(); it++)
    {
      log << i << ": " << *it << std::endl;
      i++;
    }
} // end of "printTestStringVector"
