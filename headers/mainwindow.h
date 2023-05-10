#ifndef SFTE_MAINWINDOW_H_INCLUDED
#define SFTE_MAINWINDOW_H_INCLUDED

#include "pch.h"
#include "pchSFML.h"

#include <datafile.h>
#include "button.h"
#include "titlebar.h"
#include "panel.h"

#define WINDOW_STATE_NORMAL (0)
#define WINDOW_STATE_MAXIMIZED (1)
#define WINDOW_STATE_SWAP (2)

namespace sfte
{
    class Main_window
    {
    public:
        Main_window() : Main_window(800, 600, "Simple Fast Text Editor"){};
        Main_window(const Main_window &) = delete;
        Main_window &operator=(const Main_window &) = delete;
        ~Main_window();
        explicit Main_window(unsigned int width, unsigned int height, std::string title);

        bool is_open();
        void poll_events();
        // TODO: void add_event_handler with storage of them

        void display();

        void set_state(int state = WINDOW_STATE_SWAP);

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

        Title_bar title_bar;

        // TODO: way to remember smallerwindow details
        std::vector<Panel> panels; // * temporary name

        int window_state;

    private:
        bool try_from_file();

        void mouse_resize_window(sf::Event &event);
        bool can_resize = false;
        bool resizing = false;
        bool horizontal_resize = false, vertical_resize = false;
        bool left_resize = false, top_resize = false;
        sf::Vector2i prev_pos_resize;
        sf::Rect<int> window_rect_resize;

        void mouse_move_window(sf::Event &event);
        bool can_move = false;
        bool moving = false;
        sf::Vector2i prev_pos_move;
    };
}

#endif // SFTE_MAINWINDOW_H_INCLUDED