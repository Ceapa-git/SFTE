#ifndef SFTE_BUTTON_H_INCLUDED
#define SFTE_BUTTON_H_INCLUDED

#include "pch.h"
#include "pchSFML.h"

namespace sfte
{
    class Button : public sf::Drawable, public sf::Transformable
    {
    public:
        Button() = delete;
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
        Button(const std::string &texture_path, const sf::Vector2f &position, const sf::Color &color, float width, float height = 0.f);
        ~Button() {}

        bool is_mouse_over(sf::RenderWindow &window) const;
        void set_pressed(bool state = true);
        bool is_pressed() const;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Texture texture;
        sf::Sprite sprite;
        bool pressed;
    };

}

#endif // SFTE_BUTTON_H_INCLUDED