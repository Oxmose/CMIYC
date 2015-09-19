/**
 *
 * @file main.cpp
 *
 * @authors: J.Saffi, Y.Vidal, Y.Roux, A.Torres Aurora
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Main file.
 *
 * @see main.hpp
 *
 **/
#include "main.hpp"

/// @brief Main function.
int main ()
{
    std::srand (time (NULL));
    initscr ();			  // start curses
    cbreak ();		      // line buffering disabled
    keypad (stdscr, true); // activating special keys
    nodelay (stdscr,true);
    noecho ();
    curs_set (0);

    if (has_colors ())      // checks if colors are available for the current terminal
        start_color ();

    try
    {

        // sets color pairs 1, 2 and 3 that will be used as the player colors and empty squares, as well as for the menu
        init_pair (1, ReadPlayerColor (player1), COLOR_BLACK);
        init_pair (2, ReadPlayerColor (player2), COLOR_BLACK);
        init_pair (3, ReadPlayerColor (no_player), COLOR_BLACK);
        init_pair (4, ReadItemColor (), COLOR_BLACK); // set item color.

        // setting up main menu
        std::vector <std::string> items = {
            "Play",
            "Help",
            "Settings",
            "Quit"};
        CMenu mainMenu (items);
        std::string choice;

        // generating the help window
        CHelp HelpInfo;

        // generating the settings window
        std::vector < std::string > VarNames = {
            "board_width",
            "board_height",
            "starting_player",
            "color_player1",
            "color_player2",
            "color_empty",
            "color_item",
            "barrier_apparition_frequency",
            "item_apparition_frequency",
            "dots_for_background"};

        std::vector < FIELDTYPE* > VarTypes = {
            TYPE_INTEGER,
            TYPE_INTEGER,
            TYPE_INTEGER,
            TYPE_INTEGER,
            TYPE_INTEGER,
            TYPE_INTEGER,
            TYPE_INTEGER,
            TYPE_NUMERIC,
            TYPE_NUMERIC,
            TYPE_INTEGER};
        std::vector < void* > VarValues;

        // We add the values to the values vector
        int BoardWidth = ReadBoardDimensions ().first;
        int BoardHeight = ReadBoardDimensions ().second;
        Player StartingPlayer = ReadStartingPlayer ();
        int Player1Color = ReadPlayerColor (player1);
        int Player2Color = ReadPlayerColor (player2);
        int EmptyColor = ReadPlayerColor (no_player);
        int ItemsColor = ReadItemColor ();
        float BarrierApparition = ReadBarrierApparitionFrequency();
        float ItemsApparition = ReadItemApparitionFrequency();
        int DotsForBG = ReadDotsForBackground();

        VarValues.push_back (&BoardWidth);
        VarValues.push_back (&BoardHeight);
        VarValues.push_back (&StartingPlayer);
        VarValues.push_back (&Player1Color);
        VarValues.push_back (&Player2Color);
        VarValues.push_back (&EmptyColor);
        VarValues.push_back (&ItemsColor);
        VarValues.push_back (&BarrierApparition);
        VarValues.push_back (&ItemsApparition);
        VarValues.push_back (&DotsForBG);

        CForm Settings (VarNames, VarTypes, VarValues);

        unsigned Player1Wins = 0;
        unsigned Player2Wins = 0;

        while (true) // menuloop
        {
            //displaying title
            attron(COLOR_PAIR(1));
            mvprintw((LINES-5)/4+0,(COLS-40)/2,"  ____      _       _       __  __      ");
            mvprintw((LINES-5)/4+1,(COLS-40)/2," / ___|__ _| |_ ___| |__   |  \\/  | ___ ");
            mvprintw((LINES-5)/4+2,(COLS-40)/2,"| |   / _` | __/ __| '_ \\  | |\\/| |/ _ \\");
            mvprintw((LINES-5)/4+3,(COLS-40)/2,"| |__| (_| | || (__| | | | | |  | |  __/");
            mvprintw((LINES-5)/4+4,(COLS-40)/2," \\____\\__,_|\\__\\___|_| |_| |_|  |_|\\___|");
            attroff(COLOR_PAIR(1));

            attron(COLOR_PAIR(2));
            mvprintw(3*(LINES-10)/4+6,(COLS-46)/2," ___  __  __   __             ____            ");
            mvprintw(3*(LINES-10)/4+7,(COLS-46)/2,"|_ _|/ _| \\ \\ / /__  _   _   / ___|__ _ _ __  ");
            mvprintw(3*(LINES-10)/4+8,(COLS-46)/2," | || |_   \\ V / _ \\| | | | | |   / _` | '_ \\ ");
            mvprintw(3*(LINES-10)/4+9,(COLS-46)/2," | ||  _|   | | (_) | |_| | | |__| (_| | | | |");
            mvprintw(3*(LINES-10)/4+10,(COLS-46)/2,"|___|_|     |_|\\___/ \\__,_|  \\____\\__,_|_| |_|");
            attroff(COLOR_PAIR(2));
            refresh();

            //displaying main menu
            choice = mainMenu.Display ();

            clear();

            if (choice == "Quit")//TODO: secure the way menus are handled, a simple case error can cause failure
                break;
            else if (choice == "Help")
                HelpInfo.DisplayHelp();
            else if (choice == "Settings")

                Settings.Display ();
            else
            {

                // initializing board
                Coor boardDimensions = ReadBoardDimensions ();
                Coor firstPlayerStart = Coor (boardDimensions.first - 1, 0);
                Coor secondPlayerStart = Coor (0, boardDimensions.second - 1);
                CBoard board (boardDimensions, firstPlayerStart, secondPlayerStart);

                // setting first player
                Player currentRound = ReadStartingPlayer ();

                while (! board.PlayRound (currentRound, Player1Wins, Player2Wins)) // gameloop
                    if (currentRound == player1)
                        currentRound = player2;
                    else
                        currentRound = player1;


                // we clear the screen, print the winning player and clear it again

                clear ();
                attron (COLOR_PAIR (currentRound));
                mvprintw ((LINES - 1) / 2 , (COLS - 16) / 2, "Player %d wins.", currentRound);

                if (currentRound == player1)
                    ++Player1Wins;
                else
                    ++Player2Wins;

                attroff (COLOR_PAIR (currentRound));
                refresh ();
                std::this_thread::sleep_for (std::chrono::seconds (2));
                clear ();
            }
        }
    }

    catch (const user_exit &e)
    {
        endwin ();
        return 0;
    }

    catch (const std::exception &e)
    {
        endwin ();
        std::cerr << e.what () << std::endl;
        return 1;
    }

    endwin ();
    return 0;
}
