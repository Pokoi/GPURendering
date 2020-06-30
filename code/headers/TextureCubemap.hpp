/*
 * File: TextureCubemap.hpp
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

extern "C"
{
#include <targa.h>
}

namespace OpenGLAssignment
{
	class TextureCubemap :public Texture
	{
	public:
		
        /**
        @brief Creates an instance
        @param path The path of the texture
        */
		TextureCubemap( std::string path);
		
        /**
        @brief Frees the memory
        */
        ~TextureCubemap()
        {
            glDeleteTextures(1, &id);
        }

	public:
		
        /**
        @brief Load a texture
        @param path The file path of the texture
        @return The texture
        */
        std::shared_ptr<Texture> load_texture(std::string path)
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
		
        /**
        @brief Binds a texture to use it
        */
		void bind() override 
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, id);
		}
        
        /**
        @brief Unbinds a texture before use it
        */
		void unbind() override 
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}


	};
}
