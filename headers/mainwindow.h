#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

#include "pch.h"
#include "pchSFML.h"
#include <datafile.h>

#define WINDOW_NORMAL       (0)
#define WINDOW_MAXIMIZED    (1)
#define WINDOW_FULLSCREEN   (2)

namespace sfte
{
    class Main_window
    {
    public:
        Main_window() : Main_window(800, 600, "Simple Fast Text Editor"){};
        Main_window(const Main_window &other) = delete;
        ~Main_window();
        explicit Main_window(unsigned int width, unsigned int heigth, std::string title);

        bool is_open();
        void poll_events();
        // TODO: void add_event_handler with storage of them

        void display();

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

        int window_state;

        cge::data::Data_file data;

    private:
        bool try_from_file(); // TODO: broken
    };
}

#endif //__MAINWINDOW__H__