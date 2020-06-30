/*
 * File: Texture2D.hpp
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

#include <Texture.hpp>
#include <glad/glad.h>

#include <map>
#include <string>

extern "C"
{
#include <targa.h>
}

namespace OpenGLAssignment
{
	class Texture2D : public Texture
	{
	
		static std::map<std::string, std::shared_ptr<Texture>> factory;

	public:
		
		/**
		@brief Get a texture by its path
		@param path The path of the texture
		@param wrap The wrap parameter
		@param filter The filter parameter
		@return The pointer to the texture
		*/
		static std::shared_ptr<Texture> get_texture(
													std::string path,
													Parameter wrap = Parameter::REPEAT,
													Parameter filter = Parameter::MIPMAP_LINEAR_FILTER
													)
		{
			if (factory.count(path) > 0) return factory[path];

			std::shared_ptr<Texture> texture(new Texture2D(path, wrap, filter));

			factory[path] = texture;		

			return texture;		
		}

	public:
		
		/**
		@brief Creates an instance
		@param path The path of the texture
		@param wrap The wrap parameter
		@param filter The filter parameter
		*/
		Texture2D(
					std::string path,
					Parameter wrap = Parameter::CLAMP_TO_EDGE,
					Parameter filter = Parameter::MIPMAP_LINEAR_FILTER
				)
		{
			std::shared_ptr<Texture> temp = load_texture(path, wrap, filter);

			if (temp.get() != 0) 
			{
				glEnable(GL_TEXTURE_2D);
				glGenTextures(1, &id);
				glBindTexture(GL_TEXTURE_2D, id);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);				

				glTexImage2D
				(
					GL_TEXTURE_2D,
					0,
					GL_RGBA,
					temp->get_width(),
					temp->get_height(),
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					temp->colors()
				);
			}

		}

		/**
		@brief Bind the texture to use it
		*/
		void bind() override
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}

		/**
		@brief Unbind the texture before use it
		*/
		void unbind() override
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}		
		
		std::shared_ptr<Texture> load_texture(
												std::string path,
												Parameter wrap = Parameter::CLAMP_TO_EDGE,
												Parameter filter = Parameter::MIPMAP_LINEAR_FILTER
											  )
		{
			tga_image image;

			std::shared_ptr<Texture> texture;

			const char* path_file = path.c_str();
			
			if (tga_read(&image, path_file) == TGA_NOERR)
			{
				texture.reset(new Texture(image.width, image.height));
				tga_convert_depth(&image, texture->bits_per_color());
				tga_swap_red_blue(&image);

				Texture::Color* pixels_begin = reinterpret_cast<Texture::Color*>(image.image_data);
				Texture::Color* pixels_end = pixels_begin + image.width * image.height;
				Texture::Color* buffer = texture->colors();

				while (pixels_begin < pixels_end)
				{
					*buffer++ = *pixels_begin++;
				}

				tga_free_buffers(&image);
			}

			return texture;		
		}

	};

}
