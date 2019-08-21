#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// 纹理采样器
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //根据第三个值作为参数进行线性插值，0.2代表第二个纹理的颜色比重为0.2
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}