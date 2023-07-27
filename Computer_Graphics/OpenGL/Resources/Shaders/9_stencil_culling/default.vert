#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;

out DATA{
	vec3 Normal;
	vec3 color;
	vec2 texCoord;
	mat4 projection;
} data_out;


// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
// Imports the model matrix from the main function
uniform mat4 model;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

const mat2 rot_90_degrees = mat2(0.0f, -1.0f, 1.0f, 0.0f);
const mat4 rot_90_degrees_mat4 = mat4(1.0f);


mat4 rotate90DegreesCCWOnXOY(mat4 M) {
    mat4 rotationMatrix = mat4(
        vec4(cos(radians(90.0)), 0.0, sin(radians(90.0)), 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(-sin(radians(90.0)), 0.0, cos(radians(90.0)),  0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    return rotationMatrix * M;
}

void main(){
	
	mat4 rotation_mod = rotate90DegreesCCWOnXOY(rotation);
	gl_Position = model * translation * rotation_mod * scale * vec4(aPos, 1.0f);
	data_out.Normal = aNormal;
	data_out.color = aColor;
	data_out.texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	data_out.projection = camMatrix;
}