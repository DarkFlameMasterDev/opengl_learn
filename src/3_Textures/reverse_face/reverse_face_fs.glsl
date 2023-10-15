#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

vec2 faceCoord;

// texture sampler
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main(){
    // 修改片段着色器，仅让笑脸图案朝另一个方向看
    faceCoord.x = -TexCoord.x;
    faceCoord.y = TexCoord.y;
    FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, faceCoord), 0.3);
}