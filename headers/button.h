#ifndef __BUTTTON__H__
#define __BUTTTON__H__

#include "pch.h"
#include "pchSFML.h"

namespace sfte
{
    class Button : public sf::Drawable, public sf::Transformable
    {
    public:
        Button(const std::string &texturePath, const sf::Vector2f &position, const sf::Color &color, float width, float height = 0.f);
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

#endif //__BUTTTON__H__