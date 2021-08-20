cmake_minimum_required(VERSION 3.10)
project(CheeseMenu VERSION 1.0)

add_library(CheeseMenu SHARED  src/Common.cpp src/CustomText.cpp src/D3DRenderer.cpp src/Features.cpp src/Game.cpp src/Hooking.cpp src/Logger.cpp src/LogScript.cpp src/Main.cpp src/MainScript.cpp src/QueueScript.cpp src/ScriptCallback.cpp src/ScriptManager.cpp  src/Config.cpp)
set_property(TARGET CheeseMenu PROPERTY CXX_STANDARD 20)
include_directories(include src)
# add_subdirectory(src/UI)
# add_subdirectory(src/ImGui)