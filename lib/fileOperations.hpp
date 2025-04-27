#ifndef FILEOPERATIONS_HPP
#define FILEOPERATIONS_HPP
#include "cursesWindow.hpp"
#include "sys/stat.h"
#include "vector"



bool doesDirectoryExist(const std::string& directoryFullPath);
int hwSFAddFile(std::vector<std::string> sfStrings);

#endif // FILEOPERATIONS_HPP
