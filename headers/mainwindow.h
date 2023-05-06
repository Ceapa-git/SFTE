#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

#include "pch.h"
#include "pchSFML.h"
#include <datafile.h>

#define WINDOW_NORMAL (0)
#define WINDOW_MAXIMIZED (1)
#define WINDOW_SWAP_STATE (2)

namespace sfte
{
    class Main_window
    {
    public:
        Main_window() : Main_window(800, 600, "Simple Fast Text Editor"){};
        Main_window(const Main_window &other) = delete;
        ~Main_window();
        explicit Main_window(unsigned int width, unsigned int height, std::string title);

        bool is_open();
        void poll_events();
        // TODO: void add_event_handler with storage of them

        void display();

        void set_state(int state = WINDOW_SWAP_STATE);

    private:
        sf::RenderWindow window;
        std::string title;

        // ! current
        sf::Vector2u size;
        sf::Vector2i position;
        // ! normal
        sf::Vector2u size_normal;
        sf::Vector2i position_normal;
        // ! maximized
        sf::Vector2u size_maximized;
        sf::Vector2i position_maximized;

        std::vector<sf::Drawable *> title_bar;
        sf::RectangleShape title_bar_background;

        // TODO: way to remember smallerwindow details
        std::vector<sf::Drawable> panels; // * temporary name

        int window_state;

    private:
        bool try_from_file();
        void mouse_resize(sf::Event& event);
    };
}

#endif //__MAINWINDOW__H__