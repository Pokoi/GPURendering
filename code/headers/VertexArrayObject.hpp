/*
 * File: VertexArrayObject.hpp
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

#include <VertexBufferObject.hpp>
#include <glad/glad.h>

#include <list>
#include <memory>
#include <assert.h>

namespace OpenGLAssignment
{
	class VertexArrayObject
	{
		
		unsigned int id;

		std::list<std::shared_ptr <VertexBufferObject> >vbo_list;		

	public:
		
        /**
        @brief Creates an instance
        */
		VertexArrayObject() 
		{
			glGenVertexArrays(1, &id);				
		}

        /**
        @brief Frees the memory
        */
		~VertexArrayObject()
		{
			glDeleteVertexArrays(1, &id);
		}		

        /**
        @brief Binds the vao to use it
        */
		void bind() const
		{
			glBindVertexArray(id);
		}

        /**
        @brief Unbinds the vao before use it
        */
		void unbind() const
		{
			glBindVertexArray(0);
		}
		
	};
}



