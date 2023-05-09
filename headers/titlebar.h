#ifndef SFTE_TITLEBAR_H_INCLUDED
#define SFTE_TITLEBAR_H_INCLUDED

#include "pch.h"
#include "pchSFML.h"

#include "button.h"

#define TITLE_BAR (1)
#define BUTTON_MINIMIZE (2)
#define BUTTON_MAXIMIZE (3)
#define BUTTON_EXIT (4)

namespace sfte
{
    class Title_bar : public sf::Drawable
    {
    public:
        Title_bar() = delete;
        Title_bar(const Title_bar &) = delete;
        Title_bar &operator=(const Title_bar &) = delete;
        Title_bar(float width, float title_bar_height);
        ~Title_bar() {}

        void set_title(const std::string &title);
        void resize(float width);

        void press_button_mouse_over(sf::RenderWindow &window);
        int is_mouse_over(sf::RenderWindow &window) const;
        void press_button(int button);
        int pressed_button() const;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        std::string title;
        float title_bar_height;
        sfte::Button exit_button;
        sfte::Button maximize_button;
        sfte::Button minimize_button;
        sf::RectangleShape title_bar_background;
        sf::Font font;
        sf::Text title_lable;
        unsigned int padding = 3;
    };
}

#endif // SFTE_TITLEBAR_H_INCLUDED