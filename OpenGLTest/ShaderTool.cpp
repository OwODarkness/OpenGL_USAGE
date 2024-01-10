#include "ShaderTool.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

ShaderTool::ShaderTool(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	LoadShaderCode(vertexShaderPath, fragmentShaderPath, vertexShaderCode, fragmentShaderCode);
	this->ProgramID = glCreateProgram();
	//顶点着色器
	unsigned int vertexShader = GenerateProgram(vertexShaderCode, GL_VERTEX_SHADER, "VertexShader");
	//片段着色器
	unsigned int fragmentShader = GenerateProgram(fragmentShaderCode, GL_FRAGMENT_SHADER, "FragmentShader");
	glLinkProgram(ProgramID);

	int success;
	char infoLog[512];
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
		std::cout << "PROGRAM LINK ERROR:" << infoLog << std::endl;
		exit(-1);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderTool::LoadShaderCode(const std::string vertexShaderPath, const std::string fragmentShaderPath, std::string& vertexShaderCode, std::string& fragmentShaderCode)
{
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;
	//读文件
	try
	{
		vertexShaderFile.open(vertexShaderPath, std::ios::in);
		fragmentShaderFile.open(fragmentShaderPath, std::ios::in);

		std::stringstream vertexShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();
		vertexShaderCode = vertexShaderStream.str();

		std::stringstream fragmentShaderStream;
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		fragmentShaderFile.close();
		fragmentShaderCode = fragmentShaderStream.str();

	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

unsigned int ShaderTool::GenerateProgram(const std::string& shaderCode, int ShaderType, const std::string& ShaderName)
{
	unsigned int Shader;
	Shader = glCreateShader(ShaderType);
	const char* vertexShaderSource = shaderCode.c_str();
	glShaderSource(Shader, 1, &vertexShaderSource, NULL);
	glCompileShader(Shader);

	int success;
	char infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		std::cout << "ERROR in " << ShaderName << " Compile" << infoLog << std::endl;
		exit(-1);
	}
	glAttachShader(ProgramID, Shader);
	return Shader;
}

void ShaderTool::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), (int)value);
}

void ShaderTool::setInt(const std::string& name, int value) 
{
	glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), value);
}

void ShaderTool::setFloat(const std::string& name, float value) 
{
	glUniform1f(glGetUniformLocation(ProgramID, name.c_str()), value);
}


