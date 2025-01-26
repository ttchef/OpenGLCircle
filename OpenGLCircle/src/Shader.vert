
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_proj;

out vec2 fragPos;

void main()
{
	gl_Position = u_proj * vec4(aPos, 1.0);
	fragPos = aPos.xy;
}

