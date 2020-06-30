/*
 * File: Skybox.hpp
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
#include <TextureCubemap.hpp>
#include <ShaderProgram.hpp>
#include <VertexArrayObject.hpp>
#include <VertexBufferObject.hpp>

namespace OpenGLAssignment
{
	class Skybox
	{
	private:
		
		std::shared_ptr<VertexArrayObject> vao;
		
		std::shared_ptr<VertexBufferObject> vbo;	
		
		TextureCubemap texture;
		
		std::shared_ptr<ShaderProgram> shader;

	public:
		
        /**
        @brief Creates an instance
        @param path The path of the texture of the skybox
        */
		Skybox(std::string path);
        		
        /**
        @brief Render the skybox
        @param camera A reference to the scene camera
        */
		void render(Camera & camera);
	};
}


