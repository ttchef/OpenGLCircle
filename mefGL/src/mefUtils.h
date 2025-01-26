#pragma once

#include "core.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

namespace mef
{
	class mef_vao
	{
	private:
		uint32_t ID;
	public:
		void createVao()
		{
			glGenVertexArrays(1, &ID);
			glBindVertexArray(ID);
		}
		void attribPointer(uint32_t index, uint32_t size, MEF_ENUM type, MEF_ENUM normalized, uint32_t stride, void* offset)
		{
			glVertexAttribPointer(index, size, (GLenum)type, (GLboolean)normalized, stride, offset);
			glEnableVertexAttribArray(index);
		}
		void bind()
		{
			glBindVertexArray(ID);
		}
		void unbind()
		{
			glBindVertexArray(0);
		}
		
	};

	class mef_vbo
	{
	private:
		uint32_t ID;
	public:
		template<typename T>
		void createVBO(T* data, size_t count, DRAW_MODE mode)
		{
			glGenBuffers(GL_ARRAY_BUFFER, &ID);
			glBindBuffer(GL_ARRAY_BUFFER, ID);
			glBufferData(ID, sizeof(T) * count, data, mode);
		}
		void bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, ID);
		}
		void unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};

	class mef_ebo
	{
	private:
		uint32_t ID;
	public:
		template<typename T>
		void createEBO(T* data, size_t count, DRAW_MODE mode)
		{
			glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &ID);
			bind();
			glBufferData(ID, sizeof(T) * count, data, mode);
		}
		void bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		}
		void unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	};

	class mef_shader
	{
	private:
		uint32_t ID;

		mutable std::unordered_map<std::string, GLint> uniformLocations;
	public:
		void createShader(const char* vertexPath, const char* fragmentPath)
		{
			std::string vertexStr;
			std::string fragmentStr;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;

			// Enable Exceptions for ifstream
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				// open Files
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;

				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				vShaderFile.close();
				fShaderFile.close();

				vertexStr = vShaderStream.str();
				fragmentStr = fShaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cout << "[ERROR] SHADER FILE FAILES READING" << std::endl;
			}

			const char* vShaderCode = vertexStr.c_str();
			const char* fShaderCode = fragmentStr.c_str();

			unsigned int vertex, fragment;
			int success;
			char infoLog[512];

			// vertex
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			// Error handling
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vertex, 512, NULL, infoLog);
				std::cout << "[ERROR] VERTEX SHADER COMPILATION FAILED\n" << infoLog << std::endl;
			}

			// fragment
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			// Error handling
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragment, 512, NULL, infoLog);
				std::cout << "[ERROR] FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
			}

			// Create Shader Programm
			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);

			// Error handling
			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(ID, 512, NULL, infoLog);
				std::cout << "[ERROR] SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;
			}

			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}
		GLint getUniformLocation(const std::string& name) const
		{
			const auto it = uniformLocations.find(name);
			if (it != uniformLocations.end())
			{
				return it->second;
			}
			const GLint location = glGetUniformLocation(ID, name.c_str());
			uniformLocations[name] = location;
			return location;
		}
		void bind()
		{
			glUseProgram(ID);
		}
		void unbind()
		{
			glUseProgram(0);
		}

		void setBool(const std::string& name, bool value) const
		{
			glUniform1i(getUniformLocation(name), (int)value);
		}

		void setInt(const std::string& name, int value) const
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void setFloat(const std::string& name, float value) const
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void setMatrix4fv(const std::string& name, const glm::mat4& matrix) const
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}
	};
}

