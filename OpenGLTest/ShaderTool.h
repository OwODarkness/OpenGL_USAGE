#ifndef SHADER_TOOL_H
#define SHADER_TOOL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class ShaderTool
{
private:
	unsigned int ProgramID;

public:
	ShaderTool(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderTool(){}
public:
	inline unsigned int GetProgram() const { return ProgramID; }

	inline void Use() { glUseProgram(ProgramID); }
	void setBool(const std::string& name, bool value) ;
	void setInt(const std::string& name, int value) ;
	void setFloat(const std::string& name, float value) ;
	void setMat4f(const std::string & name, float* data);


private:
	void LoadShaderCode(const std::string vertexShaderPath, const std::string fragmentShaderPath,
		std::string& vertexShaderCode, std::string& fragmentShaderCode);
	unsigned int GenerateProgram(const std::string& shaderCode, int ShaderType,const std::string& ShaderName = "Shader");
};

#endif