#include "pch.h"
#include "pchSFML.h"

#include <logger.h>
#include "panel.h"

namespace sfte
{
    Panel::Panel(const Panel &other)
    {
        this->panel_background = other.panel_background;
        this->position = other.position;
        this->size = other.size;
    }

    Panel::Panel(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color)
    {
        this->position = position;
        this->size = size;
        this->panel_background.setFillColor(color);
        this->panel_background.setPosition(position);
        this->panel_background.setSize(size);
    }

    void Panel::set_positon(const sf::Vector2f &position)
    {
        this->position = position;
        this->panel_background.setPosition(position);
    }
    void Panel::set_size(const sf::Vector2f &size)
    {
        this->size = size;
        this->panel_background.setSize(size);
    }

    void Panel::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(this->panel_background, states);
    }
}