#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D spriteSheet;
uniform vec3 spriteColor;
uniform vec2 spriteOffset; // Element position on sheet
uniform vec2 spriteSheetSize; // Num of elements in sprite sheet

void main()
{
	vec2 correctedCoords = (TexCoords/spriteSheetSize) * spriteOffset; 
	FragColor = vec4(spriteColor, 1.0) * texture(spriteSheet, correctedCoords);
}