#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

void main(){
	// FragColor = vec4(1.0f) - texture(screenTexture, texCoords);//invert color
	FragColor = texture(screenTexture, texCoords);
}