// // /*
// // ** EPITECH PROJECT, 2025
// // ** raytracer
// // ** File description:
// // ** Graphics
// // */

// // #pragma once

// // #include <SFML/Graphics.hpp>
// // #include "Utils/Color.hpp"
// // #include "Core/Scene.hpp"
// // #include "Renderer/Renderer.hpp"

// <<<<<<< Updated upstream
// namespace Raytracer {
//     /**
//      * @class Graphics
//      * @brief Handles the graphical display and user interaction for the raytracer.
//      *
//      * This class manages the SFML window, processes user input, and displays
//      * the rendered images. It provides the interface between the rendering system
//      * and the display/output system.
//      */
//     class Graphics {
//     public:
//         /**
//          * @brief Constructs a Graphics instance with specified dimensions.
//          * @param width The width of the display window in pixels.
//          * @param height The height of the display window in pixels.
//          */
//         Graphics(int width, int height);

//         /**
//          * @brief Main execution loop for the graphics system.
//          * @param scene The scene to render and display.
//          * @param renderer The renderer to use for generating images.
//          */
//         void run(Scene& scene, Renderer& renderer);

//     private:
//         /**
//          * @brief Handles user input for camera control.
//          * @param window Reference to the SFML window.
//          * @param scene Reference to the current scene.
//          */
//         void handleInput(sf::RenderWindow& window, Scene& scene);

//         /**
//          * @brief Updates the display with the rendered image.
//          * @param window Reference to the SFML window.
//          * @param image The 2D vector of colors representing the rendered image.
//          */
//         void updateDisplay(sf::RenderWindow& window, const std::vector<std::vector<Color>>& image);

//         /**
//          * @brief Processes SFML window events (close, resize, etc.).
//          * @param window Reference to the SFML window.
//          */
//         void processEvents(sf::RenderWindow& window);

//         /**
//          * @brief Converts the internal color matrix to an SFML Image.
//          * @param image The 2D vector of colors to convert.
//          * @return SFML Image containing the converted pixels.
//          */
//         sf::Image createSFImage(const std::vector<std::vector<Color>>& image);

//         /**
//          * @brief Updates camera position/orientation based on user input.
//          * @param camera Reference to the camera to modify.
//          * @return True if camera was modified, false otherwise.
//          */
//         bool updateCameraFromInput(Camera& camera);

//         int m_width;                ///< Width of the display window in pixels
//         int m_height;               ///< Height of the display window in pixels
//         const float m_moveSpeed;    ///< Camera movement speed multiplier
//         const float m_rotationSpeed; ///< Camera rotation speed multiplier
//         bool m_needsRedraw;         ///< Flag indicating if the scene needs redrawing
//     };
// }
// =======
// // namespace Raytracer {
// //     class Graphics {
// //     public:
// //         Graphics(int width, int height);
// //         void run(Scene& scene, Renderer& renderer);

// //     private:
// //         void handleInput(sf::RenderWindow& window, Scene& scene);
// //         void updateDisplay(sf::RenderWindow& window, const std::vector<std::vector<Color>>& image);
// //         void processEvents(sf::RenderWindow& window);
// //         sf::Image createSFImage(const std::vector<std::vector<Color>>& image);
// //         bool updateCameraFromInput(Camera& camera);

// //         int m_width;
// //         int m_height;
// //         const float m_moveSpeed = 10.0f;
// //         const float m_rotationSpeed = 2.0f;
// //         bool m_needsRedraw = true;
// //     };
// // }
// >>>>>>> Stashed changes
