

add_library(glfwpp
  STATIC
    Source/glfw.cpp
)

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