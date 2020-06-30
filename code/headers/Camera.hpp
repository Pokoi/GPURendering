/*
 * File: Scene.hpp
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

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace OpenGLAssignment
{	

	class Camera
	{
	private:

		float near_plane;
		float far_plane;
		
		float fov;
		float ratio;

		glm::mat4 transform;
		
		struct
		{
			float x_displacement = 0.f;
			float y_displacement = 0.f;
		} camera_movement;


	public:
		
		/**
		@brief Creates an instance
		@param near_plane The near plane to render
		@param far_plane The far plane to render
		@param fov The field of view
		@param ratio The aspect ratio
		*/
		Camera	(
					float near_plane = 0.1f, 
					float far_plane  = 1000.f, 
					float fov		 = 90.f, 
					float ratio		 = 1.f
				) : 
					transform(glm::mat4()),
					near_plane(near_plane),
					far_plane(far_plane),
					fov(fov), 
					ratio(ratio)
		{}

		/**
		@brief Gets the projection matrix
		@return The camera projection matrix
		*/
		glm::mat4 get_projection()  
		{ 
			return glm::perspective(fov, ratio, near_plane, far_plane);
		}

		/**
		@brief Gets the transformation of the camera
		@return The transformation matrix
		*/
		glm::mat4 get_transform()
		{
			return transform;
		}
		
		/**
		@brief Gets the position of the camera
		@return The camera position
		*/
		glm::vec3 get_position()
		{
			return glm::vec3{transform[3][0], transform[3][1] , transform[3][2] };
		}

		/**
		@brief Updates the camera position
		@param delta The time in seconds between fotograms
		*/
		void update(float delta)
		{
			
			transform = glm::translate(transform, glm::vec3(camera_movement.x_displacement * delta, 0, camera_movement.y_displacement * delta));
		}
		
		/**
		@brief Sets the x displacement for the camera movement
		@param value The displacement
		*/
		void set_x_displacement(float value)
		{
			camera_movement.x_displacement = value ;
		}

		/**
		@brief Sets the y displacement for the camera movement
		@param value The displacement
		*/
		void set_y_displacement(float value)
		{
			camera_movement.y_displacement = value ;
		}

	};
}



