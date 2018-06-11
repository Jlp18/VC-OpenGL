#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <gl\glew.h>
using namespace std;

class Shader
{
public:
	GLuint Program;
	//Constructor generates the shader on the fly
	Shader(const GLchar* vertexPath , const GLchar* fragmentPath)
	{
		//1.Retrieve the vertex/fragment source code from filePath
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		//ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(ifstream::badbit);
		fShaderFile.exceptions(ifstream::badbit);
		try
		{
			//open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream , fShaderStream;
			//Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close file handles
			vShaderFile.close();
			fShaderFile.close();
			//Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(ifstream::failure e)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();
		//2.Compile shaders
		GLuint vertex , fragment;
		GLint success;
		GLchar infoLog[512];
		//Vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex , 1 ,&vShaderCode , NULL);
		glCompileShader(vertex);
		//Print compile errors if any
		glGetShaderiv(vertex , GL_COMPILE_STATUS , &success);
		if(!success)
		{
			glGetShaderInfoLog(vertex , 512 , NULL , infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}
		//Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment , 1 ,&fShaderCode , NULL);
		glCompileShader(fragment);
		//Print compile errors if any
		glGetShaderiv(fragment , GL_COMPILE_STATUS , &success);
		if(!success)
		{
			glGetShaderInfoLog(fragment , 512 , NULL , infoLog);
			cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n"<< infoLog <<endl;
		}
		//Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program , vertex);
		glAttachShader(this->Program , fragment);
		glLinkProgram(this->Program);
		//Print linking errors if any
		glGetShaderiv(this->Program , GL_LINK_STATUS , &success);
		if(!success)
		{
			glGetShaderInfoLog(this->Program , 512 , NULL  , infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog <<endl; 
		}

		//Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	//Use the current shader
	void Use()
	{
		glUseProgram(this->Program);
	}
};

#endif