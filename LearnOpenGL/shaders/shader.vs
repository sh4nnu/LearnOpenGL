#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;

out vec2 texCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
//   gl_Position = vec4(-1 * aPos, 1.0); // reverse the triangle
//    gl_Position = projection * view * model * transform * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
