/*
 * File: FragmentShader.cpp
 * File Created: 21th May 2020
 * ––––––––––––––––––––––––
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * ––––––––––––––––––––––––
 * MIT License
 *
 * Copyright (c) 2020 Pokoidev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Framebuffer.hpp>
#include <assert.h>
#include <string>

namespace OpenGLAssignment
{
	Framebuffer::Framebuffer(unsigned int width, unsigned int height, std::string shader)
		:width(width), height(height)
	{
		shader_program = ShaderProgram::get_shader(shader);
	}

	void Framebuffer::build()
	{
		//Generacion de framebuffer
		glGenFramebuffers(1, &id);
		bind();

		//Textura
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			0
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, texture_id, 0);

		const GLenum draw_buffer = GL_COLOR_ATTACHMENT1;

		glDrawBuffers(1, &draw_buffer);

		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

		unbind();

		//Quad de pantalla en el que aplicar el postprocesado
		//y sus coordenadas
		static const GLfloat triangle_positions[] =
		{
			+1.0f, -1.0f, 0.0f,
			+1.0f, +1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			+1.0f, -1.0f, 0.0f

		};
		
		static const GLfloat triangle_texture_uv[] =
		{
			+1.0f,  0.0f,
			+1.0f, +1.0f,
			 0.0f, +1.0f,
			 0.0f, +1.0f,
			 0.0f,  0.0f,
			 1.0f,  0.0f
		};

		glBindVertexArray(0);


		glGenBuffers(1, &triangle_vbo0);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_positions), triangle_positions, GL_STATIC_DRAW);

		glGenBuffers(1, &triangle_vbo1);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_texture_uv), triangle_texture_uv, GL_STATIC_DRAW);

		

	}

	void Framebuffer::render()
	{
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//Uso del shader de postprocesado
		shader_program->use();
		//Textura
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//Renderizado
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
}