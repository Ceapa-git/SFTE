#include "pch.h"
#include "pchSFML.h"
#include "mainwindow.h"
#include "logger.h"

namespace sfte
{
    Main_window::Main_window(bool from_file, unsigned int width, unsigned int heigth, std::string title)
    {
        this->window.create(sf::VideoMode(width, heigth), title, sf::Style::None);
        this->size = this->window.getSize();
        this->position = this->window.getPosition();
        this->title = title;
    }

    bool Main_window::is_open()
    {
        return this->window.isOpen();
    }
    void Main_window::poll_events()
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed)
            {
                this->window.close();
            }
            else if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::F4 && event.key.alt)
                {
                    this->window.close();
                }
            }
        }
    }

    void Main_window::display()
    {
        this->window.clear();
        this->window.display();
    }
}