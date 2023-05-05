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
        FULLSCREEN
    } window_state;
    class Main_window
    {
    public:
        Main_window() = delete;
        Main_window(const Main_window &other) = delete;
        ~Main_window(){};
        explicit Main_window(bool from_file, unsigned int width = 800, unsigned int heigth = 600, std::string title = "Simple Fast Text Editor");

        bool is_open();
        void poll_events();
        // TODO: void add_event_handler with storage of them

        void display();

    private:
        sf::RenderWindow window;
        sf::Vector2u size;
        sf::Vector2i position;

        std::string title;
        cge::data::Data_file data;

    private:
        bool try_from_file();//TODO: broken
    };
}

#endif //__MAINWINDOW__H__