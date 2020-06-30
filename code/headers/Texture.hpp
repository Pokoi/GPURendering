/*
 * File: Texture.hpp
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
#include <SFML/Graphics.hpp>
#include <ColorRGBA8888.hpp>

#include <string>
#include <vector>

namespace OpenGLAssignment
{
	class Texture
	{
	public:
	
		enum Parameter 
		{
			//WRAP PARAMETERS
			REPEAT			= GL_REPEAT,
			MIRRORED		= GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,

			//FILTER PARAMETERS
			NEAR_PIXEL_FILTER		 = GL_NEAREST,
			LINEAR_FILTER			 = GL_LINEAR,
			MIPMAP_NEAR_PIXEL_FILTER = GL_LINEAR_MIPMAP_NEAREST,
			MIPMAP_LINEAR_FILTER	 = GL_LINEAR_MIPMAP_LINEAR
		};


	protected:
		typedef ColorRGBA8888 Color;
		
		GLenum id;		

		std::vector <ColorRGBA8888> texture_buffer;
		
		Color color;
		
		unsigned int width;
		
		unsigned int height;

	public:

		/**
		@brief Creates an instance
		*/
		Texture()
		{}
		
		/**
		@brief Creates an instance
		@param width The width of the texture
		@param height The height of the texture
		*/
		Texture(
				unsigned int width,
				unsigned int height
			   ) : 
				width(width),
				height(height),
				texture_buffer(width*height)
		{}
			
		/**
		@brief Load a texture file
		@param path The path of the file
		@param wrap The wrap parameter
		@param filter The filter parameter
		@return The texture
		*/
		virtual std::shared_ptr<Texture> load_texture(
														std::string path,
														Parameter wrap, 
														Parameter filter
													) 
		{ 
			return std::shared_ptr<Texture>();
		}

		/**
		@brief Binds the texture to use it
		*/
		virtual void bind() {}

		/**
		@brief Unbinds the texture before use it
		*/
		virtual void unbind() {}		

		/**
		@brief Gets the size of the texture buffer
		@return The texture buffer size
		*/
		size_t get_size() 
		{ 
			texture_buffer.size();
		}

		/**
		@brief Gets the id of the texture
		@return The id 
		*/
		GLenum get_id() 
		{ 
			return id;
		}
		
		/**
		@brief Gets the width of the texture
		@return The texture width
		*/
		unsigned int get_width()
		{
			return width;
		}

		/**
		@brief Gets the height of the texture
		@return The height of the texture
		*/
		unsigned int get_height()
		{
			return height;
		}

	public:
		
		/**
		@brief Gets a pointer to the first element in the texture buffer
		@return A pointer to the first elemen in buffer
		*/
		Color * colors()
		{
			return (&texture_buffer.front());
		}			 

		/**
		@brief Gets the bits per color
		@return The bits per color
		*/
		int bits_per_color() 	
		{
			return (sizeof(Color) * 8);
		}

		/**
		@brief Gets the size of the buffer
		@return The size of the buffer
		*/
		size_t size()
		{
			return (texture_buffer.size());
		}

		/**
		@brief Set the color
		@param r The r component to set
		@param g The g component to set
		@param b The b component to set
		*/
		void set_color(int r, int g, int b)
		{
			color.data.component.r = uint8_t(r < 0 ? 0 : r > 255 ? 255 : r);
			color.data.component.g = uint8_t(g < 0 ? 0 : g > 255 ? 255 : g);
			color.data.component.b = uint8_t(b < 0 ? 0 : b > 255 ? 255 : b);
			color.data.component.a = 0xFF;
		}

		/**
		@brief Set the color
		@param new_color The color to set
		*/
		void set_color(Color & new_color)
		{
			color = new_color;
		}

		/**
		@brief Set a pixel
		@param offset The pixel 
		*/
		void set_pixel(size_t offset)
		{
			texture_buffer[offset] = color;
		}

		/**
		@brief Set a pixel
		@param x The x coordinate of the pixel
		@param y The y coordinate of the pixel 
		*/
		void set_pixel(int x, int y)
		{
			texture_buffer[y * width + x] = color;
		}		

	};
}

