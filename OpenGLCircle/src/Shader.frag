
#version 330 core

out vec4 FragColor;

float radius = 0.5f;
vec2 pos = vec2(0.0f, 0.0f);

in vec2 fragPos;

void main()
{
	FragColor = vec4(0.0, 0.0, 1.0, 1.0);

	float dist = length(fragPos - pos);

	if (dist > radius)
	{
		FragColor.a = 0.0;
	}

}


