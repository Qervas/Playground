
#include"9_stencil_culling/Model.h"



#include<filesystem>
namespace fs = std::filesystem;
const unsigned int width = 1920;
const unsigned int height = 1080;

float rectangleVertices[] = {
	// Coords    // texCoords
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,

	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::string title = "OpenGL  ";
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, width, height);

	std::string shaderDir = "Resources/Shaders/9_stencil_culling/";
	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram( (shaderDir + "default.vert").c_str(), (shaderDir + "default.frag").c_str(), (shaderDir + "default.geom").c_str());
	Shader outliningProgram( (shaderDir + "outlining.vert").c_str(), (shaderDir + "outlining.frag").c_str(), nullptr);
	Shader framebufferProgram( (shaderDir + "framebuffer.vert").c_str(), (shaderDir + "framebuffer.frag").c_str(), nullptr);
	
	//related light
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	framebufferProgram.Activate();
	glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);




	// Enables the Depth Buffer, Stencil buffer, Stencil tests rule
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.5f, 2.0f));
	
	std::string model_dir = fs::current_path().string() + "/Resources/Models/";
	Model model((model_dir + "wooden/scene.gltf").c_str());
	Model outline((model_dir + "wooden_outline/wooden_outline.gltf").c_str());


	unsigned int rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));



	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	unsigned int framebufferTexture;
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if( fboStatus != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Framebuffer error:" << fboStatus << std::endl;
	}






	// Main while loop
	while (!glfwWindowShouldClose(window)){

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
	        glfwSetWindowShouldClose(window, GL_TRUE);		
		}

		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		++counter;
		if(timeDiff >= 1.0 / 30.0){
			std::string FPS = std::to_string((1.0 / timeDiff) * counter) + " FPS/";
			std::string ms = std::to_string((timeDiff / counter) * 1000) + " ms";
			glfwSetWindowTitle(window, (title + FPS + ms).c_str());
			prevTime = crntTime;
			counter = 0;

		}

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		// Specify the color of the background
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Make it so the stencil test always passes
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		// Enable modifying of the stencil buffer
		glStencilMask(0xFF);
		// Draw the normal model
		model.Draw(shaderProgram, camera);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		framebufferProgram.Activate();
		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// // Make it so only the pixels without the value 1 pass the test
		// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		// // Disable modifying of the stencil buffer
		// glStencilMask(0x00);
		// // Disable the depth buffer
		// glDisable(GL_DEPTH_TEST);
		
		// outline.Draw(outliningProgram, camera);

		// // Enable modifying of the stencil buffer
		// glStencilMask(0xFF);
		// // Clear stencil buffer
		// glStencilFunc(GL_ALWAYS, 0, 0xFF);
		// // Enable the depth buffer
		// glEnable(GL_DEPTH_TEST);

		// glDisable(GL_CULL_FACE);
		// // grass.Draw(grassProgram, camera);
		// glEnable(GL_CULL_FACE);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	outliningProgram.Delete();
	// grassProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}