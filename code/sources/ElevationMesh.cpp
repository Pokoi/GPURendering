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

#include <ElevationMesh.hpp>

#include <ColorRGBA8888.hpp>
#include <assert.h>

#include <iostream>

extern "C"
{
#include <targa.h>
}

namespace OpenGLAssignment
{
	ElevationMesh::ElevationMesh(std::string path_file,unsigned int width, unsigned int height)
	{		
		tga_image image;

		std::vector<ColorRGBA8888> colors;

		if (tga_read(&image, path_file.c_str()) == TGA_NOERR)
		{
			colors.resize(image.width * image.height);
			tga_convert_depth(&image, sizeof(ColorRGBA8888) * 8);

			ColorRGBA8888 * begin = reinterpret_cast<ColorRGBA8888*>(image.image_data);
			ColorRGBA8888 * end = begin + image.width * image.height;
			ColorRGBA8888 * buffer = &colors.front();

			while (begin < end)
				*buffer++ = *begin++;

		}
		else
			assert(false);
				
		
		vertex.resize(width * height * 3);
		normals.resize(width * height * 3);
		texcoord.resize(width * height * 2);
		indices.resize(2 * (width - 1) * (height - 1) * 3);

		float elevation = 0;
		float increment = image.width / float(width);

		size_t index = 0;
		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j, index += 3, elevation += increment)
			{
				vertex[index] = j;
				vertex[index + 1] = (colors[size_t(elevation)].data.component.r / float(255)) * 10.f;
				vertex[index + 2] = i;
			}
		}

		index = 0;
		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j, index += 2)
			{
				texcoord[index] = j / float((width - 1));
				texcoord[index + 1] = i / float((height - 1));
			}
		}
				
		index = 0;
		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j, index += 3)
			{
				glm::vec3 n = calculate_normal(width, height, i, index / 3);
				normals[index] = n[0];
				normals[index + 1] = n[1];
				normals[index + 2] = n[2];					
			}
		}

		index = 0;
		for (size_t i = 0, k = 0; i < height - 1; ++i)
		{
			for (size_t j = 0; j < width - 1; ++j, ++k, index += 6)
			{
				indices[index] = k;
				indices[index + 1] = k + width;
				indices[index + 2] = k + 1;

				indices[index + 3] = k + 1;
				indices[index + 4] = k + width;
				indices[index + 5] = k + 1 + width;
			}
			++k;
		}

		tga_free_buffers(&image);

		//VAO y VBOs

		vao.reset(new VertexArrayObject);
		vao->bind();

		vertex_buffer.reset(new VertexBufferObject(&vertex[0], vertex.size() * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, vertex_buffer->get_element_type(), GL_FALSE, 3 * sizeof(GLfloat), 0);

		texcoord_buffer.reset(new VertexBufferObject(&texcoord[0], sizeof(texcoord)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, texcoord_buffer->get_element_type(), GL_FALSE, 2 * sizeof(GLfloat), 0);

		normals_buffer.reset(new VertexBufferObject(&normals[0], normals.size() * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, normals_buffer->get_element_type(), GL_FALSE, 3 * sizeof(GLfloat), 0);

		indices_buffer.reset(new VertexBufferObject(&indices[0], indices.size() * sizeof(GLuint), VertexBufferObject::EAB));

		vao->unbind();

	}

	glm::vec3 ElevationMesh::calculate_normal(unsigned int width, unsigned int height, size_t i, size_t index)
	{
		glm::vec3 result = glm::vec3();
		std::vector<glm::vec3> near_points;
		std::vector<glm::vec3> vertices = to_glm_vector(vertex);

		const glm::vec3 & point = vertices[index];
		size_t vertex_count = vertex.size() / 3;

		size_t start = i * height;
		size_t end = i * height + (width - 1);

		// Special cases
		
		int temp = index - width;
		if (temp > 0)
		{
			glm::vec3 aux = vertices[index - width];
			glm::vec3 new_point = aux - point;
			near_points.push_back(glm::normalize(new_point));
		}
		
		if (index - 1 > 0)
		{
			if (index > start && index < end)
			{
				glm::vec3 aux = vertices[index - 1];
				glm::vec3 new_point = aux - point;
				near_points.push_back(glm::normalize(new_point));
			}
		}
		
		if ((index + width - 1) > 0 && (index + width - 1 < vertex_count - 1))
		{
			if (!(index > start && index < end))
			{
				glm::vec3 aux = vertices[(index + width) - 1];
				glm::vec3 new_point = aux - point;
				near_points.push_back(glm::normalize(new_point));
			}
		}
		
		if (index + width > 0 && index + width < vertex_count - 1)
		{
			glm::vec3 aux = vertices[index + width];
			glm::vec3 new_point = aux - point;
			near_points.push_back(glm::normalize(new_point));
		}
		
		if (index + 1 > 0 && index + 1 < vertex_count - 1)
		{
			if (index > start && index < end)
			{
				glm::vec3 aux = vertices[index+1];
				glm::vec3 new_point = aux - point;
				near_points.push_back(glm::normalize(new_point));
			}
		}
		
		temp = index - width + 1;
		if (temp > 0)
		{
			if (!(index > start && index < end))
			{
				glm::vec3 aux = vertices[index - width +1];
				glm::vec3 new_point = aux - point;
				near_points.push_back(glm::normalize(new_point));
			}
		}		

		std::vector<glm::vec3> products;

		for (size_t j = 0; j < near_points.size() - 1; ++j)
		{
			glm::vec3 & vec1 = near_points[j];
			glm::vec3 & vec2 = near_points[j+1];

			products.push_back(glm::cross(vec1, vec2));
		}

		if (near_points.size() > 1)
		{
			glm::vec3 & begin = near_points[0];
			glm::vec3 & end = near_points[near_points.size() - 1];

			products.push_back(glm::cross(begin, end));
		}		

		for (size_t k = 0; k < products.size(); ++k)
		{
			result += products[k];
		}

		result /= products.size();

		return glm::normalize(result);
	}
	
}