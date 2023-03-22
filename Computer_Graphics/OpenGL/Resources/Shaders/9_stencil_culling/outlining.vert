#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


mat4 rotate_XOY_degree_c(float degree) { // rotate on xOy plane clockwise
    mat4 rotationMatrix = mat4(
        vec4(cos(radians(degree)), -sin(radians(degree)), 0.0, 0.0),
        vec4(sin(radians(degree)), cos(radians(degree)), 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    return rotationMatrix;
}
mat4 rotate_XOZ_degree_c(float degree) { // rotate on xOz plane clockwise
    mat4 rotationMatrix = mat4(
        vec4(cos(radians(degree)), 0.0, sin(radians(degree)), 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(-sin(radians(degree)), 0.0, cos(radians(degree)),  0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    return rotationMatrix;
}
mat4 rotate_YOZ_degree_c(float degree) { //rotate on yOz plane clockwise
    mat4 rotationMatrix = mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, cos(radians(degree)), -sin(radians(degree)), 0.0),
        vec4(0.0, sin(radians(degree)), cos(radians(degree)), 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    return rotationMatrix;
}


void main(){
    mat4 rot1 = rotate_XOY_degree_c(270.0f);
    mat4 rot2 = rotate_XOZ_degree_c(90.0f);
    mat4 rot3 = rotate_YOZ_degree_c(90.0f);
    
    float scale_factor = 1.05f;

    mat4 rotation_mod =  rot1 * rot3 * rotation; // fix model position
    
	vec3 crntPos = vec3(model * translation * rotation_mod* scale * scale_factor * vec4(aPos, 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0f);
}