/*
 * File: Scene.hpp
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


#include <memory>
#include <chrono>

#include <iostream>

#include <Window.hpp>
#include <RenderTask.hpp>
#include <ElevationMesh.hpp>

namespace OpenGLAssignment
{
	class Scene
	{
		
		Window window;

		Camera camera;
		
		RenderTask view;
		
		bool is_running = true;

	public:
		
        /**
        @brief Creates an instance
        @param name The name of the window
        @param widht The width of the window
        @param height The height of the window
        */
        Scene(
                std::string name, 
                unsigned int width,
                unsigned int height
             ):
                window(name, width, height),
                camera(Camera()),
                view(camera, width, height)
        {
        
            std::shared_ptr<ElevationMesh> terrain(new ElevationMesh("../../assets/heightmap/heightmap.tga", 96, 44));
            std::shared_ptr<Material> material = Material::get("lightShader", "../../assets/shaders/vertex/pointLightVertex", "../../assets/shaders/fragment/pointLightFragment", glm::vec3(1, 1, 1), "../../assets/textures/uv-checker-2.tga");
            std::shared_ptr<Model> terrain_model(new Model(terrain, material));
            
            glm::mat4 transform = terrain_model->get_transform();
            transform = glm::translate(transform, glm::vec3(-50.f, -10.f, -50.f));
            terrain_model->set_transform(transform);

            view.add_opaque_model("elevation", terrain_model);  
            
            std::shared_ptr<Mesh> cube (new Mesh("../../assets/meshes/Cube_obj.obj"));
            material = Material::get("lightShader", "../../assets/shaders/vertex/pointLightVertex", "../../assets/shaders/fragment/pointLightFragment", glm::vec3(1, 1, 1), "../../assets/textures/uv-checker-2.tga");
            std::shared_ptr<Model> cube_model (new Model(cube, material));
            
            transform = cube_model->get_transform();
            transform = glm::translate(transform, glm::vec3(0.f, 0.f, -20.f));
            cube_model->set_transform(transform);
            
            view.add_transparent_model("cube1", cube_model);

            std::shared_ptr<Mesh> cube2(new Mesh("../../assets/meshes/Cube_obj.obj"));           
            std::shared_ptr<Model> cube2_model(new Model(cube2, material));

            transform = cube2_model->get_transform();
            transform = glm::translate(transform, glm::vec3(0.f, -10.f, -15.f));
            cube2_model->set_transform(transform);

            view.add_transparent_model("cube2", cube2_model);          
           
        }
		
        /**
        @brief Scene loop
        */
        void run()
        {
            unsigned fps = 60;
            const sf::Time update = sf::seconds(1.f / float(fps));
            sf::Clock timer;

            auto last_time = sf::Time::Zero;
            auto now = timer.getElapsedTime();
            auto deltaTime = now - last_time;
            
            do
            {
                now = timer.getElapsedTime();

                input();
                
                camera.update(deltaTime.asSeconds());               
                
                glm::mat4 transform = view.get_model("cube1", false)->get_transform();
                transform = glm::rotate(transform, 0.03f, glm::vec3(1.f, 0.f, 0.f));
                view.get_model("cube1", false)->set_transform(transform);
                
                transform = view.get_model("cube2", false)->get_transform();
                transform = glm::rotate(transform, 0.03f, glm::vec3(0.f, 1.f, 0.f));
                view.get_model("cube2", false)->set_transform(transform);
                
                window.clear();
                render();

                deltaTime = now - last_time;
                last_time = now;

                window.swap_buffers();

                std::cout << "Camera x: " << std::to_string(camera.get_position()[0]) << std::endl;
                std::cout << "Camera y: " << std::to_string(camera.get_position()[1]) << std::endl;
                std::cout << "Camera z: " << std::to_string(camera.get_position()[2]) << std::endl;

            } while (is_running);
        
        }
		
        /**
        @brief Render the scene
        */
        void render()
        {
            view.render();
        }
	
        /**
        @brief Handle the input
        */
        void input()
        {
            sf::Event e;
            while (window.poll_event(e))
            {               
                switch (e.type)
                {
                case sf::Event::Closed:
                    is_running = false;
                    break;

                case sf::Event::KeyPressed:
                    switch (e.key.code)
                    {
                    case sf::Keyboard::Escape: is_running = false;  break;                                    
                    case sf::Keyboard::W: camera.set_y_displacement(+1); break;
                    case sf::Keyboard::S: camera.set_y_displacement(-1); break;
                    case sf::Keyboard::A: camera.set_x_displacement(-1); break;                        
                    case sf::Keyboard::D: camera.set_x_displacement(+1); break;                        
                    case sf::Keyboard::E: view.toggle_postproccess(); break;                        
                    }                
                break;

                case sf::Event::KeyReleased:
                {

                    switch (e.key.code)
                    {
                    case sf::Keyboard::W: camera.set_y_displacement(0); break;
                    case sf::Keyboard::S: camera.set_y_displacement(0); break;
                    case sf::Keyboard::A: camera.set_x_displacement(0); break;
                    case sf::Keyboard::D: camera.set_y_displacement(0); break;
                    }
                }

                break;

                }
            }
        }
	};
}


