/*
 * File: ShaderProgram.cpp
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


#include <ShaderProgram.hpp>
#include <VertexShader.hpp>
#include <FragmentShader.hpp>

namespace OpenGLAssignment
{
	std::map<std::string, std::shared_ptr<ShaderProgram>> ShaderProgram::factory;

	std::shared_ptr<ShaderProgram> ShaderProgram::create_shader(std::string name, std::string vertex_shader_path, std::string fragment_shader_path)
	{
		
		if (factory.count(name) > 0)
			return factory[name];

		
		std::shared_ptr<ShaderProgram> shader(new ShaderProgram);
		
		shader->attach(VertexShader(Shader::SourceCode::from_file(vertex_shader_path + ".shader")));
		shader->attach(FragmentShader(Shader::SourceCode::from_file(fragment_shader_path + ".shader")));
		shader->link();
		
		factory[name] = shader;		

		return shader;
	}

	std::shared_ptr<ShaderProgram> ShaderProgram::get_shader(std::string name)
	{
		if (factory.count(name) > 0)
		{
			return factory[name];
		}

		return std::shared_ptr<ShaderProgram>();
	}

}