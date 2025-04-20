#include "programStates.hpp"

void enterHWSFAddFileState(std::unordered_map<int, CursesWindow*>& wins,
                           std::ofstream& log)
{
  flashButton(wins,
              _HWSFADDFILE,
              _hwSFAddFile,
              _BLACK_TEXT,
              _WHITE_TEXT,
              log);
  defineSFPromptWin(wins,
                    log);
  printPrompt(wins,
              _SFPROMPTWIN,
              _hwSFAddFileWin,
              log);

  // yOffset = 2;
  // xOffset = 2;
  // CursesWindow* userInputWindow = new CursesWindow();
  // wins.insert(std::make_pair(_USERINPUTWIN, userInputWindow));
  // wins.at(_USERINPUTWIN)->defineWindow(newwin(1,
  //                                             wins.at(_SFPROMPTWIN)->getNumCols(),
  //                                             0,
  //                                             0),
  //                                      "UserInputWindow",
  //                                      0,
  //                                      wins.at(_SFPROMPTWIN)->getStartY(),
  //                                      wins.at(_SFPROMPTWIN)->getStartX(),
  //                                      10);

  // while(input != KEY_ENTER)
  //   {
  //     input = getch();
  //     printUserInput(wins,
  //                    _SFPROMPTWIN,
  //                    input,
  //                    yOffset,
  //                    xOffset);
  //     flushinp();
  //     refreshwins(wins);
  //     doupdate();
  //     usleep(15000);
  //   }
  usleep(1000000);

} // end of "enterHWSFAddFileState"
