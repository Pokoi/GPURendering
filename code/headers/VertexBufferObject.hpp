/*
 * File: VertexBufferObject.hpp
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

#pragma once

#include <glad/glad.h>

namespace OpenGLAssignment
{
	class VertexBufferObject
	{
	
		unsigned int id;
		
		GLenum buffer_type;

		GLenum element_type;


	public:
		
		enum BufferTypes

		{
			VBO = GL_ARRAY_BUFFER,
			EAB = GL_ELEMENT_ARRAY_BUFFER
		};

		
		VertexBufferObject(
							const GLbyte   * data, 
							size_t size, 
							BufferTypes buffer_type = VBO
						  ) : 
							element_type(GL_BYTE),
							buffer_type(GLenum(buffer_type)
							) 
		{ 
			create(data, size);
		}


		VertexBufferObject(
							const GLubyte  * data,
							size_t size,
							BufferTypes buffer_type = VBO
					      ) : 
							element_type(GL_UNSIGNED_BYTE), 
							buffer_type(GLenum(buffer_type))
				 
		{ 
			create(data, size);
		}

		VertexBufferObject(
							const GLshort  * data, 
							size_t size, 
							BufferTypes buffer_type = VBO
						   ) : 
							element_type(GL_SHORT), 
							buffer_type(GLenum(buffer_type)) 
		{ 
			create(data, size);
		}
		
		VertexBufferObject(
							const GLushort * data, 
							size_t size, 
							BufferTypes buffer_type = VBO
						   ) : 
							element_type(GL_UNSIGNED_SHORT), 
							buffer_type(GLenum(buffer_type)) 
		{ 
			create(data, size);
		}
		
		VertexBufferObject(
							const GLint    * data, 
							size_t size, 
							BufferTypes buffer_type = VBO
						   ) : 
							element_type(GL_INT),
							buffer_type(GLenum(buffer_type))
		{ 
			create(data, size);
		}
		
		VertexBufferObject(
							const GLuint   * data, 
							size_t size, 
							BufferTypes buffer_type = VBO
						   ) : 
							element_type(GL_UNSIGNED_INT), 
							buffer_type(GLenum(buffer_type)) 
		{ 
			create(data, size);
		}
		
		VertexBufferObject(
							const GLfloat  * data,
							size_t size, 
							BufferTypes buffer_type = VBO
						   ) : 
							element_type(GL_FLOAT),
							buffer_type(GLenum(buffer_type))
		{
			create(data, size);
		}
				
		/**
		@brief Frees the memory
		*/
		~VertexBufferObject()
		{
			glDeleteBuffers(1, &id);
		}

	public:		

		/**
		@brief Get the type of the content of the buffer
		@return The content type
		*/
		GLenum get_element_type() const
		{
			return element_type;
		}

		/**
		@brief Binds the buffer to use it
		*/
		void bind() const
		{
			glBindBuffer(buffer_type, id);
		}

		/**
		@brief Unbinds the buffer before use it
		*/
		void unbind() const
		{
			glBindBuffer(buffer_type, 0);
		}
		
		/**
		@brief Create a buffer in the video memory
		*/
		void create(const void* data, size_t size)
		{
			glGenBuffers(1, &id);
			bind();
			glBufferData(buffer_type, size, data, GL_STATIC_DRAW);			
		}

	};

}


