#ifndef __TITLEBAR__H__
#define __TITLEBAR__H__

#include "pch.h"
#include "pchSFML.h"

#include "button.h"

namespace sfte
{
    class Title_bar : public sf::Drawable
    {
    public:
        Title_bar() = delete;
        Title_bar(const Title_bar &) = delete;
        Title_bar &operator=(const Title_bar &) = delete;
        Title_bar(const std::string &title, float width, float title_bar_height);
        ~Title_bar() {}

        void resize(float width);
        // TODO: is mouse over button
        // TODO: is mouse over bar

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        std::string title;
        float title_bar_height;
        sfte::Button exit_button;
        sfte::Button maximize_button;
        sfte::Button minimize_button;
        sf::RectangleShape title_bar_background;
    };
}

#endif //__TITLEBAR__H__