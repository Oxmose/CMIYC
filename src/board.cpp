/**
 *
 * @file board.cpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Board class implementation.
 *
 * @see board.hpp
 *
 **/

#include "board.hpp"

CBoard::CBoard () : CBoard (Coor (10,10), Coor (9,0), Coor (0,9)) // BEAUTIFUL: C++11 allows constructor delegation
{

}

CBoard::CBoard (Coor dimensions, Coor firstPlayer, Coor secondPlayer)
{
    // we set the dimensions of the playfield
    // we set the dimensions of the playfield
    playfield.resize (dimensions.first);

    for (unsigned i = 0; i < dimensions.first; i++)
        for (unsigned j = 0; j < dimensions.second; j++)
            if (Coor (i,j) == firstPlayer)  // placing the players
                playfield[i].push_back (CSquare (player1));
            else if (Coor (i,j) == secondPlayer)
                playfield[i].push_back (CSquare (player2));
            else
                if (rand () % (unsigned) std::floor (0.5 + 1 / ReadBarrierApparitionFrequency ()) == 0
                        && i != 0
                        && j != 0
                        && i != dimensions.first - 1
                        && j != dimensions.second - 1)
                    playfield[i].push_back (CSquare (no_player,true));
                else
                    playfield[i].push_back (CSquare (no_player));
    // we create a curses window to display our board in
    window = newwin (dimensions.second+2, dimensions.first+2, (LINES - dimensions.second + 2 ) / 2, (COLS - dimensions.first + 2) / 2);
    box (window,0,0);
    wrefresh (window);
    refresh ();

    AreWallsBroken = false;
    PlayerHere = false;

}

