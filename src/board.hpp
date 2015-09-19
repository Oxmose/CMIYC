/**
 *
 * @file board.hpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Board class header.
 *
 * @see board.cpp
 *
 **/


#ifndef _BOARD_HEADER_GUARD_
#define _BOARD_HEADER_GUARD_

#include "common.hpp"
#include "square.hpp"
#include "confmanager.hpp"
#include <vector>
#include <limits>
#include <exception>
#include <ncurses.h>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <thread>



/// @class CBoard board.hpp
/// @brief The board on which the game is played.
/// @details One Board object represents one game, it has methods to advance the state of the game or display it.
class CBoard
{
    public:
        /// @fn CBoard ();
        /// @brief The default constructor.
        /// @details It creates a 10x10 board with players in the upper-right-most and lower-left-most positions.
        /// It's only a delegation from the detailed constructor.
        CBoard();

        /// @fn CBoard (Coor dimensions, Coor firstPlayer, Coor secondPlayer);
        /// @param dimensions The dimensions of the desired board.
        /// @param firstPlayer The starting coordinates of the first player.
        /// @param secondPlayer The starting coordinates of the second player.
        /// @brief The detailed constructor.
        /// @details It creates a board according to the specified dimensions and will place the players if they are at a valid position.
        /// It will also initialize a ncurses window and a border accordingly.
        CBoard (Coor dimensions, Coor firstPlayer, Coor secondPlayer);

        /// @fn ~CBoard ();
        /// @brief The destructor.
        /// @details It will get rid of the ncurses window and its border.
        ~CBoard ();

        /// @fn void Display (Player currentRound);
        /// @param currentRound The player that will play the next turn.
        /// @brief Displays the current round of the game.
        void Display (Player currentRound);

        /// @fn bool PlayRound (Player currentRound, unsigned Player1WinNb, unsigned Player2WinNb);
        /// @param currentRound The player that will play the turn.
        /// If it is no_player, the turn is skipped.
        /// @param Player1WinNb the number of rounds won by player1.
        /// @param Player2WinNb the number of rounds won by player2.
        /// @return true if a player moves over the other, false otherwise.
        /// @brief Plays a turn of the game.
        /// @details This procedure will get the input of the player until it is valid and will then move the player square accordingly.
        bool PlayRound (Player currentRound, unsigned Player1WinNb, unsigned Player2WinNb);





    private:
        /// @fn void Move (Coor squareToMove, Direction direction);
        /// @param squareToMove The coordinates of the Square that will be moved.
        /// @param direction The Direction in which the Square will be moved.
        /// @brief Moves a square of the board.
        /// @details No check are made in the validity of the input.
        /// The Square is swapped with the one in the specified direction, its content is not modified.
        void Move (Coor squareToMove, Direction direction);

        /// @fn Direction UserInput();
        /// @return The direction chosen by the user.
        /// @brief Gets input from the player.
        /// @throws user_exit if the player presses ESC, resulting in the program closing successfuly.
        Direction UserInput ();

        /// @fn void SpawnItem();
        /// @brief Spawns an item in the board.
        /// @details This method will spawn an item in a free Square of the board. The frequency of spawn is variable in the setting.
        void SpawnItem ();

        /// @fn void ApplyPowerUp(Player player, PowerUp powerUp)
        /// @param player the player that get the Power up
        /// @param powerUp the powerup the apply
        /// @brief Apply a powerUp on a player.
        void ApplyPowerUp (Player player, PowerUp powerUp);

        /// @brief Contain the information if wall has been broke.
        bool AreWallsBroken;

        /// @brief Contain the information if the player is in the Square.
        /// @details Use only for the DoubleSpeed effect.
        bool PlayerHere;

        /// @brief Delete all wall in the board and generate another board with wall.
        void ChangeWall ();

        /// @brief Square matrix to store the playfield.
        std::vector < std::vector <CSquare> > playfield;

        /// @brief ncurses window to display the playfield.
        WINDOW *window;

        /// @brief Player 1 number of wins
        unsigned Player1Wins;

        /// @brief Player 2 number of wins
        unsigned Player2Wins;
};

#endif
