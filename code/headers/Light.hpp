/*
 * File: Light.hpp
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
#include <glm.hpp>

namespace OpenGLAssignment
{
	class Light
	{	
			
		float intensity;

		float ambient_intensity;

		glm::vec3 light_color;

		glm::mat4 transform;

	public:
		

		/**
		@brief Creates an instance
		@param color The color of the light
		@param intensity The intensity of the light
		@param ambiental The ambient intensity
		*/
		Light(
				glm::vec3 color,
				float intensity = 1.f,
				float ambiental = 0.25f
			):
				transform(glm::mat4()),
				intensity(intensity),
				ambient_intensity(ambiental),
				light_color(color)
		{
			
		}
	
		/**
		@brief Set the color of the light
		@param color The color to set
		*/
		void set_color	(glm::vec3 & color)		
		{ 
			light_color = color;
		}

		/**
		@brief Set the ambient intensity
		@param value The ambient intensity to set
		*/
		void set_ambient_intensity	(float value)				
		{ 
			ambient_intensity = value;
		}

		/**
		@brief Set the intensity
		@param The intensity to set
		*/
		void set_intensity	(float value)
		{ 
			intensity = value;
		}

		/**
		@brief Gets the color of the light
		@retun The light color
		*/
		glm::vec3 & get_color() 
		{ 
			return light_color;
		}
		
		/**
		@brief Gets the light intensity
		@return The light intensity
		*/
		float get_intensity() 
		{ 
			return intensity;
		}
		
		/**
		@brief Gets the ambient intensity
		@return The ambient intensity
		*/
		float get_ambient_intensity() 
		{
			return ambient_intensity;
		}
		
		/**
		@brief Render. Update the lights values
		@param camera The reference of the camera
		*/
		void render(Camera& camera)
		{			
			auto light_shader = ShaderProgram::get_shader("lightShader");
			light_shader->use();					

			unsigned int light_position_id = light_shader->get_uniform_location("light.position");
			unsigned int light_color_id = light_shader->get_uniform_location("light.color");
			unsigned int ambient_id = light_shader->get_uniform_location("ambientIntensity");
			unsigned int intensity_id = light_shader->get_uniform_location("intensity");
			unsigned int view_id = light_shader->get_uniform_location("viewPosition");
			unsigned int color_id = light_shader->get_uniform_location("_Color");

			light_shader->set_variant_value(light_position_id, glm::vec3(1.f, 2.f, 1.f));
			light_shader->set_variant_value(light_color_id, glm::vec3(1.0f, 1.0f, 1.0f));
			light_shader->set_variant_value(ambient_id, get_ambient_intensity());
			light_shader->set_variant_value(intensity_id, get_intensity());
			light_shader->set_variant_value(view_id, camera.get_position());

			light_shader->set_variant_value(color_id, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		
	};
}