CBoard::~CBoard()
{
    wborder (window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');// clearing the window border
    // clearing the inside of the window
    for (unsigned j = 0; j < playfield[0].size (); ++j)
        for (unsigned i = 0; i < playfield.size (); ++i)
            mvwaddch (window, j + 1, i + 1, ' ');
    wrefresh (window);
    delwin (window);// removing the actual window
    refresh ();

}

void CBoard::Display (Player currentRound)
{
    // Display the score
    mvprintw (2, 2, "Player 1 : %d", Player1Wins);
    mvprintw (2, COLS - 16, "Player 2 : %d", Player2Wins);

    for (unsigned j = 0; j < playfield[0].size (); ++j)
        for (unsigned i = 0; i < playfield.size (); ++i)

            if (playfield[i][j].ContainsPlayer (player1))
                if (currentRound == player1)
                    mvwaddch (window, j + 1, i + 1, 'O' | COLOR_PAIR (1) | A_BOLD | A_REVERSE);
                else
                    mvwaddch (window, j + 1, i + 1, 'O' | COLOR_PAIR (1) | A_BOLD);

            else if (playfield[i][j].ContainsPlayer (player2))
                if (currentRound == player2)
                    mvwaddch (window, j + 1, i + 1, 'X' | COLOR_PAIR (2) | A_BOLD | A_REVERSE);
                else
                    mvwaddch (window, j + 1, i + 1, 'X' | COLOR_PAIR (2) | A_BOLD);

            else
                if (playfield[i][j].ContainsBarrier ())
                    mvwaddch (window, j + 1, i + 1, '#' | COLOR_PAIR (3));
                else if (playfield[i][j].ContainsItem())
                    mvwaddch (window, j + 1, i + 1, '@' | COLOR_PAIR (4));
                else
                    mvwaddch (window, j + 1, i + 1, ReadDotsForBackground () ? '.' : ' ' | COLOR_PAIR (3));

    box (window, 0, 0);
    wrefresh (window);
    refresh ();
}

void CBoard::Move (Coor squareToMove, Direction direction)
{
    // NO CHECKS ARE MADE, the input has to be checked BEFORE using this procedure

    unsigned x = squareToMove.first;
    unsigned y = squareToMove.second;
    // we created those two variables to clarify the following code
    switch (direction)
    {
        case north:
            std::swap (playfield[x][y], playfield[x][y - 1]);
            break;
        case north_east:
            std::swap (playfield[x][y], playfield[x + 1][ y - 1]);
            break;
        case east:
            std::swap (playfield[x][y], playfield[x + 1][y]);
            break;
        case south_east:
            std::swap (playfield[x][y], playfield[x + 1][y + 1]);
            break;
        case south:
            std::swap (playfield[x][y], playfield[x][y + 1]);
            break;
        case south_west:
            std::swap (playfield[x][y], playfield[x - 1][y + 1]);
            break;
        case west:
            std::swap (playfield[x][y], playfield[x - 1][y]);
            break;
        case north_west:
            std::swap (playfield[x][y], playfield[x - 1][y - 1]);
            break;
    }
}

void CBoard::SpawnItem ()
{
    unsigned x;
    unsigned y;
    for (unsigned i = 0; i < playfield.size (); i++)
        for (unsigned j = 0; j < playfield[i].size (); j++)

            if (playfield[i][j].ContainsItem ())
                return;

    if (rand () % (unsigned) std::floor (0.5 + 1 / ReadItemApparitionFrequency ()) == 0)
    {
        do
        {
            y = rand () % playfield.size ();
            x = rand () % playfield[0].size ();
        } while (playfield[x][y].ContainsPlayer () || playfield[x][y].ContainsBarrier ());

        int randomInt;
        if (AreWallsBroken)
            randomInt = std::rand () % 3;
        else
            randomInt = std::rand () % 4;

        switch (randomInt)
        {
            case 0:
                playfield[x][y].AddItem (double_speed);
                break;

            case 1:
                playfield[x][y].AddItem (teleportation);
                break;

            case 2:
                playfield[x][y].AddItem (change_wall);
                break;

            case 3:
                playfield[x][y].AddItem (break_wall);
                break;
        }

    }
}

Direction CBoard::UserInput ()// only check if the user used the right controls, impossible moves are handled by playRound()
{

    char Input;
    while (true)
    {
        Input = getch ();
        switch (Input)
        {
            case 'y': case '7':
                return north_west;

            case 'k': case '8':
                return north;

            case 'u': case '9':
                return north_east;

            case 'h': case '4':
                return west;

            case 'l': case '6':
                return east;

            case 'b': case '1':
                return south_west;

            case 'j': case '2':
                return south;

            case 'n': case '3':
                return south_east;

            case 27:// this is the code for the ESC key
                throw user_exit ();
        }
    }
}

bool CBoard::PlayRound (Player currentRound, unsigned Player1WinNb, unsigned Player2WinNb)// returns true if player1 got player2
{
    Player1Wins = Player1WinNb;
    Player2Wins = Player2WinNb;

    if (currentRound == no_player) // if none is to play, do nothing
        return false;
    if (PlayerHere) // test
        return true;

    // locate the player
    unsigned x = 0;
    unsigned y = 0;
    for (unsigned i = 0; i < playfield.size (); i++)
        for (unsigned j = 0; j < playfield[i].size (); j++)
            if (playfield[i][j].ContainsPlayer (currentRound))
            {
                x = i;
                y = j;
            }

    // gets valid user input
    Direction input;
    bool validInput = false;
    while (! validInput)
    {
        Display (currentRound);
        input = UserInput ();
        switch (input)
        {
            case north:
                if (y > 0 &&
                        ! playfield[x][y - 1].ContainsBarrier ())
                    validInput = true;
                break;

            case north_east:
                if (x + 1 < playfield.size () && y > 0 &&
                        ! playfield[x + 1][y - 1].ContainsBarrier ())
                    validInput = true;
                break;

            case east:
                if ( x + 1 < playfield.size () &&
                        ! playfield[x + 1][y].ContainsBarrier ())
                    validInput = true;
                break;

            case south_east:
                if (x + 1 < playfield.size() && y + 1 < playfield[0].size () &&
                        ! playfield[x + 1][y + 1].ContainsBarrier ())
                    validInput = true;
                break;

            case south:
                if ( y + 1 < playfield[0].size () &&
                        ! playfield[x][y + 1].ContainsBarrier ())
                    validInput = true;
                break;

            case south_west:
                if (x > 0 && y + 1 < playfield[0].size () &&
                        ! playfield[x - 1][y + 1].ContainsBarrier ())
                    validInput = true;
                break;

            case west:
                if (x > 0 &&
                        ! playfield[ x - 1][y].ContainsBarrier ())
                    validInput = true;
                break;

            case north_west:
                if (x > 0 && y > 0 &&
                        ! playfield[x - 1][y - 1].ContainsBarrier ())
                    validInput = true;
                break;
        }
    }
    // check victory conditions and if there is a power up
    unsigned destX = 0;
    unsigned destY = 0;
    switch (input)
    {
        case north:
            destX = x;
            destY = y - 1;
            break;

        case north_east:
            destX = x + 1;
            destY = y - 1;
            break;

        case east:
            destX = x + 1;
            destY = y;
            break;

        case south_east:
            destX = x + 1;
            destY = y + 1;
            break;
        case south:
            destX = x;
            destY = y + 1;
            break;

        case south_west:
            destX = x - 1;
            destY = y + 1;
            break;

        case west:
            destX = x - 1;
            destY = y;
            break;

        case north_west:
            destX = x - 1;
            destY = y - 1;
            break;

    }
    if (playfield[destX][destY].ContainsPlayer ())
    {
        PlayerHere = true;
        return true;
    }

    PowerUp powerUpToApply = no_power_up;

    if (playfield[destX][destY].ContainsItem ())
    {
        powerUpToApply = playfield[destX][destY].WhichPowerUp ();
        playfield[destX][destY].DeleteItem ();
    }
    // moving the player
    Move (Coor (x,y), input);
    // applying the powerup if any
    ApplyPowerUp (currentRound, powerUpToApply);
    // input item
    SpawnItem ();
    return false;
}

void CBoard::ChangeWall ()
{
    // destroy current wall
    for (unsigned i = 0; i < playfield.size (); i++)
        for (unsigned j = 0; j < playfield[i].size (); j++)
            playfield[i][j].BreakWall ();

    // build another wall
    for (unsigned j = 0; j < playfield[0].size(); ++j)
        for (unsigned i = 0; i < playfield.size(); ++i)		
            if (rand () % (unsigned) std::floor (0.5 + 1 / ReadBarrierApparitionFrequency ()) == 0
                    && i != 0
                    && j != 0)
                playfield[i][j].AddWall ();
}

void CBoard::ApplyPowerUp (Player player, PowerUp powerUp)
{
    unsigned randX;
    unsigned randY;
    unsigned x = 0;
    unsigned y = 0;
    switch (powerUp)
    {
        case double_speed:
            mvprintw ((LINES - 1) / 2, (COLS + 30) / 2, "Catched Double Speed");			
            mvprintw ((LINES + 3) / 2, (COLS + 30) / 2, "You can move 3 more times.");

            refresh ();
            std::this_thread::sleep_for (std::chrono::seconds (1));
            clear ();
            refresh ();
            // lets play a few rounds
            for (unsigned i = 3; i != 0; i--)
                PlayRound (player, Player1Wins, Player2Wins);
            break;

        case teleportation:
            mvprintw (( LINES - 1) / 2, (COLS + 30) / 2, "Catched Teleportation.");
            refresh ();
            std::this_thread::sleep_for (std::chrono::seconds (1));
            clear ();
            refresh ();
            // locate player
            for (unsigned i = 0; i < playfield.size (); i++)
                for (unsigned j = 0; j < playfield[i].size (); j++)
                    if (playfield[i][j].ContainsPlayer (player))
                    {
                        x = i;
                        y = j;
                    }
            // random position to teleport.
            do
            {
                randX = rand() % playfield.size ();
                randY = rand() % playfield[0].size ();

            } while(playfield[randX][randY].ContainsPlayer () || playfield[randX][randY].ContainsBarrier ());
            // move player to the random position.
            std::swap (playfield[x][y], playfield[randX][randY]);
            break;

        case break_wall:
            mvprintw ((LINES - 1) / 2, (COLS + 30) / 2, "Catched BreakWall");
            refresh ();
            std::this_thread::sleep_for (std::chrono::seconds (1));
            clear ();
            refresh ();
            if (AreWallsBroken)
            {
                // do whatever you want to do if walls are indeed broken
            }
            else
            {
                for (unsigned i = 0; i < playfield.size (); i++)
                    for (unsigned j = 0; j < playfield[i].size (); j++)
                        playfield[i][j].BreakWall ();
                AreWallsBroken = true;
            }
            break;

        case change_wall:
            mvprintw ((LINES - 1) / 2, (COLS + 30) / 2, "Catched Change Wall");
            refresh ();
            std::this_thread::sleep_for (std::chrono::seconds (1));
            clear ();
            refresh ();
            ChangeWall ();
            AreWallsBroken = false;
            break;

        default:
            break;
    }
}
