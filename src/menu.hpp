/**
 *
 * @file menu.hpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Menu class header.
 *
 * @see menu.cpp
 *
 **/

#ifndef _MENU_HEADER_GUARD_
#define _MENU_HEADER_GUARD_

#include "common.hpp"
#include "confmanager.hpp"
#include <ncurses.h>
#include <menu.h>
#include <exception>
#include <vector>
#include <string>

/// @class CMenu menu.hpp
/// @brief A user-friendly menu.
/// @details A Menu object lets the user choose between different options with arrow keys.
/// The Menu class uses directly the MENU type from ncurses as defined in menu.h
class CMenu
{
    public:
        /// @fn CMenu (std::vector <std::string> choices);
        /// @param choices A vector of all the different choices the user can make.
        /// @brief The constructor.
        /// @details It will create the window the menu is displayed into and allocate the memory used to store the menu.
        CMenu (std::vector <std::string> choices);

        /// @fn ~CMenu ();
        /// @brief The destructor.
        /// @details It will free the memory allocated by the constructor and remove the window.
        ~CMenu ();

        /// @fn std::string Display ();
        /// @returns The choice of the user.
        /// @brief Displays the menu window and returns the choice of the user.
        std::string Display ();

    private:
        /// @brief A pointer to the ncurses MENU used by the Menu.
        MENU *menu;

        /// @brief A pointer to an array of the ITEMs used by the MENU.
        ITEM **items;

        /// @brief The number of elements of the array items points to.
        /// @details This is necessary for proper destruction of the object.
        unsigned itemCount;

        /// @brief The WINDOW the menu is displayed into.
        WINDOW *window;
};

#endif
