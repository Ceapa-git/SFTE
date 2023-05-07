#include "pch.h"
#include "pchSFML.h"

#include <logger.h>
#include "titlebar.h"
#include "button.h"

namespace sfte
{
    Title_bar::Title_bar(const std::string &title, float width, float title_bar_height)
        : exit_button("res\\circle_button.png", sf::Vector2f(width - 1.5f * title_bar_height, 0.f), sf::Color::Red, title_bar_height),
          maximize_button("res\\circle_button.png", sf::Vector2f(width - 2.5f * title_bar_height, 0.f), sf::Color::Green, title_bar_height),
          minimize_button("res\\circle_button.png", sf::Vector2f(width - 3.5f * title_bar_height, 0.f), sf::Color::Yellow, title_bar_height)
    {
        this->title = title;
        this->title_bar_height = title_bar_height;
        this->title_bar_background.setSize(sf::Vector2f(width, this->title_bar_height));
        this->title_bar_background.setPosition(0.f, 0.f);
        this->title_bar_background.setFillColor(sf::Color(133, 129, 119));
        this->title_bar_background.setOutlineThickness(0.f);
    }

    void Title_bar::resize(float width)
    {
        this->title_bar_background.setSize(sf::Vector2f(width, this->title_bar_height));
        this->minimize_button.setPosition(sf::Vector2f(width - 3.5f * this->title_bar_height, 0.f));
        this->maximize_button.setPosition(sf::Vector2f(width - 2.5f * this->title_bar_height, 0.f));
        this->exit_button.setPosition(sf::Vector2f(width - 1.5f * this->title_bar_height, 0.f));
    }

    void Title_bar::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        this->minimize_button.draw(target, states);
        this->maximize_button.draw(target, states);
        this->exit_button.draw(target, states);
    }

}