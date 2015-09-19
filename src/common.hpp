/**
 *
 * @file common.hpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Common header.
 *
 * @details Contains the type definitions used throughout the project.
 *
 * @see board.cpp
 *
 **/


#ifndef _COMMON_HEADER_GUARD_
#define _COMMON_HEADER_GUARD_

#include <utility>

/// @typedef typedef enum{player1 = 1, player2 = 2, no_player = 3} Player;
/// @brief One of the players or no_player.
typedef enum{player1 = 1, player2 = 2, no_player = 3} Player;

/// @typedef typedef enum{north, north_east, east, south_east, south, south_west, west, north_west} Direction;
/// @brief One of the eight cardinal points.
typedef enum{north, north_east, east, south_east, south, south_west, west, north_west} Direction;

/// @typedef typedef std::pair <unsigned, unsigned> Coor;
/// @brief Coordinates in a two dimensionnal matrix.
typedef std::pair <unsigned, unsigned> Coor;

/// @typedef typedef enum{double_speed, teleportation, break_wall, change_wall, no_power_up} PowerUp;
/// @brief Different sort of power up.
typedef enum{double_speed, teleportation, break_wall, change_wall, no_power_up} PowerUp;

/// @brief The exception type thrown when the user wants to exit the game prematurely.
struct user_exit {};
#endif
