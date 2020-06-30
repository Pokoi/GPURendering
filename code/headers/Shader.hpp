/*
 * File: Shader.hpp
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

#include <string>

#include <glad/glad.h>

namespace OpenGLAssignment
{
	class Shader
	{
	public:
		
		class SourceCode
		{
		
			std::string string;

		public:

			/**
			@brief Extract the shader code from a string
			@param code_string The string with the shader code
			@return The shader sourcecode
			*/
			static SourceCode from_string(const std::string & code_string)
			{
				return (SourceCode(code_string));
			}

			/**
			@brief Extract the shader code from a file
			@param file_path The path of the file
			@return The shader sourcecode
			*/
			static SourceCode from_file(const std::string & file_path);

		private:
			
			/**
			@brief Creates an instance
			*/
			SourceCode() {}

			/**
			@brief Creates an instance from a string content
			*/
			SourceCode(std::string source_code_string)
				:string(source_code_string)
			{}


		public:

			/**
			@brief Gets the size of the content of the shader
			@return The size of the shader content
			*/
			size_t size()  
			{ 
				return (string.size());
			}			

		public:

			operator const std::string & () const
			{
				return (SourceCode::string);
			}

			operator const char * () const
			{
				return (SourceCode::string.c_str());
			}


		};

	private:
		
		unsigned int  id;
		

	protected:

		/**
		@brief Creates an instance
		@param source_code The source code of the shader
		@param shader_type The type of the shader (vertex shader or fragment shader)
		*/
		Shader(SourceCode & source_code, GLenum shader_type);

		/**
		@brief Frees the memory of the shader
		*/
		virtual ~Shader();

	public:

		

		operator GLuint () const
		{
			return (id);
		}

	};
}

