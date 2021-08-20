add_library(ImGUI imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_impl_dx11.cpp imgui_impl_win32.cpp imgui_widgets.cpp)
target_include_directories(UIManager PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))