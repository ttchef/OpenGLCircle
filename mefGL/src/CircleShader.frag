#version 330 core 

out vec4 FragColor;

uniform float radius;  // Im Bereich [0,1]
uniform float xPos;    // Center X position in NDC [-1,1]
uniform float yPos;    // Center Y position in NDC [-1,1]

uniform float WinWidth;
uniform float WinHeight;

void main()
{
    FragColor = vec4(0.0, 1.0, 0.0, 1.0);

    vec2 pixelPosZeroToOne = gl_FragCoord.xy / vec2(WinWidth, WinHeight);

    vec2 pixelPos = vec2((pixelPosZeroToOne.x * 2) - 1, 1 - (pixelPosZeroToOne.y * 2));

    vec2 CenterPos = vec2(xPos, yPos);

    float xDif = pixelPos.x - CenterPos.x;
    float yDif = pixelPos.y - CenterPos.y;
    float distanceSquared = xDif * xDif + yDif * yDif;

    if (distanceSquared > radius * radius)  
    {
        FragColor.a = 0.0;  
    }
}
