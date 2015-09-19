/**
 *
 * @file square.hpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Square class header.
 *
 * @see square.cpp
 *
 **/

#ifndef _SQUARE_HEADER_GUARD_
#define _SQUARE_HEADER_GUARD_

#include "common.hpp"
#include <exception>
#include <stdexcept>

/// @class CSquare square.hpp
/// @brief The squares of the board.
/// @details One Square object represents one square of the playfield and its content.
/// The content of a Square cannot be modified after its creation.

class CSquare
{
    public:

        /// @fn CSquare (Player content = no_player, bool hasBarrier = false);
        /// @param content The content of the Square, defaults to no_player.
        /// @param hasBarrier Specifies if the Square contains a barrier, default to false.
        /// @brief The constructor.
        CSquare (Player content = no_player, bool hasBarrier = false);

        /// @fn bool ContainsPlayer ();
        /// @returns false if the Square contains no_player, true otherwise.
        /// @brief Checks if the Square contains any player.
        bool ContainsPlayer ();

        /// @fn bool ContainsPlayer (Player p);
        /// @param p The player to look for.
        /// @returns true if the Square contains p, false otherwise.
        /// @brief Checks if the Square contains a particular player.
        bool ContainsPlayer (Player p);

        /// @fn bool ContainsBarrier ();
        /// @returns true if the Square contains a barrier, false otherwise.
        /// @brief Checks if the Square contains a barrier.
        bool ContainsBarrier ();

        /// @fn bool ContainsItem ();
        /// @returns true if the Square contains an item, false otherwise.
        /// @brief Checks if the Square contains an item.
        bool ContainsItem ();

        /// @fn void AddItem (PowerUp itemToAdd);
        /// @param itemToAdd The item to add to the Square.
        /// @brief Adds an item to the Square.
        void AddItem (PowerUp itemToAdd);

        /// @fn void DeleteItem ();
        /// @brief Removes the item in the Square.
        void DeleteItem ();

        /// @fn PowerUp WhichPowerUp ();
        /// @brief Checks which PowerUp the player have.
        PowerUp WhichPowerUp ();

        /// @fn void BreakWall ();
        /// @brief Removes barrier from the Square.
        void BreakWall ();

        /// @fn void AddWall ();
        /// @brief Adds barrier to the Square.
        void AddWall ();

    private:
        /// @brief The content of the Square.
        Player content;

        /// @brief Stores if the Square contains a barrier.
        bool hasBarrier;

        /// @brief Stores the kind of item the Square contains.
        PowerUp Item;

};

#endif
