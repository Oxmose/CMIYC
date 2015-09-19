/**
 *
 * @file square.cpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Square class implementation.
 *
 * @see square.hpp
 *
 **/

#include "square.hpp"

CSquare::CSquare (Player content, bool hasBarrier)
{
    if (content != no_player && hasBarrier)
        throw std::runtime_error ("Player is in Barrier !");
    this -> content = content;
    this -> hasBarrier = hasBarrier;
    Item = no_power_up;
}

bool CSquare::ContainsPlayer ()
{
    return content != no_player;
}

bool CSquare::ContainsPlayer (Player p)
{
    return content == p;
}

bool CSquare::ContainsBarrier ()
{
    return hasBarrier;
}

bool CSquare::ContainsItem ()
{
    return Item != no_power_up;
}

void CSquare::AddItem (PowerUp itemToAdd)
{
    Item = itemToAdd;
}

void CSquare::DeleteItem ()
{
    Item = no_power_up;
}

PowerUp CSquare::WhichPowerUp ()
{
    return Item;
}

void CSquare::BreakWall ()
{
    hasBarrier = false;
}

void CSquare::AddWall ()
{
    hasBarrier = true;
}
