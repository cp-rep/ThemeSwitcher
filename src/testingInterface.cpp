#include "testingInterface.hpp"


void initTestStringVector(std::vector<std::string>& testStrings,
                          const int numStrings,
                          const int numChars,
                          std::ofstream& log)
{
  std::string tempString;
  std::string extension = ".ext";
  bool appendedExt = false;

  for(int i = 0; i < numStrings; i++)
  {
    char temp = 'a';

    for(int j = 0; j < numChars - extension.length(); j++)
      {
        tempString.push_back(temp);
        temp++;

        if(temp == 'z')
          {
            temp = 'a';
          }
      }

    tempString.append(extension);
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
