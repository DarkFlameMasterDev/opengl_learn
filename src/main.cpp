#include "1_HelloOpenGL/hello_window.h"
#include "1_HelloOpenGL/hello_triangle.h"
#include "1_HelloOpenGL/hello_square.h"
#include "1_HelloOpenGL/practice/1_two_triangle.h"
#include "1_HelloOpenGL/practice/2_two_VAO_two_VBO.h"
#include "1_HelloOpenGL/practice/3_two_triangle_with_two_shader.h"
#include "2_GLSL/use_uniform.h"
#include "2_GLSL/color_in_vertices.h"
#include "2_GLSL/practice/use_uniform_move.h"
#include "2_GLSL/practice/reverse_triangle.h"
#include "2_GLSL/practice/final_practice.h"
#include "3_Textures/HelloTexture.h"
#include "3_Textures/texture_wrap/TextureWrap.h"
#include "3_Textures/uniform_mix/mix.h"
#include "3_Textures/texture_coord/TextureCoord.h"
#include "4_transform/HelloTransform.h"

#include <iostream>


int main() {
//    hello_window::create_a_window();
//    hello_triangle::create_a_triangle();
//    hello_square::create_a_square();
//    hello_window::create_a_window();
//    two_VAO_two_VBO::create_two_triangle_with_two_VAO_two_VBO();
//    two_triangle_with_two_shader::create_two_triangle_with_two_shader();
//    use_uniform::create_a_triangle_with_glsl_uniform();
//    color_in_vertices::create_a_triangle_color_in_vertices();
//    use_uniform_move::create_a_triangle_with_glsl_uniform_move();
//    reverse_triangle::create_a_reverse_triangle();
//    final_practice::create_a_triangle();
//    HelloTexture::create_a_triangle_with_textures();
//    TextureWrap::another_texture_wrap();
//    mix::create_a_triangle_with_mix_textures();
//    TextureCoord::create_a_textures();
    HelloTransform::create_textures_with_transform();
    return 0;
}
