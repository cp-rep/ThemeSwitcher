# add the librarys we're going to test
add_library(Gtest)

# direct the file names for the libaries
target_sources(Gtest
  PRIVATE
  # program source
  log.cpp
  PUBLIC
  # program library files
  ../lib/log.hpp
  )

# direct the location of the files
target_include_directories(Gtest
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/../lib    
  )
