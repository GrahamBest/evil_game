#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "../main.hpp"

class c_shader
{
public:
	std::uint32_t program;

	void load_shader(std::string vertex_path, std::string fragment_path)
	{
		std::string vertex_code;
		std::string fragment_code;
		std::ifstream v_shader_file;
		std::ifstream f_shader_file;

		v_shader_file.exceptions(std::ifstream::badbit);
		f_shader_file.exceptions(std::ifstream::badbit);

		try
		{
			v_shader_file.open(vertex_path);
			f_shader_file.open(fragment_path);
			std::stringstream v_shader_stream, f_shader_stream;

			v_shader_stream << v_shader_file.rdbuf();
			f_shader_stream << f_shader_file.rdbuf();

			v_shader_file.close();
			f_shader_file.close();

			vertex_code = v_shader_stream.str();
			fragment_code = f_shader_stream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::printf("FATAL SHADER ERROR !!!!\n SHADER FILE NOT SUCCESFULLY READ\n");
		}

		const char* v_shader_code = vertex_code.c_str();
		const char* f_shader_code = fragment_code.c_str();

		std::uint32_t vertex;
		std::uint32_t fragment;
		std::int32_t success;
		std::uint8_t info_log[512];
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &v_shader_code, NULL);
		glCompileShader(vertex);
		// runtime errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, info_log);
			std::cout << "FATAL SHADER ERROR !!!!\n COMPILATION FAILED\n" << info_log << std::endl;
		}

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &f_shader_code, NULL);
		glCompileShader(fragment);
		// compile errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, info_log);
			std::cout << "FATAL SHADER ERROR !!!!\n COMPILATION FAILED\n" << info_log << std::endl;
		}

		// shader program
		this->program = glCreateProgram();
		glAttachShader(this->program, vertex);
		glAttachShader(this->program, fragment);
		glLinkProgram(this->program);
		// linking errors
		glGetProgramiv(this->program, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(this->program, 512, NULL, info_log);
			std::cout << "FATAL SHADER ERROR !!!!\n LINKING FAILED\n" << info_log << std::endl;
		}

		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	// Uses the current shader
	void use()
	{
		glUseProgram(this->program);
	}
};