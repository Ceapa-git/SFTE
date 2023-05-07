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
        target.draw(this->title_bar_background, states);
        target.draw(this->minimize_button, states);
        target.draw(this->maximize_button, states);
        target.draw(this->exit_button, states);
    }

    void Title_bar::press_button_mouse_over(sf::RenderWindow &window)
    {
        int button = this->is_mouse_over(window);
        this->press_button(button);
    }
    int Title_bar::is_mouse_over(sf::RenderWindow &window) const
    {
        if (!this->title_bar_background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            return 0;

        if (this->minimize_button.is_mouse_over(window))
            return BUTTON_MINIMIZE;
        if (this->maximize_button.is_mouse_over(window))
            return BUTTON_MAXIMIZE;
        if (this->exit_button.is_mouse_over(window))
            return BUTTON_EXIT;

        return TITLE_BAR;
    }
    void Title_bar::press_button(int button)
    {
        if (button == BUTTON_MINIMIZE)
            this->minimize_button.set_pressed();
        else if (button == BUTTON_MAXIMIZE)
            this->maximize_button.set_pressed();
        else if (button == BUTTON_EXIT)
            this->exit_button.set_pressed();
        else
        {
            this->minimize_button.set_pressed(false);
            this->maximize_button.set_pressed(false);
            this->exit_button.set_pressed(false);
        }
    }
    int Title_bar::pressed_button() const
    {
        if (this->minimize_button.is_pressed())
            return BUTTON_MINIMIZE;
        else if (this->maximize_button.is_pressed())
            return BUTTON_MAXIMIZE;
        else if (this->exit_button.is_pressed())
            return BUTTON_EXIT;
        return 0;
    }

}