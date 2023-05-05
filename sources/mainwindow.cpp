#include "pch.h"
#include "pchSFML.h"
#include "mainwindow.h"
#include "logger.h"

static unsigned int uint_from_ucharp(const unsigned char *ucharp)
{
    unsigned int res = 0;
    res |= ucharp[0] << 8 * 0;
    res |= ucharp[1] << 8 * 1;
    res |= ucharp[2] << 8 * 2;
    res |= ucharp[3] << 8 * 3;
    return res;
}
static int int_from_ucharp(const unsigned char *ucharp)
{
    int res = 0;
    res |= ucharp[0] << 8 * 0;
    res |= ucharp[1] << 8 * 1;
    res |= ucharp[2] << 8 * 2;
    res |= ucharp[3] << 8 * 3;
    return res;
}
static void ucharp_from_uint(unsigned char *ucharp, unsigned int val)
{
    ucharp[0] = (unsigned char)((val >> 8 * 0) & 0xff);
    ucharp[1] = (unsigned char)((val >> 8 * 1) & 0xff);
    ucharp[2] = (unsigned char)((val >> 8 * 2) & 0xff);
    ucharp[3] = (unsigned char)((val >> 8 * 3) & 0xff);
}
static void ucharp_from_int(unsigned char *ucharp, int val)
{
    ucharp[0] = (unsigned char)((val >> 8 * 0) & 0xff);
    ucharp[1] = (unsigned char)((val >> 8 * 1) & 0xff);
    ucharp[2] = (unsigned char)((val >> 8 * 2) & 0xff);
    ucharp[3] = (unsigned char)((val >> 8 * 3) & 0xff);
}

namespace sfte
{
    Main_window::Main_window(unsigned int width, unsigned int heigth, std::string title)
    {
        bool file_succes = this->try_from_file();
        if (!file_succes)
        {
            this->window.create(sf::VideoMode(width, heigth), title, sf::Style::None);
            this->title = title;
            this->size = this->window.getSize();
            this->position = this->window.getPosition();
        }
        if (!std::filesystem::is_directory(".sfte"))
            std::filesystem::create_directory(".sfte");

        unsigned char d_content[4];

        this->data.add(this->title.length() + 1, reinterpret_cast<const unsigned char *>(this->title.c_str()));

        ucharp_from_uint(d_content, this->size.x);
        this->data.add(4, d_content);
        ucharp_from_uint(d_content, this->size.y);
        this->data.add(4, d_content);

        ucharp_from_int(d_content, this->position.x);
        this->data.add(4, d_content);
        ucharp_from_int(d_content, this->position.y);
        this->data.add(4, d_content);
    }
    bool Main_window::try_from_file()
    {
        cge::data::Data_file load;
        load.load(".sfte/editor.bin");
        if (!load.is_valid())
            return false;
        if (load.get_count() != 5)
            return false;

        int d_size;
        const unsigned char *d_content;

        load.get(0, d_size, d_content);
        this->title = reinterpret_cast<const char *>(d_content);

        load.get(1, d_size, d_content);
        this->size.x = uint_from_ucharp(d_content);
        load.get(2, d_size, d_content);
        this->size.y = uint_from_ucharp(d_content);

        load.get(3, d_size, d_content);
        this->position.x = int_from_ucharp(d_content);
        load.get(4, d_size, d_content);
        this->position.y = int_from_ucharp(d_content);

        this->window.create(sf::VideoMode(this->size.x, this->size.y), this->title, sf::Style::None);
        this->window.setPosition(this->position);

        return true;
    }
    Main_window::~Main_window()
    {
        this->data.save(".sfte/editor.bin");
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