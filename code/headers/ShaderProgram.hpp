/*
 * File: ShaderProgram.hpp
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

#include <Shader.hpp>
#include <Texture.hpp>

#include <glad/glad.h>
#include <cassert>
#include <glm.hpp>
#include <map>
#include <string>

namespace OpenGLAssignment
{
	class ShaderProgram
	{	
		
		unsigned int id;
	
		static std::map<std::string, std::shared_ptr<ShaderProgram>> factory;

	public:
		
		/**
		@brief Creates a shader with the given info
		@param name The name of the shader
		@param vertex_shader_path The path of the vertex shader of this shader program
		@param fragment_shader_path The path of the fragment shader of this shader program 
		@return A reference to the shader program
		*/
		static std::shared_ptr<ShaderProgram> create_shader(std::string name, std::string vertex_shader_path, std::string fragment_shader_path);		
		
		/**
		@brief Gets a shader program by its name
		@return A reference to the desired shader program
		*/
		static std::shared_ptr<ShaderProgram> get_shader(std::string name);

		/**
		@brief Creates an instance
		*/
		ShaderProgram()
		{
			id = glCreateProgram();			
			assert(id != 0);
		}

		/**
		@brief Frees the memory
		*/
		~ShaderProgram()
		{
			glDeleteProgram(id);
			id = 0;
		}			

		/**
		@brief Disable the shader program before use it
		*/
		void disable()
		{
			glUseProgram(0);
		}			

		/**
		@brief Attach a shader to the shader program
		@param shader The shader to attach
		*/
		void attach(const Shader & shader)
		{
			glAttachShader(id, shader);
		}

		/**
		@brief Detach a shader from the shader program 
		@param shade The shader to detach
		*/
		void detach(const Shader & shader)
		{
			glDetachShader(id, shader);
		}

		/**
		@brief Link a shader program
		*/
		bool link()
		{
			glLinkProgram(id);
			return true;
		}

		/**
		@brief Prepare the shader program to use it
		*/
		void use()  
		{		
			glUseProgram(id);
		}

		/**
		@brief Get the location of a uniform value
		@param identifier The name of the uniform value
		@return The location
		*/
		unsigned int get_uniform_location(std::string identifier)
		{
			unsigned int uniform_location = glGetUniformLocation(id, identifier.c_str());

			assert(uniform_location != -1);

			return uniform_location;
		}

		/**
		@brief Gets the location of a vertex attribute 
		@param identifier The name of the attribute 
		@return The location
		*/
		unsigned int get_vertex_attrib_location(std::string identifier)
		{

			unsigned int attrib_id = glGetAttribLocation(id, identifier.c_str());

			assert(attrib_id != -1);

			return attrib_id;
		}
		
		operator GLuint () const
		{
			return (id);
		}

		void set_variant_value(GLint variant_id, const GLint     & value) { glUniform1i(variant_id, value); }
		void set_variant_value(GLint variant_id, const float     & value) { glUniform1f(variant_id, value); }
		void set_variant_value(GLint variant_id, const glm::vec2  & vector) { glUniform2f(variant_id, vector[0], vector[1]); }
		void set_variant_value(GLint variant_id, const glm::vec3  & vector) { glUniform3f(variant_id, vector[0], vector[1], vector[2]); }
		void set_variant_value(GLint variant_id, const glm::vec4  & vector) { glUniform4f(variant_id, vector[0], vector[1], vector[2], vector[3]); }
		void set_variant_value(GLint variant_id, const glm::mat2 & matrix) { glUniformMatrix2fv(variant_id, 1, GL_FALSE, &matrix[0][0]); }
		void set_variant_value(GLint variant_id, const glm::mat3 & matrix) { glUniformMatrix3fv(variant_id, 1, GL_FALSE, &matrix[0][0]); }
		void set_variant_value(GLint variant_id, const glm::mat4 & matrix) { glUniformMatrix4fv(variant_id, 1, GL_FALSE, &matrix[0][0]); }

		void set_vertex_attribute(GLint attribute_id, const float    & value) { glVertexAttrib1f(attribute_id, value); }
		void set_vertex_attribute(GLint attribute_id, const glm::vec2 & vector) { glVertexAttrib2fv(attribute_id, &vector[0]); }
		void set_vertex_attribute(GLint attribute_id, const glm::vec3 & vector) { glVertexAttrib3fv(attribute_id, &vector[0]); }
		void set_vertex_attribute(GLint attribute_id, const glm::vec4 & vector) { glVertexAttrib4fv(attribute_id, &vector[0]); }
		
				
	};
}


