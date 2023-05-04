#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

#include "pch.h"
#include "pchSFML.h"
#include <datafile.h>

namespace sfte
{
    typedef enum
    {
        MAXIMIZE,
        NORMAL,
        FULLSCREEN,
        KEEP // only for set state
    } window_state;
    class Main_window
    {
    public:
        Main_window() = delete;
        Main_window(const Main_window &other) = delete;
        ~Main_window();
        explicit Main_window(bool from_file = true, unsigned int width = 800, unsigned int heigth = 600, const char *title = "Simple Fast Text Editor");

        void set_state(window_state state = window_state::KEEP);

        bool is_open() const;
        void poll_events();
        // TODO: void add_event_handler with storage of them

        void display();

    private:
        sf::RenderWindow window;
        sf::Vector2u size;
        sf::Vector2i position;
        sf::Vector2u size_normal;
        sf::Vector2i position_normal;
        sf::Vector2u size_maximized;
        sf::Vector2i position_maximized;
        window_state state;

        std::unique_ptr<char[]> title;
        cge::data::Data_file data;

    private:
        bool try_from_file();
    };
}

#endif //__MAINWINDOW__H__