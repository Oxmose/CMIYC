/**
 *
 * @file help.hpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Help class header.
 *
 * @see help.cpp
 *
 **/

#ifndef _HELP_HEADER_GUARD_
#define _HELP_HEADER_GUARD_

#include "common.hpp"

#include <vector>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <ncurses.h>
#include <iostream>

/// @def HELP_FILE_PATH
/// @brief The (relative) path of the help file at execution.
#define HELP_FILE_PATH "help.txt"

/// @class CHelp help.hpp
/// @brief The help window
/// @details The help is the window that will show help to the user about how to play the game
/// and about how the cofiguration file was made.
class CHelp
{
    public:

        /// @fn CHelp ();
        /// @brief The constructor
        /// @details The constructor will generate the window and read the help file to display.
        CHelp ();

        /// @fn ~CHelp ();
        /// @brief The destructor.
        /// @details It will free the memory allocated by the constructor and remove the window.
        ~CHelp ();

        /// @fn void DisplayHelp ();
        /// @brief Displays help window.
        /// @details The function will open a new window that will display the informations the player needs to play.
        /// It contains commands, the rules of the game and the available options in the configuration file.
        void DisplayHelp ();



    private:

        /// @fn void ReadHelpFile (const std::string &KFileName);
        /// @brief Read the help file.
        /// @param KFileName The path of the help file.
        /// @details The function will read the help file that have the path we give by parameters and store the file in a vector.
        void ReadHelpFile (const std::string &KFileName);

        /// @brief The WINDOW the help information are displayed into.
        WINDOW *helpwin;

        /// @brief The string the information contained in the help file are stored into.
        std::string HelpString;

};


#endif
