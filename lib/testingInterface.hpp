#ifndef TESTINGINTERFACE_HPP
#define TESTINGINTERFACE_HPP
#include <vector>
#include "log.hpp"
#include "typeConversions.hpp"

void initTestStringVector(std::vector<std::string>& testStrings,
                          const int numStrings,
                          const int numChars,
                          std::ofstream& log);
void initTestFilesStringVector(std::vector<std::string>& testStrings,
                               const int numStrings,
                               std::ofstream& log);
void initTestCurrThemesStringVector(std::vector<std::string>& testStrings,
                               const int numStrings,
                               std::ofstream& log);
void printTestStringVectorToLog(const std::vector<std::string>& strings,
                                std::ofstream& log);


#endif // TESTINGINTERFACE_H_
