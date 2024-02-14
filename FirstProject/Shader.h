#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	// 程序ID
	unsigned int ID;

	// 构造器读取并创建Shader
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	
	// 使用Program
	void use();

	// uniform工具函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif
