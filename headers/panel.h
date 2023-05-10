#ifndef SFTE_PANEL_H_INCLUDED
#define SFTE_PANEL_H_INCLUDED

#include "pch.h"
#include "pchSFML.h"

namespace sfte
{
    class Panel : public sf::Drawable
    {
    public:
        Panel() : Panel(sf::Vector2f(), sf::Vector2f()){};
        Panel(const Panel &other);
        Panel(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color = sf::Color::White);
        ~Panel(){};

        void set_positon(const sf::Vector2f &position);
        void set_size(const sf::Vector2f &size);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    protected:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::RectangleShape panel_background;
    };
}

#endif // SFTE_PANEL_H_INCLUDED