#include <iostream>

//GLEW
#define GLEW_STATIC
#include <gl/glew.h>

//GLFW
#include <GLFW/glfw3.h>


//SOIL
#include <soil/SOIL.h>
#include "Shader.h"
using namespace std;
//Windows dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);



int main()
{
	//Init glfw
	glfwInit();
	//Set all the requires options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE , GL_FALSE);

	//Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH , HEIGHT , "LearnOpenGL" , nullptr , nullptr);
	glfwMakeContextCurrent(window);

	//Set the required callback functiuon
	glfwSetKeyCallback(window, key_callback);

	//Set this to sure so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental=GLU_TRUE;
	//Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	//Delete the viewport dimensions
	glViewport(0 , 0 ,WIDTH , HEIGHT);

	
	//Build and compile our shader program
	Shader ourShader("textures.vs" , "textures.frag");

	//Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		//Positions           //Colors            //Texture Coords纹理坐标
		0.5f , 0.5f , 0.0f , 1.0f , 0.0f , 0.0f , 1.0f , 1.0f,
		0.5f , -0.5f , 0.0f , 0.0f , 1.0f , 0.0f , 1.0f , 0.0f,
		-0.5f , -0.5f , 0.0f , 0.0f , 0.0f , 1.0f , 0.0f , 0.0f,
		-0.5f , 0.5f , 0.0f , 1.0f , 1.0f , 0.0f , 0.0f , 1.0f
	};

	GLuint indices[] = {
		0 , 1 , 3,
		1 , 2 , 3
	};

	GLuint VBO , VAO , EBO;
	glGenVertexArrays(1 , &VAO);
	glGenBuffers(1 , &VBO);
	glGenBuffers(1 , &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER , VBO);
	glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 8*sizeof(GLfloat) , (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color attribute
	glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 8*sizeof(GLfloat) , (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//TexCoord attribute
	glVertexAttribPointer(2 , 2 , GL_FLOAT , GL_FALSE , 8*sizeof(GLfloat) , (GLvoid*)(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); //Unbind VAO

	//Load and create a texture
	GLuint texture;
	glGenTextures(1 , &texture);
	glBindTexture(GL_TEXTURE_2D , texture);// All upcoming GL_TEXTURE_2D operations now have effect on this texture object

	//Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT);
	//Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
	//Load image , create texture and generate mipmaps
	int width , height;
	unsigned char* image = SOIL_load_image("container.jpg" , &width , &height , 0 , SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image); //释放内存
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture. 解绑


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Activate shader
        ourShader.Use();       
        
        // Draw container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();



	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}