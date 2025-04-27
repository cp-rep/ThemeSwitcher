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



bool makeDirectory(const std::string& dirPath)
{
  if(doesDirectoryExist(dirPath))
    {
      return false;
    }
  else
    {
      mkdir(dirPath.c_str(), 0755);
      return true;
    }
}}
