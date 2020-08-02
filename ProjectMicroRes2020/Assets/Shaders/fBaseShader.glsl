#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D spriteSheet;
uniform vec3 spriteColor;
uniform vec2 spriteOffset; // Element position on sheet
uniform vec2 spriteSheetSize; // Num of elements in sprite sheet

void main()
{
	float xOffset = (1.0 / spriteSheetSize.x) * spriteOffset.x;
	vec2 offsetSize = vec2(1.0, 1.0) / spriteSheetSize;
	vec2 correctedCoords = (TexCoords / spriteSheetSize) + (offsetSize * spriteOffset); 
	FragColor = vec4(spriteColor, 1.0) * texture(spriteSheet, correctedCoords);
}