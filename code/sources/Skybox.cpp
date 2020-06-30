/*
 * File: Skybox.cpp
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

#include <glad/glad.h>
#include <Skybox.hpp>
#include <VertexShader.hpp>
#include <FragmentShader.hpp>
#include <glm.hpp>
#include <assert.h>


namespace OpenGLAssignment
{	
	
	Skybox::Skybox (std::string path)
					:
					texture(path), 
					shader(new ShaderProgram)
	{
		
		const GLfloat coordinates[] =
		{
			-1.0f, +1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			+1.0f, -1.0f, -1.0f,
			+1.0f, -1.0f, -1.0f,
			+1.0f, +1.0f, -1.0f,
			-1.0f, +1.0f, -1.0f,
			-1.0f, -1.0f, +1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, +1.0f, -1.0f,
			-1.0f, +1.0f, -1.0f,
			-1.0f, +1.0f, +1.0f,
			-1.0f, -1.0f, +1.0f,
			+1.0f, -1.0f, -1.0f,
			+1.0f, -1.0f, +1.0f,
			+1.0f, +1.0f, +1.0f,
			+1.0f, +1.0f, +1.0f,
			+1.0f, +1.0f, -1.0f,
			+1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, +1.0f,
			-1.0f, +1.0f, +1.0f,
			+1.0f, +1.0f, +1.0f,
			+1.0f, +1.0f, +1.0f,
			+1.0f, -1.0f, +1.0f,
			-1.0f, -1.0f, +1.0f,
			-1.0f, +1.0f, -1.0f,
			+1.0f, +1.0f, -1.0f,
			+1.0f, +1.0f, +1.0f,
			+1.0f, +1.0f, +1.0f,
			-1.0f, +1.0f, +1.0f,
			-1.0f, +1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, +1.0f,
			+1.0f, -1.0f, -1.0f,
			+1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, +1.0f,
			+1.0f, -1.0f, +1.0f,
		};

		shader->attach(VertexShader(Shader::SourceCode::from_file("../../assets/shaders/SkyboxVertex.shader")));
		shader->attach(FragmentShader(Shader::SourceCode::from_file("../../assets/shaders/SkyboxFragment.shader")));

		shader->link();
		
		vao.reset(new VertexArrayObject);

		vao->bind();
		vbo.reset(new VertexBufferObject(coordinates, sizeof(coordinates)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, vbo->get_element_type(), GL_FALSE, 0, 0);
		vao->unbind();
	}

	void Skybox::render(Camera & camera)
	{
		shader->use();

		texture.bind();

		glm::mat4 model_view_matrix = camera.get_transform();
		//model_view_matrix = glm::translate(model_view_matrix, camera.get_position());

		glm::mat4 projection = camera.get_projection();

		unsigned int model_view_matrix_id = shader->get_uniform_location("model_view_matrix");
		unsigned int projection_matrix_id = shader->get_uniform_location("projection_matrix");

		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));
		glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection));

		glDepthMask(GL_FALSE);

		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		vao->unbind();

		glDepthMask(GL_TRUE);

		shader->disable();
	}
}
