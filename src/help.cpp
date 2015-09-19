/**
 *
 * @file help.cpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Help display implementation.
 *
 * @see help.hpp
 *
 **/

#include "help.hpp"


CHelp::CHelp ()
{


    // Generate the window
    helpwin = newwin (LINES, COLS, 0, 0);
    keypad (helpwin, true);


    // reading the help file
    ReadHelpFile (HELP_FILE_PATH);


}

CHelp::~CHelp ()
{
    // Removing the borders
    wborder (helpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    delwin (helpwin);	
    refresh ();

}

void CHelp::DisplayHelp ()
{
    clear ();

    int Line = 1;
    int c = 0;

    int LowerScroll;

    // for low res screens
    if (LINES > int (HelpString.size () / ( COLS - 3 )))
        LowerScroll =  HelpString.size () / ( COLS - 3 ) - 2;
    // for hight res screens
    else
        LowerScroll =  -1;



    do
    {		
        for (int Cls (0); Cls < LINES - 1; ++Cls)
            mvwprintw (helpwin, Cls, 1, "                                                                                                             ");

        //This line is used to clear the line that contains "Pg-Up ..."
        mvwprintw (helpwin, LINES - 1, 0, "                                                                                     ");


        mvwprintw (derwin (helpwin, LINES - 4, COLS - 2, 1, 1), 0, 0, HelpString.substr ( ( Line - 1) * ( COLS - 3 ) ).c_str ());

        mvwprintw (helpwin, LINES - 2, COLS - 37, "Pg-Up / Pg-Down to scroll, q to exit");	
        mvwprintw (helpwin, 3 - Line * 2 , COLS / 2 - 4, "Help");	
        box (helpwin, 0, 0);

        clear ();	
        refresh ();	

        c = wgetch (helpwin);

        if (c == KEY_PPAGE)
        {
            if (Line > 1)
                --Line;
        }
        else if (c == KEY_NPAGE)
        {
            if (Line < LowerScroll)
                ++Line;
        }
        else if (c == 27) // ESC
            throw user_exit ();

    } while (c != 'q' && c != 'Q');

    clear ();
    refresh ();

}

void CHelp::ReadHelpFile (const std::string &KFileName)
{
    std::ifstream FileToStore (KFileName, std::ios::in);

    if (! FileToStore)
        throw std::runtime_error ("No help file.");

    std::string Line;
    HelpString = ' ';

    while (std::getline (FileToStore, Line))
    {
        HelpString += '\n' + Line;
    }

    FileToStore.close ();
}


