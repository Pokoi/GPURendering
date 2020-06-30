/*
 * File: RenderTask.cpp
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

#include <Camera.hpp>
#include <Skybox.hpp>
#include <Model.hpp>
#include <Light.hpp>
#include <Framebuffer.hpp>

#include <vector>
#include <map>

namespace OpenGLAssignment
{
	class RenderTask
	{	
		
		Camera * camera;
		
		Skybox * skybox;
		
		Light * light;
		
		Framebuffer* framebuffer;
		
		bool is_postproccess_active = false;
		
		unsigned int width;

		unsigned int height;
		
		std::map<std::string, std::shared_ptr<Model>> opaque_models;
		
		std::map<std::string, std::shared_ptr<Model>> transparent_models;


	public:
	
		/**
		@brief Creates an instance
		@param camera A reference to the camera of the scene
		@param width The width of the view
		@param height The height of the view
		*/
		RenderTask(Camera & camera, unsigned int width, unsigned int height);
		
		/**
		@brief Render the scene
		*/
		void render();

		/**
		@brief Activates or inactivates the postproccess in a switch way 
		*/
		void toggle_postproccess()
		{
			is_postproccess_active = !is_postproccess_active;
		}

		/**
		@brief Adds an opaque model to the collection
		@param name The name of the model
		@param model The model to add
		*/
		void add_opaque_model(std::string name, std::shared_ptr<Model> model)
		{
			opaque_models[name] = model;
		}

		/**
		@brief Adds a transparent model to the collection
		@param name The name of the model
		@param model The model to add
		*/
		void add_transparent_model(std::string name, std::shared_ptr<Model> model)
		{
			transparent_models[name] = model;
		}

		/**
		@brief Adds a light to the scene 
		@param light The light to add
		*/
		void add_light(Light& light)
		{
			this->light = &light;
		}

		/**
		@brief Gets a model by name
		@param name The name of the model
		@param opaque If the model is opaque or transparent. True = opaque, false = transparen
		@return A reference to the desired model
		*/
		std::shared_ptr<Model> & get_model(std::string name, bool opaque)
		{
			if (opaque) return opaque_models[name];
			else return transparent_models[name];
		}

	};
}
