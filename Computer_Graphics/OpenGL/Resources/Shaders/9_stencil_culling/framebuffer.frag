#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

const float offset_x = 1.0f / 1920.f; //width
const float offset_y = 1.0f / 1080.f; //height

vec2 offsets[9] = vec2[](
	vec2(-offset_x, offset_y), //top left
	vec2(0.0f, offset_y), //top center
	vec2(offset_x, offset_y), //top right
	vec2(-offset_x, 0.0f), //center left
	vec2(0.0f, 0.0f), //center center
	vec2(offset_x, 0.0f), //center right
	vec2(-offset_x, -offset_y), //bottom left
	vec2(0.0f, -offset_y), //bottom center
	vec2(offset_x, -offset_y) //bottom right

);
//edge detection
float kernel[9] = float[](
	1.0f, 1.0f, 1.0f,
	1.0f, -8.0f, 1.0f,
	1.0f, 1.0f, 1.0f
);

// //Guassian blur
// float kernel[9] = float[](
// 	1.0f / 16, 2.0f / 16, 1.0f / 16,
// 	2.0f / 16, 4.0f / 16, 2.0f / 16,
// 	1.0f / 16, 2.0f / 16, 1.0f / 16
// );

// //pixelation
// float kernel[9] = float[](
// 	0.25f, 0.25f, 0.25f,
// 	0.25f, 0.25f, 0.25f,
// 	0.25f, 0.25f, 0.25f
// );

// // sharpen
// float kernel[9] = float[](
//     -1, -1, -1,
//     -1,  9, -1,
//     -1, -1, -1
// );

void main(){
	vec3 color = vec3(0.0f);
	for(int i = 0; i < 9; ++i){
		color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * kernel[i];
	}
	FragColor = vec4(color, 1.0f);
}