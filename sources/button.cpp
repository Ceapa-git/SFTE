#include "pch.h"
#include "pchSFML.h"

#include "button.h"

namespace sfte
{
    Button::Button(const std::string &texture_path, const sf::Vector2f &position, const sf::Color &color, float width, float height)
    {
        if (height == 0.f)
            height = width;
        if (!this->texture.loadFromFile(texture_path))
            throw std::runtime_error("Failed to load texture: " + texture_path);
        this->sprite.setTexture(this->texture);
        this->sprite.setScale(width / this->texture.getSize().x, height / this->texture.getSize().y);
        this->sprite.setPosition(position);
        this->sprite.setColor(color);
    }

    bool Button::is_mouse_over(sf::RenderWindow &window) const
    {
        sf::FloatRect transformedBounds = getTransform().transformRect(sprite.getGlobalBounds());
        return transformedBounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    }
    void Button::set_pressed(bool state)
    {
        this->pressed = state;
    }
    bool Button::is_pressed() const
    {
        return this->pressed;
    }

    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(this->sprite, states);
    }
}