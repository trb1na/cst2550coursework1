cmake_minimum_required(VERSION 3.8)
project(Library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
  main.cpp
  Book.cpp
  Librarian.cpp
  Member.cpp
  Person.cpp
  utils.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tests
  tests.cpp
  Book.cpp
  Librarian.cpp
  Member.cpp
  Person.cpp
  utils.cpp
  )

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


enable_testing()
add_test(NAME LibraryTests COMMAND tests)
