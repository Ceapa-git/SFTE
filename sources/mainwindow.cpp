#include "pch.h"
#include "pchSFML.h"
#include "mainwindow.h"
#include "logger.h"

namespace sfte
{
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
        ucharp[0] = (unsigned char)((val >> 8 * 0) | 0xff);
        ucharp[1] = (unsigned char)((val >> 8 * 1) | 0xff);
        ucharp[2] = (unsigned char)((val >> 8 * 2) | 0xff);
        ucharp[3] = (unsigned char)((val >> 8 * 3) | 0xff);
    }
    static void ucharp_from_int(unsigned char *ucharp, int val)
    {
        ucharp[0] = (unsigned char)((val >> 8 * 0) | 0xff);
        ucharp[1] = (unsigned char)((val >> 8 * 1) | 0xff);
        ucharp[2] = (unsigned char)((val >> 8 * 2) | 0xff);
        ucharp[3] = (unsigned char)((val >> 8 * 3) | 0xff);
    }

    Main_window::Main_window(bool from_file, unsigned int width, unsigned int heigth, const char *title)
        : window()
    {
        bool file_succes = false;
        if (from_file)
            file_succes = try_from_file();
        if (!file_succes)
        {
            this->position_maximized = sf::Vector2i(0, 0);
            this->size = sf::Vector2u(width, heigth);
            this->size_maximized = sf::Vector2u(1920u, 1009u);
            this->size_normal = this->size;
            this->state = window_state::NORMAL;
            this->title = std::make_unique<char[]>(strlen(title) + 1);
            strcpy(this->title.get(), title);

            this->window.create(sf::VideoMode(this->size.x, this->size.y), this->title.get(), sf::Style::None);
            this->position = this->window.getPosition();
            this->position_normal = this->position;
        }

        if (!std::filesystem::is_directory(".stfe"))
            std::filesystem::create_directory(".stfe");

        unsigned char content[8];

        ucharp_from_uint(content, this->size.x);
        ucharp_from_uint(content + 4, this->size.x);
        data.add(8, content);
        ucharp_from_int(content, this->position.x);
        ucharp_from_int(content + 4, this->position.x);
        data.add(8, content);
        ucharp_from_uint(content, this->size_normal.x);
        ucharp_from_uint(content + 4, this->size_normal.x);
        data.add(8, content);
        ucharp_from_int(content, this->position_normal.x);
        ucharp_from_int(content + 4, this->position_normal.x);
        data.add(8, content);
        ucharp_from_uint(content, this->size_maximized.x);
        ucharp_from_uint(content + 4, this->size_maximized.x);
        data.add(8, content);
        ucharp_from_int(content, this->position_maximized.x);
        ucharp_from_int(content + 4, this->position_maximized.x);
        data.add(8, content);
        content[0] = (state == window_state::NORMAL ? 0 : (state == window_state::MAXIMIZE ? 1 : 2));
        data.add(1, content);
        data.add(strlen(this->title.get()), reinterpret_cast<const unsigned char *>(this->title.get()));

        data.set_auto_save(true, ".stfe/editor.bin");
        data.set_auto_save_interval(std::chrono::seconds(10)); //// std::chrono::minutes(1))
    }
    Main_window::~Main_window()
    {
    }

    bool Main_window::try_from_file()
    {
        cge::data::Data_file load_file;
        load_file.load(".stfe/editor.bin");
        if (!load_file.is_valid() || load_file.get_count() != 8)
            return false;

        int contetn_size;
        const unsigned char *content;

        sf::Vector2u size;
        load_file.get(0, contetn_size, content);
        if (contetn_size != 2 * sizeof(unsigned int))
            return false;
        size.x = uint_from_ucharp(content);
        size.y = uint_from_ucharp(content + 4);

        sf::Vector2i position;
        load_file.get(1, contetn_size, content);
        if (contetn_size != 2 * sizeof(int))
            return false;
        position.x = int_from_ucharp(content);
        position.y = int_from_ucharp(content + 4);

        sf::Vector2u size_normal;
        load_file.get(2, contetn_size, content);
        if (contetn_size != 2 * sizeof(unsigned int))
            return false;
        size_normal.x = uint_from_ucharp(content);
        size_normal.y = uint_from_ucharp(content + 4);

        sf::Vector2i position_normal;
        load_file.get(3, contetn_size, content);
        if (contetn_size != 2 * sizeof(int))
            return false;
        position_normal.x = int_from_ucharp(content);
        position_normal.y = int_from_ucharp(content + 4);

        sf::Vector2u size_maximized;
        load_file.get(4, contetn_size, content);
        if (contetn_size != 2 * sizeof(unsigned int))
            return false;
        size_maximized.x = uint_from_ucharp(content);
        size_maximized.y = uint_from_ucharp(content + 4);

        sf::Vector2i position_maximized;
        load_file.get(5, contetn_size, content);
        if (contetn_size != 2 * sizeof(int))
            return false;
        position_maximized.x = int_from_ucharp(content);
        position_maximized.y = int_from_ucharp(content + 4);

        load_file.get(7, contetn_size, content);
        const char *title = (const char *)content;

        window_state state;
        load_file.get(6, contetn_size, content);
        if (contetn_size != 1)
            return false;
        switch (content[0])
        {
        case 0:
            state = window_state::NORMAL;
            break;
        case 1:
            state = window_state::MAXIMIZE;
            break;
        case 2:
            state = window_state::FULLSCREEN;
            break;
        default:
            return false;
        }

        this->position = position;
        this->position_maximized = position_maximized;
        this->position_normal = position_normal;
        this->size = size;
        this->size_maximized = size_maximized;
        this->size_normal = size_normal;
        this->state = state;
        this->title = std::make_unique<char[]>(sizeof(strlen(title) + 1));
        strcpy(this->title.get(), title);

        window.create(sf::VideoMode(size.x, size.y), this->title.get(), sf::Style::None);
        this->set_state();

        return true;
    }

    void Main_window::set_state(window_state state)
    {
        if (state == this->state)
            return;
        switch (state)
        {
        case window_state::KEEP:
            break;
        default:
            break;
        }
    }

    bool Main_window::is_open() const
    {
        return window.isOpen();
    }
    void Main_window::poll_events()
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            // TODO: add custom handlers returning bool true if overiding the default
            if (event.type == sf::Event::Closed)
                this->window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::F4 && event.key.alt)
                    this->window.close();
            }
        }
    }

    void Main_window::display()
    {
        this->window.clear();
        this->window.display();
    }
}