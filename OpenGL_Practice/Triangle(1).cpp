#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
using namespace std;

//function prototypes
void key_callback(GLFWwindow* window , int key , int scancode , int action , int mode);

//Window dimensions
const GLuint WIDTH = 800 , HEIGHT = 600;

//Shaders Source codes
const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n" //position 变量的的属性位置值为0
	"out vec3 ourColor;\n"  //为片段着色器指定一个颜色输出
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position , 1.0);\n"
	"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
	//"in vec4 vertexColor;"  //从定点着色器传来的输入变量（名称、类型相同）
	"out vec4 color;\n" //片段着色器输出的变量名可以任意命名 ， 类型必须是vec4
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"color = ourColor;\n"
	"}\n\0";




int main()
{
	//Init GLFW
	glfwInit();
	//Set all the required options for glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE , GL_FALSE);

	//Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH , HEIGHT , "LearnOpenGL" , nullptr , nullptr);
	glfwMakeContextCurrent(window);

	//Set the required callback functions
	glfwSetKeyCallback(window , key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	//Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	//Define the viewport dimensions
	int width , height;
	glfwGetFramebufferSize(window , &width , &height);
	glViewport(0 , 0 ,width , height);

	//Build and compile our shader program
	//Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
	glCompileShader(vertexShader);

	//Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader , GL_COMPILE_STATUS , &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader , 512 , NULL , infoLog);
		cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<endl;
	}
	//Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
	glCompileShader(fragmentShader);
	//Check for compile time errors
	glGetShaderiv(fragmentShader , GL_COMPILE_STATUS , &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader , 512 , NULL , infoLog);
		cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<endl;
	}
	//Link Shaders
	GLuint shaderProgram = glCreateProgram();
	//将着色器程序链接到所创建的程序中
	glAttachShader(shaderProgram , vertexShader);
	glAttachShader(shaderProgram , fragmentShader);
	//将这些对象链接成一个可执行的程序
	glLinkProgram(shaderProgram);
	//检查链接是否成功
	glGetProgramiv(shaderProgram , GL_LINK_STATUS , &success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram , 512 , NULL , infoLog);
		cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Set up vertex data(and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		//位置信息             
		0.5f , -0.5f , 0.0f ,
		-0.5f , -0.5f , 0.0f ,
		0.0f , 0.5f , 0.0f 
	};
	GLuint VBO , VAO;
	glGenVertexArrays(1 , &VAO);
	glGenBuffers(1 , &VBO);
	
	//Bind the Vertex Array Object first
	glBindVertexArray(VAO);
	//Then bind and set vertex buffer(s) and attribute pointer(s)
	glBindBuffer(GL_ARRAY_BUFFER , VBO);
	glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
	//位置属性  
	glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(GLfloat) , (GLvoid*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER , 0);
	glBindVertexArray(0);


	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();


		//Render
		//Clear the colorbuffer
		glClearColor(0.2f , 0.3f , 0.3f , 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//Draw the Triangle 相当于激活Shader,uniform用于已激活的Shader
		glUseProgram(shaderProgram);

		//Update the uniform color
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue)/2)+0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram , "ourColor");
		glUniform4f(vertexColorLocation , 0.5f , greenValue , 0.2f , 1.0f);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES , 0 , 3);
		glBindVertexArray(0);

		//Swap the screen buffers
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1 , &VAO);
	glDeleteBuffers(1 , &VBO);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window , int key , int scancode , int action , int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window , GL_TRUE);
	}

}