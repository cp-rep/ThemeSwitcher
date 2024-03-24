#include "testingInterface.hpp"


void initTestStringVector(std::vector<std::string>& testStrings,
                          const int numStrings,
                          const int numChars,
                          std::ofstream& log)
{
  if(numStrings == 0)
    {
      return;
    }

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



void initTestFilesStringVector(std::vector<std::string>& testStrings,
                               const int numStrings,
                               std::ofstream& log)
{
  if(numStrings == 0)
    {
      return;
    }

  std::string tempString;
  std::string file1 = "/home/mine/somedir/anotherdir/andanotherdir/file";
  std::string file2 = "/home/mine/somedir//andanotherdir/file";
  std::string file3 = "/home//mine/somedir/file";
  std::string file4 = "/home/mine/somedir/anotherdir/andanotherdir/andonemore//file";
  std::string file5 = "/home/mine/somedir/anotherdir/andanotherdir/andonemore/andFinalDir/file";
  std::string file6 = "/home/mine/somedir/anotherdir/andanotherdir/andonemore/andFinalDir//home/";
  file6.append("thisisaverylongfile/very/very/long/file/");
  file6.append("mine/somedir/anotherdir/andanotherdir/andonemore/andFinalDir/file");

  for(int i = 0; i < numStrings; i++)
  {
    char temp = 'a';
    int switchVal = random() % 6;

    switch(switchVal)
      {
      case 0:
        testStrings.push_back(file1);
        break;
      case 1:
        testStrings.push_back(file2);
        break;
      case 2:
        testStrings.push_back(file3);
        break;
      case 3:
        testStrings.push_back(file4);
        break;
      case 4:
        testStrings.push_back(file5);
        break;
      case 5:
        testStrings.push_back(file6);
        break;
      default:
        break;
      }

    testStrings.at(i).append(intToStr(i));
    testStrings.at(i).append(".ext");
  }
} // end of "initTestStringVector"



void initTestCurrThemesStringVector(std::vector<std::string>& testStrings,
                               const int numStrings,
                               std::ofstream& log)
{
  if(numStrings == 0)
    {
      return;
    }

  std::string tempString;
  std::string theme1 = "dracula_theme.el";
  std::string theme2 = "doom_one_theme.el";
  std::string theme3 = "low_contrast.toml";
  std::string theme4 = "high_contrsat.py";
  std::string theme5 = "this_is_very_high_contrast.yml";
  std::string theme6 = "this_is_very_low_constrats.yml";

  for(int i = 0; i < numStrings; i++)
  {
    char temp = 'a';
    int switchVal = random() % 6;

    switch(switchVal)
      {
      case 0:
        testStrings.push_back(theme1);
        break;
      case 1:
        testStrings.push_back(theme2);
        break;
      case 2:
        testStrings.push_back(theme3);
        break;
      case 3:
        testStrings.push_back(theme4);
        break;
      case 4:
        testStrings.push_back(theme5);
        break;
      case 5:
        testStrings.push_back(theme6);
        break;
      default:
        break;
      }
  }
} // end of "initTestStringVector"



void printTestStringVectorToLog(const std::vector<std::string>& strings,
                                std::ofstream& log)
{
  if(strings.empty())
    {
      return;
    }

  std::vector<std::string>::const_iterator it;
  int i = 0;

  for(it = strings.begin(); it != strings.end(); it++)
    {
      log << i << ": " << *it << std::endl;
      i++;
    }
} // end of "printTestStringVector"
