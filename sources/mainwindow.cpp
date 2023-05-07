#include "pch.h"
#include "pchSFML.h"

#include <logger.h>
#include "mainwindow.h"
#include "button.h"

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
    Main_window::Main_window(unsigned int width, unsigned int height, std::string title)
        : title_bar(title, width, 20.f)
    {
        bool file_succes = this->try_from_file();
        if (!file_succes)
        {
            this->window.create(sf::VideoMode(width, height), title, sf::Style::None);
            this->title = title;

            this->size = this->window.getSize();
            this->position = this->window.getPosition();

            this->size_normal = this->window.getSize();
            this->position_normal = this->window.getPosition();

            this->size_maximized = sf::Vector2u(1920, 1032);
            this->position_maximized = sf::Vector2i(0, 0);

            this->window_state = WINDOW_NORMAL;
        }

        this->title_bar.resize(this->size.x);
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
            this->mouse_resize_window(event);
            this->mouse_move_window(event);
            if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::F4 && event.key.alt)
                    this->window.close();
                else if (event.key.code == sf::Keyboard::Key::F12)
                    this->set_state();
            }
            else if (event.type == sf::Event::EventType::MouseButtonPressed)
            {
                this->title_bar.press_button_mouse_over(this->window);
            }
            else if (event.type == sf::Event::EventType::MouseButtonReleased)
            {
                int button_pressed = this->title_bar.pressed_button();
                int mouse_over = this->title_bar.is_mouse_over(window);
                if (button_pressed == mouse_over)
                {
                    switch (button_pressed)
                    {
                    case BUTTON_MINIMIZE:
                        this->window.setPosition(sf::Vector2i(this->position.x, -this->size.y - 10));
                        break;
                    case BUTTON_MAXIMIZE:
                        this->set_state();
                        break;
                    case BUTTON_EXIT:
                        this->window.close();
                        break;
                    default:
                        break;
                    }
                }
                this->title_bar.press_button(0);
            }
            else if (event.type == sf::Event::EventType::LostFocus)
            {
                this->title_bar.press_button(0);
            }
            else if (event.type == sf::Event::EventType::GainedFocus)
            {
                this->window.setPosition(this->position);
            }
            else if (event.type == sf::Event::EventType::Resized)
            {
                this->title_bar.resize(event.size.width);

                sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visible_area));
            }
            else if (event.type == sf::Event::EventType::Closed)
            {
                this->window.close();
            }
        }
    }
    void Main_window::mouse_resize_window(sf::Event &event)
    {
        static const sf::Rect<int> min_window(INT_MIN, INT_MIN, 400, 200);
        static const sf::Rect<int> max_window(INT_MAX, INT_MAX, INT_MAX, INT_MAX);
        auto get_between = [](int v_min, int v_max, int val)
        {
            return std::min<int>(v_max, std::max<int>(v_min, val));
        };

        if (this->window_state == WINDOW_MAXIMIZED || this->moving ||
            this->title_bar.is_mouse_over(this->window) > TITLE_BAR)
        {
            if (this->can_resize)
            {
                sf::Cursor cursor;
                this->can_resize = false;
                cursor.loadFromSystem(sf::Cursor::Arrow);
                this->window.setMouseCursor(cursor);
            }
            return;
        }
        if (event.type == sf::Event::EventType::MouseMoved && !this->resizing)
        {
            this->horizontal_resize = false, this->vertical_resize = false, this->left_resize = false, this->top_resize = false;
            if (event.mouseMove.x <= 5)
            {
                this->left_resize = true;
                this->horizontal_resize = true;
            }
            else if (event.mouseMove.x >= (int)this->size.x - 6)
            {
                this->horizontal_resize = true;
            }
            if (event.mouseMove.y <= 5)
            {
                this->top_resize = true;
                this->vertical_resize = true;
            }
            else if (event.mouseMove.y >= (int)this->size.y - 6)
            {
                this->vertical_resize = true;
            }

            sf::Cursor cursor;

            if (this->horizontal_resize && this->vertical_resize)
            {
                this->can_resize = true;
                if (this->left_resize)
                {
                    if (this->top_resize)
                        cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
                    else
                        cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
                }
                else
                {
                    if (this->top_resize)
                        cursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
                    else
                        cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
                }
            }
            else if (this->horizontal_resize)
            {
                this->can_resize = true;
                cursor.loadFromSystem(sf::Cursor::SizeHorizontal);
            }
            else if (this->vertical_resize)
            {
                this->can_resize = true;
                cursor.loadFromSystem(sf::Cursor::SizeVertical);
            }
            else if (this->can_resize)
            {
                this->can_resize = false;
                cursor.loadFromSystem(sf::Cursor::Arrow);
            }
            else
                return;

            this->window.setMouseCursor(cursor);
        }
        else if (event.type == sf::Event::EventType::MouseMoved && this->resizing) // ? possile refactor of this
        {
            sf::Vector2i dif_pos = sf::Mouse::getPosition() - this->prev_pos_resize;
            if (this->left_resize)
                dif_pos.x = -dif_pos.x;
            if (this->top_resize)
                dif_pos.y = -dif_pos.y;
            sf::Rect<int> new_window_rect = this->window_rect_resize;

            if (this->horizontal_resize)
            {
                new_window_rect.width = get_between(min_window.width, max_window.width, this->window_rect_resize.width + dif_pos.x);
                if (new_window_rect.width != this->window_rect_resize.width)
                {
                    dif_pos.x = new_window_rect.width - window_rect_resize.width;
                    if (this->left_resize)
                    {
                        new_window_rect.left = get_between(min_window.left, max_window.left, this->window_rect_resize.left - dif_pos.x);
                        dif_pos.x = -dif_pos.x;
                    }
                }
                else
                    dif_pos.x = 0;
            }
            if (this->vertical_resize)
            {
                new_window_rect.height = get_between(min_window.height, max_window.height, this->window_rect_resize.height + dif_pos.y);
                if (new_window_rect.height != this->window_rect_resize.height)
                {
                    dif_pos.y = new_window_rect.height - this->window_rect_resize.height;
                    if (this->top_resize)
                    {
                        new_window_rect.top = get_between(min_window.top, max_window.top, this->window_rect_resize.top - dif_pos.y);
                        dif_pos.y = -dif_pos.y;
                    }
                }
                else
                    dif_pos.y = 0;
            }

            this->window_rect_resize = new_window_rect;
            this->prev_pos_resize += dif_pos;
            this->position = sf::Vector2i(window_rect_resize.left, window_rect_resize.top);
            this->size = sf::Vector2u(static_cast<unsigned int>(window_rect_resize.width), static_cast<unsigned int>(window_rect_resize.height));
            this->window.setPosition(this->position);
            this->window.setSize(this->size);
        }
        else if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
        {
            if (!this->can_resize)
                return;
            this->resizing = true;
            this->prev_pos_resize = sf::Mouse::getPosition();
            this->window_rect_resize.left = this->position.x;
            this->window_rect_resize.top = this->position.y;
            this->window_rect_resize.width = this->size.x;
            this->window_rect_resize.height = this->size.y;
        }
        else if (event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
        {
            this->resizing = false;
        }
    }
    void Main_window::mouse_move_window(sf::Event &event)
    {
        if (this->window_state == WINDOW_MAXIMIZED || this->can_resize || this->resizing ||
            this->title_bar.is_mouse_over(this->window) > TITLE_BAR)
        {
            this->can_move = false;
            return;
        }
        if (event.type == sf::Event::EventType::MouseMoved && !this->moving)
        {
            this->can_move = this->title_bar.is_mouse_over(this->window);
        }
        else if (event.type == sf::Event::EventType::MouseMoved && this->moving)
        {
            sf::Vector2i dif_pos = sf::Mouse::getPosition() - this->prev_pos_move;
            this->prev_pos_move = sf::Mouse::getPosition();
            this->position += dif_pos;
            this->window.setPosition(this->position);
        }
        else if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
        {
            if (!this->can_move)
                return;
            this->moving = true;
            this->prev_pos_move = sf::Mouse::getPosition();
        }
        else if (event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
        {
            this->moving = false;
        }
    }

    void Main_window::display()
    {
        this->window.clear();
        this->window.draw(this->title_bar);
        for (sf::Drawable *&drawable : this->panels)
            this->window.draw(*drawable);
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
    }
}