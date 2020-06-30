/*
 * File: ElevationMesh.hpp
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

#include <vector>
#include <string>

namespace OpenGLAssignment
{
	class ElevationMesh :public Mesh
	{	
	 
		std::vector<GLfloat> vertex;
		
		std::vector<GLfloat> normals;

		std::vector<GLfloat> texcoord;
		
		std::vector<GLuint> indices;

	public:
		
        /**
        @brief Creates an instance
        @param path_file The path of the heightmap file
        @param width The width of the surface to create
        @param height The height of the surface to create
        */
		ElevationMesh(std::string path_file,unsigned int width, unsigned int height);

        /**
        @brief Render the surface
        */
		void render()
		{
			vao->bind();
			glDrawElements(GL_TRIANGLES, GLsizei(sizeof(indices) * indices.size()), GL_UNSIGNED_INT, 0);
		}

        /**
        @brief Calculate the normal vertex
        */
		glm::vec3 calculate_normal(unsigned int width, unsigned int height, size_t i, size_t index);

        /**
        @brief Converts a given vector of floats to glm vec3 structure
        @param vector1 de float vector to convert
        @return The converted vector
        */
        std::vector<glm::vec3> to_glm_vector(std::vector<float>& vector1)
        {
            bool check = vector1.size() % 3 == 0;
            assert(check);

            std::vector<glm::vec3> result;
            result.resize(vector1.size() / 3);

            for (size_t i = 0, j = 0; i < result.size(); ++i, j += 3)
            {
                result[i] = { vector1[j],vector1[j + 1] ,vector1[j + 2] };
            }

            return result;
        }

	};
}

