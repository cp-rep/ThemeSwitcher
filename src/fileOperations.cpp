#include "fileOperations.hpp"




bool doesDirectoryExist(const std::string& directoryFullPath)
{
  struct stat file;

  if( stat(directoryFullPath.c_str(), &file) )
    {
      return false;
    }

  return ( (file.st_mode & S_IFDIR) != 0 );
} // end of "doesDirectoryExist"



int hwSFAddFile(std::vector<std::string> sfStrings)
{

}
