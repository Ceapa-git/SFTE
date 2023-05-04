#include "pch.h"
#include "pchSFML.h"
#include "mainwindow.h"
#include "logger.h"

#define WIDTH (800)
#define HEIGHT (600)

int main(int argc, char **argv)
{
    sfte::Main_window main_win(false);

    while (main_win.is_open())
    {
        main_win.poll_events();

        main_win.display();
    }

    return 0;
}