// // /*
// // ** EPITECH PROJECT, 2025
// // ** raytracer
// // ** File description:
// // ** Graphics
// // */

// // #include "Graphics/Graphics.hpp"

// <<<<<<< Updated upstream
// Raytracer::Graphics::Graphics(int width, int height)
//     : m_width(width), m_height(height), m_moveSpeed(0.1f), m_rotationSpeed(2.0f), m_needsRedraw(false) {}
// =======
// // Raytracer::Graphics::Graphics(int width, int height)
// //     : m_width(width), m_height(height) {}
// >>>>>>> Stashed changes

// // void Raytracer::Graphics::updateDisplay(sf::RenderWindow& window, const std::vector<std::vector<Color>>& image)
// // {
// //     sf::Image sfImage;
// //     sfImage.create(m_width, m_height);

// //     for (int y = 0; y < m_height; ++y) {
// //         for (int x = 0; x < m_width; ++x) {
// //             const Color& color = image[y][x];
// //             sfImage.setPixel(x, y, sf::Color(
// //                 static_cast<sf::Uint8>(color.getR()),
// //                 static_cast<sf::Uint8>(color.getG()),
// //                 static_cast<sf::Uint8>(color.getB())));
// //         }
// //     }
// //     sf::Texture texture;
// //     texture.loadFromImage(sfImage);
// //     sf::Sprite sprite(texture);

// //     window.clear();
// //     window.draw(sprite);
// //     window.display();
// // }

// // void Raytracer::Graphics::handleInput(sf::RenderWindow& window, Scene& scene)
// // {
// //     Camera& camera = scene.getCamera();
// //     Vector3 position = camera.getPosition();
// //     Vector3 rotation = camera.getRotation();

// <<<<<<< Updated upstream
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) 
//         position.z += m_moveSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
//         position.z -= m_moveSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) 
//         position.x -= m_moveSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
//         position.x += m_moveSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//         position.y += m_moveSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
//         position.y -= m_moveSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
//         rotation.y -= m_rotationSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
//         rotation.y += m_rotationSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
//         rotation.x -= m_rotationSpeed;
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
//         rotation.x += m_rotationSpeed;
// =======
// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) 
// //         position.z += m_moveSpeed;
// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
// //         position.z -= m_moveSpeed;
// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) 
// //         position.x -= m_moveSpeed;
// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
// //         position.x += m_moveSpeed;

// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
// //         rotation.y -= m_rotationSpeed;
// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
// //         rotation.y += m_rotationSpeed;
// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
// //         rotation.x -= m_rotationSpeed;
// //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
// //         rotation.x += m_rotationSpeed;
// >>>>>>> Stashed changes

// //     bool positionChanged = 
// //         position.x != camera.getPosition().x ||
// //         position.y != camera.getPosition().y ||
// //         position.z != camera.getPosition().z;
    
// //     bool rotationChanged = 
// //         rotation.x != camera.getRotation().x ||
// //         rotation.y != camera.getRotation().y ||
// //         rotation.z != camera.getRotation().z;

// //     if (positionChanged || rotationChanged) {
// //         camera.setPosition(position);
// //         camera.setRotation(rotation);
// //         m_needsRedraw = true;
// //     }
// // }

// // void Raytracer::Graphics::run(Scene& scene, Renderer& renderer)
// // {
// //     sf::RenderWindow window(sf::VideoMode(m_width, m_height), "Raytracer");
// //     window.setFramerateLimit(60);

// //     renderer.render();
// //     updateDisplay(window, renderer.getImage());
// //     m_needsRedraw = false;

// //     while (window.isOpen()) {
// //         sf::Event event;
// //         while (window.pollEvent(event)) {
// //             if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
// //                 window.close();
// //         }
// //         handleInput(window, scene);
// //         if (m_needsRedraw) {
// //             renderer.render();
// //             updateDisplay(window, renderer.getImage());
// //             m_needsRedraw = false;
// //         }
// //         sf::sleep(sf::milliseconds(10));
// //     }
// // }