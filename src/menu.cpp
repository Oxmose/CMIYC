/**
 *
 * @file menu.cpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Menu class implementation.
 *
 * @see menu.hpp
 *
 **/

#include "menu.hpp"

CMenu::CMenu (std::vector <std::string> choices)
{
    // maxStringLength and itemCount are used to compute the size of the window and of the items array
    unsigned maxStringLength = 0;

    for (std::string str : choices)
        if (str.length () > maxStringLength)
            maxStringLength = str.length ();
    itemCount = choices.size ();

    items = new ITEM * [itemCount + 1];

    for (unsigned i = 0; i < itemCount; ++i)
        items[i] = new_item (choices[i].c_str (), NULL);
    items[itemCount] = NULL; // the ITEM* array is NULL terminated

    menu = new_menu (items);

    // we need to let space for the border
    window = newwin (itemCount + 4, maxStringLength + 6,(LINES - itemCount + 4) / 2 - (itemCount), (COLS-maxStringLength + 4) / 2 - (maxStringLength));
    keypad (window, true);

    // setting the menu window and subwindow
    set_menu_win (menu, window);
    set_menu_sub (menu, derwin (window, itemCount, maxStringLength, 2, 3));

    set_menu_fore (menu, COLOR_PAIR (3) | A_REVERSE);
    set_menu_mark (menu, NULL); // no menu mark

    box (window, 0, 0);
    refresh ();
}

CMenu::~CMenu()
{
    for (unsigned i = 0; i < itemCount; ++i)
        free_item (items[i]);
    delete items;
    free_menu (menu);
    wrefresh (window);
    delwin (window);
    refresh ();
}

std::string CMenu::Display ()
{
    box (window, 0, 0);
    post_menu (menu);

    std::string choice;
    int c;
    while ((c = wgetch (window)))
    {
        wrefresh (window);
        refresh ();
        switch (c)
        {
            case KEY_DOWN:
                //case 'x':
                menu_driver (menu, REQ_DOWN_ITEM);
                break;

            case KEY_UP:
                //case 'z':
                menu_driver (menu, REQ_UP_ITEM);
                break;

            case 10:// Enter
                choice = item_name (current_item (menu));
                pos_menu_cursor (menu);
                unpost_menu (menu);
                wborder (window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');// clearing the window border
                wrefresh (window);
                refresh ();
                return choice;

            case 27:// ESC
                throw user_exit ();
        }
    }
    throw std::runtime_error ("Can't get input from user.");
}
