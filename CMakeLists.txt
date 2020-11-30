# CMakeList.txt : CMake project for WFC_Cloth_Mesh_Corrugator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("WFC_Cloth_Mesh_Corrugator")

# Add source to this project's executable.
add_executable (WFC_Cloth_Mesh_Corrugator 
"WFC_Cloth_Mesh_Corrugator.cpp" 
"WFC_Cloth_Mesh_Corrugator.h" 
"toojpeg.cpp" 
"toojpeg.h"
"stb_image.h" 
"bitmap.h" 
"Preprocessor.h" 
"Preprocessor.cpp")

# TODO: Add tests and install targets if needed.
