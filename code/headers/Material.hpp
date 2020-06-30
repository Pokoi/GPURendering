/*
 * File: Material.hpp
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

#include <Texture2D.hpp>
#include <ShaderProgram.hpp>
#include <map>
#include <string>

namespace OpenGLAssignment
{
	class Material
	{	
		
		std::shared_ptr < ShaderProgram> shader;		
		
		std::shared_ptr<Texture> texture;

		glm::vec3 color;

	public:
		
		static std::map<std::string, std::shared_ptr<Material>> factory;

		/**
		@brief Gets a Material from the factory. Creates one if the desired does not exist
		@param shader_name The name of the shader
		@param vertex_path The path of the vertex shader
		@param fragment_path The path of the fragment_shader
		@param color The base color
		@param texture_path The path of the texture 
		@return The material
		*/
		static std::shared_ptr<Material> get(
												std::string	shader_name,
												std::string	vertex_path,
												std::string	fragment_path,
												glm::vec3	color = { 1,1,1 },
												std::string	texture_path = "../../assets/textures/default.tga"
										    )
		{					
			std::string id = (vertex_path + fragment_path + texture_path);
			
			if (factory.count(id) > 0 && factory[id]->get_color() == color)
			{
				return factory[id];
			}
			
			std::shared_ptr<Material> material(new Material(shader_name, vertex_path, fragment_path, texture_path));
			material->set_color(color);
			
			factory[id] = material;	

			return material;
		
		}

		/**
		@brief Creates an instance
		@param shader_program The shader program of the material
		*/
		Material(std::shared_ptr<ShaderProgram>& shader_program) :shader(shader_program)
		{}

		/**
		@brief Creates an instance
		@param shader_name The shader program of the material
		@param vertex_path The path of the vertex shader
		@param fragment_path The path of the fragment shader
		@param texture_path The path of the texture
		*/
		Material( 
					std::string shader_name,
					std::string vertex_path,
					std::string fragment_path,
					std::string texture_path
				)
		{
		
			texture = Texture2D::get_texture(texture_path);			
			shader = ShaderProgram::create_shader(shader_name, vertex_path, fragment_path);				
		}
		
		/**
		@brief Use the material
		*/
		void use()
		{
			shader->use();
		}

		/**
		@brief Get the shader program of the material
		@return The shader program
		*/
		std::shared_ptr<ShaderProgram> get_shader() 
		{ 
			return shader;
		}

		/**
		@brief Get the texture of the material
		@return The material texture
		*/
		std::shared_ptr<Texture> get_texture()
		{ 
			return texture;
		}

		/**
		@brief Gets the base color
		@return The material base color
		*/
		glm::vec3 get_color()  
		{
			return color;
		}

		/**
		@brief Sets the material color
		@param color The color to set
		*/
		void set_color(glm::vec3 color) 
		{ 
			this->color = color;
		}


	};
}



