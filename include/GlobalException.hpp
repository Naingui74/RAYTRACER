/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** GlobalException
*/

#ifndef GLOBALEXCEPTION_HPP_
#define GLOBALEXCEPTION_HPP_

#define EXIT_FAILURE_TECH 84 ///< Custom technical failure exit code

#include <exception>
#include <string>

/**
 * @class GlobalException
 * @brief Custom exception class for the Raytracer project.
 *
 * This exception class extends std::exception to provide custom error handling
 * with descriptive messages. It's used throughout the project to handle
 * various error conditions consistently.
 */
class GlobalException : public std::exception {
public:
    /**
     * @brief Constructs a GlobalException with an error message.
     * @param message The error description to be associated with this exception.
     */
    explicit GlobalException(const std::string &message) : _message(message) {
    }

    /**
     * @brief Gets the exception message.
     * @return C-style string containing the error message.
     * @note This override is marked noexcept as required by std::exception.
     */
    const char *what() const noexcept override {
            return _message.c_str();
    }

private:
    std::string _message; ///< Stores the exception message
};

#endif /* !GLOBALEXCEPTION_HPP_ */