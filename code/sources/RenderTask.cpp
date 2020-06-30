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


#include <RenderTask.hpp>
#include <SFML/OpenGL.hpp>

#include <ShaderProgram.hpp>
#include <Material.hpp>
#include <Framebuffer.hpp>

namespace OpenGLAssignment
{
	RenderTask::RenderTask(
							Camera & camera, 
							unsigned int width,
							unsigned int height
						  ) :
							camera(&camera),
							width(width),
							height(height),
							skybox(new Skybox("../../assets/skybox/")),
							light(new Light(glm::vec3(1.f,1.f,1.f)))
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);		
		
		ShaderProgram::create_shader("lightShader", "../../assets/shaders/pointLightVertex", "../../assets/shaders/pointLightFragment");
		ShaderProgram::create_shader("postprocess", "../../assets/shaders/postprocessVertex", "../../assets/shaders/postprocessFragment");
		
		framebuffer = new Framebuffer(width, height, "postprocess");
		framebuffer->build();		
	}

	void RenderTask::render()
	{
		if (is_postproccess_active) framebuffer->bind();
		
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		
		skybox->render(*camera);
		light->render(*camera);

		// Opaque models
		for (auto & model : opaque_models)
		{
			model.second->render(camera);
		}

		// Transparent models
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		for (auto & model : transparent_models)
		{
			model.second->render(camera);
		}
		glDisable(GL_BLEND);
		glFlush();
		
		if(is_postproccess_active) framebuffer->render();
	}

}