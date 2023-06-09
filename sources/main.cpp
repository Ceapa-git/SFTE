#include "pch.h"
#include "pchSFML.h"

#include <logger.h>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    sfte::Main_window main_win;

    while (main_win.is_open())
    {
        main_win.poll_events();

        main_win.display();
    }

    return 0;
}