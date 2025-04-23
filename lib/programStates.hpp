#ifndef PROGRAMSTATES_HPP
#define PROGRAMSTATES_HPP
#include <fstream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include "_cursesWinConsts.hpp"
#include "_progStateConsts.hpp"
#include "_winStringConsts.hpp"
#include "cursesFunctions.hpp"
#include "cursesWindow.hpp"
#include "fileOperations.hpp"
#include "log.hpp"

void enterHWSFAddFileState(std::unordered_map<int, CursesWindow*>& wins,
                           MEVENT& mouse,
                           int& mouseLine,
                           int& mouseCol,
                           std::ofstream& log);
#endif // PROGRAMSTATES_HPP
