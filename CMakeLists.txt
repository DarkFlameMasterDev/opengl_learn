cmake_minimum_required(VERSION 3.25)
project(opengl_environment_test)

set(CMAKE_CXX_STANDARD 11)

# 检查环境变量
if (NOT DEFINED ENV{GLFW_HOME})
    message(FATAL_ERROR "found no env named GLFW_HOME")
endif ()
if (NOT DEFINED ENV{GLAD_HOME})
    message(FATAL_ERROR "found no env named GLAD_HOME")
endif ()
if (NOT DEFINED ENV{GLM_HOME})
    message(FATAL_ERROR "found no env named GLM_HOME")
endif ()
if (NOT DEFINED ENV{opengl_custom_includes})
    message(FATAL_ERROR "found no env named opengl_custom_includes")
endif ()
if (NOT DEFINED ENV{opengl_custom_config})
    message(FATAL_ERROR "found no env named opengl_custom_config")
endif ()

# 暂存环境变量
set(GLFW_HOME $ENV{GLFW_HOME})
set(GLAD_HOME $ENV{GLAD_HOME})
set(GLM_HOME $ENV{GLM_HOME})
set(OPENGL_CUSTOM_INCLUDES $ENV{opengl_custom_includes})
set(OPENGL_CUSTOM_CONFIG $ENV{opengl_custom_config})

# 设置头文件目录
include_directories("${GLFW_HOME}/include")
include_directories("${GLAD_HOME}/include")
include_directories("${GLM_HOME}")
include_directories("${OPENGL_CUSTOM_INCLUDES}")

# 添加 GLFW3 预编译库
add_library(glfw SHARED IMPORTED)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION "${GLFW_HOME}/lib-universal/libglfw.3.dylib")

# 编译 GLAD 库
add_library(glad SHARED "${GLAD_HOME}/src/glad.c")


####################################################

configure_file(${OPENGL_CUSTOM_CONFIG}/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)


# 创建可执行文件
add_executable(opengl_environment_test
        src/main.cpp
        src/1_HelloOpenGL/hello_window.cpp
        src/1_HelloOpenGL/hello_window.h
        src/1_HelloOpenGL/hello_triangle.cpp
        src/1_HelloOpenGL/hello_triangle.h
        src/1_HelloOpenGL/hello_square.cpp
        src/1_HelloOpenGL/hello_square.h
        src/1_HelloOpenGL/practice/1_two_triangle.cpp
        src/1_HelloOpenGL/practice/1_two_triangle.h
        src/1_HelloOpenGL/practice/2_two_VAO_two_VBO.cpp
        src/1_HelloOpenGL/practice/2_two_VAO_two_VBO.h
        src/1_HelloOpenGL/practice/3_two_triangle_with_two_shader.cpp
        src/1_HelloOpenGL/practice/3_two_triangle_with_two_shader.h
        src/2_GLSL/use_uniform.cpp
        src/2_GLSL/use_uniform.h
        src/2_GLSL/color_in_vertices.cpp
        src/2_GLSL/color_in_vertices.h
        src/2_GLSL/practice/use_uniform_move.cpp
        src/2_GLSL/practice/use_uniform_move.h
        src/2_GLSL/practice/reverse_triangle.cpp
        src/2_GLSL/practice/reverse_triangle.h
        src/2_GLSL/practice/final_practice.cpp
        src/2_GLSL/practice/final_practice.h
        src/3_Textures/HelloTexture.cpp
        src/3_Textures/HelloTexture.h
        src/3_Textures/texture_wrap/TextureWrap.cpp
        src/3_Textures/texture_wrap/TextureWrap.h
        src/3_Textures/uniform_mix/mix.cpp
        src/3_Textures/uniform_mix/mix.h
        src/3_Textures/texture_coord/TextureCoord.cpp
        src/3_Textures/texture_coord/TextureCoord.h
        src/4_transform/HelloTransform.cpp
        src/4_transform/HelloTransform.h
)

# 链接 GLFW GLAD OpenGL
target_link_libraries(opengl_environment_test glfw glad "-framework OpenGL")