# CMakeList.txt : CMake project for C++FinalProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("C++FinalProject")

# Add source to this project's executable.
add_executable (C++FinalProject "C++FinalProject.cpp" "C++FinalProject.h" "Customers.h"  "Vehicle.h" "RentalLocation.h" "Rental.h")
target_include_directories(C++FinalProject PUBLIC "C:\\Users\\hp\\source\\repos\\nana_1.7.4\\nana\\include")
target_include_directories(C++FinalProject PUBLIC "C:\\Users\\hp\\source\\repos\\nana_1.7.4\\nana\\include\\nana\\gui")
target_include_directories(C++FinalProject PUBLIC "C:\\Users\\hp\\source\\repos\\nana_1.7.4\\nana\\include\\nana\\gui\\widgets")
target_include_directories(C++FinalProject PUBLIC "C:\\Users\\hp\\source\\repos\\nana_1.7.4\\nana\\include\\nana\\gui\\detail")
add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
target_link_libraries(C++FinalProject "nana_v143_Debug_x64")
target_link_directories(C++FinalProject PUBLIC "C:\\Users\\hp\\source\\repos\\nana_1.7.4\\nana\\build\\bin")
# TODO: Add tests and install targets if needed.
