/*
 * File: Mesh.hpp
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
#include <VertexArrayObject.hpp>
#include <VertexBufferObject.hpp>

#include <glm.hpp>

#include <memory>

#include <tiny_obj_loader.h>

namespace OpenGLAssignment
{
	class Mesh
	{
	protected:
		
		
		std::shared_ptr<VertexArrayObject> vao;
		
		std::shared_ptr<VertexBufferObject> vertex_buffer;
		
		std::shared_ptr<VertexBufferObject> texcoord_buffer;
		
		std::shared_ptr<VertexBufferObject> normals_buffer;
		
		std::shared_ptr<VertexBufferObject> indices_buffer;

        std::vector<GLubyte> indices;

	public:

        /**
        @brief Creates an instance
        */
        Mesh()
        {}

        /**
        @brief Creates an instance from a .obj file
        @param file_path The path of the obj file
        */
        Mesh(std::string file_path);

        /**
        @brief Render the mesh
        */
		virtual void render() 
        {
            vao->bind();
            glDrawElements(GL_TRIANGLES, GLsizei(sizeof(GLubyte) * indices.size()), GL_UNSIGNED_BYTE, 0);
        }

        /**
        @brief Set the VAO of the mesh
        @param new_vao The vao to set
        */
		void set_vao(std::shared_ptr<VertexArrayObject> new_vao) 
        { 
            vao = new_vao;
        }

        /**
        @brief Set the vertex coordinates information 
        @param vertex The vertex coordinates data
        */
		void set_vertex(std::shared_ptr<VertexBufferObject> vertex) 
        { 
            vertex_buffer = vertex;
        }

        /**
        @brief Set the texture coordinates information
        @param textcoord The texture coordinates data
        */
		void set_texcoord(std::shared_ptr<VertexBufferObject> texcoord) 
        { 
            texcoord_buffer = texcoord;
        }

        /**
        @brief Set the normals information
        @param normals The normals data
        */
		void set_normals(std::shared_ptr<VertexBufferObject> normals)
        {
            normals_buffer = normals;
        }

        /**
        @brief Set the indices information
        @param indices The indices data
        */
		void set_indices(std::shared_ptr<VertexBufferObject> indices) 
        { 
            indices_buffer = indices;
        }

	};
}




