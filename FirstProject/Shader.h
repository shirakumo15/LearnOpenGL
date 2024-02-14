#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	// ����ID
	unsigned int ID;

	// ��������ȡ������Shader
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	
	// ʹ��Program
	void use();

	// uniform���ߺ���
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif
