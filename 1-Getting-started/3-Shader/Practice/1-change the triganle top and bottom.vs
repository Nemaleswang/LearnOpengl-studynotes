#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos.x,-aPos.y,aPos.z, 1.0);//让三角形倒置只需要改变y轴正负号即可
    ourColor = aColor;
}