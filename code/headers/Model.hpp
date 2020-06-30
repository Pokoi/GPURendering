/*
 * File: Model.hpp
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

#include <Mesh.hpp>
#include <Material.hpp>
#include <Camera.hpp>

#include <vector>


namespace OpenGLAssignment
{
	class Model
	{
		
		std::shared_ptr<Mesh> mesh;

		std::shared_ptr<Material> material;		
		
		glm::mat4 transform;
		
		Model * parent;

	public:
				
		/**
		@brief Creates an instance
		@param parent The parent
		*/
		Model(Model* parent = nullptr) : parent{parent}
		{
		
		}

		/**
		@brief Creates an instance
		@param mesh The mesh of the model
		@param material The material of the model
		@param parent the parent of the model
		*/
		Model(
				std::shared_ptr<Mesh> mesh, 
				std::shared_ptr<Material> material, 
				Model* parent = nullptr
			 ) : 
				mesh{mesh},
				material{material},
				parent{parent}
		{}

		/**
		@brief Get the transformation matrix of the model
		@return The transformation matrix
		*/
		glm::mat4 get_transform()
		{
			if (parent) return transform * parent->get_transform();
			return transform;
		}		

		/**
		@brief Set the transformation matrix of the model
		@param transform The transformation matrix to set
		*/
		void set_transform(glm::mat4 transform)
		{
			this->transform = transform;
		}

		/**
		@brief Set the material of the model
		@param mat The material to set
		*/
		void set_material(std::shared_ptr<Material> mat)
		{
			material = mat;
		}

		/**
		@brief Set the mesh of the model
		@param mesh The mesh of the model
		*/
		void set_mesh(std::shared_ptr<Mesh> mesh)
		{
			this->mesh = mesh;
		}
		
		/**
		@brief Render the model
		@param camera A reference to the scene camera
		*/
		void render(Camera* camera)
		{
			glm::mat4 model_view_matrix = camera->get_transform();

			model_view_matrix = model_view_matrix * transform;
			
			material->get_shader()->use();

			unsigned int model_view_id		= material->get_shader()->get_uniform_location("model_view_matrix");
			unsigned int projection_view_id = material->get_shader()->get_uniform_location("projection_matrix");

			glUniformMatrix4fv(model_view_id, 1, GL_FALSE, glm::value_ptr((model_view_matrix)));
			glUniformMatrix4fv(projection_view_id, 1, GL_FALSE, glm::value_ptr((camera->get_projection())));
			
			material->get_texture()->bind();	

			mesh->render();

			material->get_texture()->unbind();
		}

		/**
		@brief Get the position of the model
		@return The position of the model
		*/
		glm::vec3 get_position() 
		{
			return glm::vec3(transform[3][0], transform [3][1], transform [3][2]);
		}	
		
		/**
		@brief Get the material of the model
		@return The material of the model
		*/
		std::shared_ptr<Material> get_material() 
		{ 
			return material;
		}
	
	};
}


