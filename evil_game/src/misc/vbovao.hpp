#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>

struct layoutelement_t
{
	std::int32_t type;
	std::int32_t count;
	std::int32_t normalized;
};

class c_vbo_layout
{
public:
	void push(std::int32_t count, float type)
	{
		this->elements.push_back({ GL_FLOAT, count, GL_FALSE });
		this->stride += count * sizeof(float);
	}

	void push(std::int32_t count, std::uint32_t type)
	{
		this->elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		this->stride += count * sizeof(std::uint8_t);
	}

	void push(std::int32_t count, std::uint8_t type)
	{
		this->elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		this->stride += count * sizeof(std::uint8_t);
	}

	std::vector<layoutelement_t> elements;
	std::uint32_t stride;
private:
};

/*
	VBO, ALWAYS GOES BEFORE VAO
*/
class c_vbo
{
public:
	c_vbo(void* data, std::uint32_t size)
	{
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo); 
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	}

	c_vbo(void* data, std::uint32_t size, std::string vs, std::string fs)
	{
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	}

	~c_vbo()
	{
		glDeleteBuffers(1, &this->vbo);
	}

	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	}

	void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	std::uint32_t vbo;
private:
};

/*
	VAO, ALWAYS GOES AFTER VBO(S)
*/
class c_vao
{
public:
	c_vao()
	{
		glGenVertexArrays(1, &this->vao);
	}

	~c_vao()
	{
		glDeleteVertexArrays(1, &this->vao);
	}

	void bind()
	{
		glBindVertexArray(this->vao);
	}

	void add_buffer(c_vbo& vb, c_vbo_layout& layout)
	{
		this->bind();
		vb.bind();
		const auto& elements = layout.elements;
		std::uint32_t offset;

		for (std::uint32_t i = 0; i < elements.size(); i++)
		{
			const auto& element = layout.elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride, reinterpret_cast<const void*>(offset));
			offset += element.count * sizeof(element.type);
		}
	}

	void unbind()
	{
		glBindVertexArray(0);
	}

	std::uint32_t vao;
private:
	std::string file_name_vs;
	std::string file_name_fs;
};