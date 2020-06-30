/*
 * File: Mesh.cpp
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

#include <Mesh.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace OpenGLAssignment
{
    Mesh::Mesh(std::string file_path)
    {
        std::vector<GLfloat> vertex;
        std::vector<GLfloat> texcoord;
        std::vector<GLfloat> normals;

        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        tinyobj::attrib_t attributes;

        std::string log_error;

        if (tinyobj::LoadObj(&attributes, &shapes, &materials, &log_error, file_path.c_str(), 0, true))
        {
            vertex = attributes.vertices;
            texcoord = attributes.texcoords;
            normals = attributes.normals;
            indices.resize(shapes[0].mesh.indices.size());

            for (size_t i = 0; i < indices.size(); ++i)
            {
                indices[i] = shapes[0].mesh.indices[i].vertex_index;
            }
        }

        vao.reset(new VertexArrayObject);
        vao->bind();

        vertex_buffer.reset(new VertexBufferObject(&vertex[0], vertex.size() * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, vertex_buffer->get_element_type(), GL_FALSE, 3 * sizeof(GLfloat), 0);

        if (texcoord.size() > 0)
        {
            texcoord_buffer.reset(new VertexBufferObject(&texcoord[0], texcoord.size() * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, texcoord_buffer->get_element_type(), GL_FALSE, 2 * sizeof(GLfloat), 0);
        }

        normals_buffer.reset(new VertexBufferObject(&normals[0], normals.size() * sizeof(GLfloat)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, normals_buffer->get_element_type(), GL_FALSE, 3 * sizeof(GLfloat), 0);

        indices_buffer.reset(new VertexBufferObject(&indices[0], indices.size() * sizeof(GLubyte), VertexBufferObject::EAB));

        vao->unbind();
    }
}