

add_library(glfwpp
    STATIC
    Source/glfw.cpp
    ../NetUtils/Source/NetUtils.cpp ../NetUtils/Include/NetUtils.hpp)

target_compile_definitions(glfwpp
  PRIVATE
    GLFW_INTERNALS
)

target_include_directories(glfwpp
  PUBLIC
    Include
)

target_link_libraries(glfwpp
  PUBLIC
    glfw
)