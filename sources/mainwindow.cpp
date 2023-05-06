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

            this->size_normal = this->window.getSize();
            this->position_normal = this->window.getPosition();

            this->size_maximized = sf::Vector2u(1920, 1032);
            this->position_maximized = sf::Vector2i(0, 0);

            this->window_state = WINDOW_NORMAL;
        }
        // TODO: create title bar
        this->title_bar_background.setSize(sf::Vector2f(this->size.x, 20.f));
        this->title_bar_background.setPosition(0.f, 0.f);
        this->title_bar_background.setFillColor(sf::Color(133, 129, 119));
        this->title_bar_background.setOutlineThickness(0.f);
        this->title_bar.push_back(&this->title_bar_background);
    }
    bool Main_window::try_from_file()
    {
        cge::data::Data_file load;
        load.load(".sfte/editor.bin");
        if (!load.is_valid())
            return false;
        if (load.get_count() != 14)
            return false;

        std::cout << "Opening local editor config" << std::endl;

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

        load.get(5, d_size, d_content);
        this->size_normal.x = uint_from_ucharp(d_content);
        load.get(6, d_size, d_content);
        this->size_normal.y = uint_from_ucharp(d_content);
        load.get(7, d_size, d_content);
        this->position_normal.x = int_from_ucharp(d_content);
        load.get(8, d_size, d_content);
        this->position_normal.y = int_from_ucharp(d_content);

        load.get(9, d_size, d_content);
        this->size_maximized.x = uint_from_ucharp(d_content);
        load.get(10, d_size, d_content);
        this->size_maximized.y = uint_from_ucharp(d_content);
        load.get(11, d_size, d_content);
        this->position_maximized.x = int_from_ucharp(d_content);
        load.get(12, d_size, d_content);
        this->position_maximized.y = int_from_ucharp(d_content);

        load.get(13, d_size, d_content);
        this->window_state = int_from_ucharp(d_content);

        this->window.create(sf::VideoMode(this->size.x, this->size.y), this->title, sf::Style::None);
        this->window.setPosition(this->position);

        return true;
    }
    Main_window::~Main_window()
    {
        std::cout << "Closing editor, saving preferences" << std::endl;
        if (!std::filesystem::is_directory(".sfte"))
            std::filesystem::create_directory(".sfte");

        unsigned char d_content[4];
        cge::data::Data_file save;

        save.add(this->title.length() + 1, reinterpret_cast<const unsigned char *>(this->title.c_str()));

        ucharp_from_uint(d_content, this->size.x);
        save.add(4, d_content);
        ucharp_from_uint(d_content, this->size.y);
        save.add(4, d_content);
        ucharp_from_int(d_content, this->position.x);
        save.add(4, d_content);
        ucharp_from_int(d_content, this->position.y);
        save.add(4, d_content);

        ucharp_from_uint(d_content, this->size_normal.x);
        save.add(4, d_content);
        ucharp_from_uint(d_content, this->size_normal.y);
        save.add(4, d_content);
        ucharp_from_int(d_content, this->position_normal.x);
        save.add(4, d_content);
        ucharp_from_int(d_content, this->position_normal.y);
        save.add(4, d_content);

        ucharp_from_uint(d_content, this->size_maximized.x);
        save.add(4, d_content);
        ucharp_from_uint(d_content, this->size_maximized.y);
        save.add(4, d_content);
        ucharp_from_int(d_content, this->position_maximized.x);
        save.add(4, d_content);
        ucharp_from_int(d_content, this->position_maximized.y);
        save.add(4, d_content);

        ucharp_from_int(d_content, this->window_state);
        save.add(4, d_content);
        save.save(".sfte/editor.bin");
        std::cout << "Preferences saved" << std::endl;
    }

    bool Main_window::is_open()
    {
        return this->window.isOpen();
    }
    void Main_window::poll_events()
    {
        sf::Event event;
        while (this->window.pollEvent(event)) // TODO: call custom event callbacks
        {
            this->mouse_resize(event);
            if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::F4 && event.key.alt)
                    this->window.close();
                else if (event.key.code == sf::Keyboard::Key::F12)
                    this->set_state();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visible_area));
            }
            else if (event.type == sf::Event::EventType::Closed)
            {
                this->window.close();
            }
        }
    }
    void Main_window::mouse_resize(sf::Event &event)
    {
        if (event.type == sf::Event::EventType::MouseMoved)
        {
            bool horizontal = false, vertical = false, left = false, up = false;
            if (event.mouseMove.x < 5)
            {
                left = true;
                horizontal = true;
            }
            else if (event.mouseMove.x >= (int)this->size.x - 5)
            {
                horizontal = true;
            }
            if (event.mouseMove.y < 5)
            {
                up = true;
                vertical = true;
            }
            else if (event.mouseMove.y >= (int)this->size.y - 5)
            {
                vertical = true;
            }

            sf::Cursor cursor;
            if (!horizontal && !vertical)
                cursor.loadFromSystem(sf::Cursor::Arrow);
            else if (horizontal && vertical)
            {
                cursor.loadFromSystem(left
                                          ? (up ? sf::Cursor::SizeTopLeftBottomRight : sf::Cursor::SizeBottomLeftTopRight)
                                          : (up ? sf::Cursor::SizeBottomLeftTopRight : sf::Cursor::SizeTopLeftBottomRight));
            }
            else if (horizontal)
                cursor.loadFromSystem(sf::Cursor::SizeHorizontal);
            else if (vertical)
                cursor.loadFromSystem(sf::Cursor::SizeVertical);

            this->window.setMouseCursor(cursor);
        }
    }

    void Main_window::display()
    {
        this->window.clear();
        // TODO: display title bar
        for (sf::Drawable *&drawable : this->title_bar)
            this->window.draw(*drawable);
        for (sf::Drawable &drawable : this->panels)
            this->window.draw(drawable);
        this->window.display();
    }

    void Main_window::set_state(int state)
    {
        if (state == this->window_state)
            return;
        if (state == WINDOW_NORMAL || (this->window_state == WINDOW_MAXIMIZED && state == WINDOW_SWAP_STATE))
        {
            this->size_maximized = this->window.getSize();
            this->position_maximized = this->window.getPosition();
            this->window.setSize(this->size_normal);
            this->window.setPosition(this->position_normal);
            this->window_state = WINDOW_NORMAL;
        }
        else if (state == WINDOW_MAXIMIZED || (this->window_state == WINDOW_NORMAL && state == WINDOW_SWAP_STATE))
        {
            this->size_normal = this->window.getSize();
            this->position_normal = this->window.getPosition();
            this->window.setSize(this->size_maximized);
            this->window.setPosition(this->position_maximized);
            this->window_state = WINDOW_MAXIMIZED;
        }

        this->size = this->window.getSize();
        this->position = this->window.getPosition();

        sf::Vector2f new_size(this->title_bar_background.getSize());
        new_size.x = this->size.x;
        this->title_bar_background.setSize(new_size);
    }
}