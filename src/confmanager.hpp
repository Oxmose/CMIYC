/**
 *
 * @file confmanager.hpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Configuration file management header.
 *
 * @see confmanager.cpp
 *
 **/

#ifndef _CONFMANAGER_HEADER_GUARD_
#define _CONFMANAGER_HEADER_GUARD_

#include "common.hpp"

#include <fstream>
#include <string>
#include <stdexcept>
#include <exception>
#include <vector>
#include <iostream>
#include <cctype>

/// @def CONFIG_FILE_PATH
/// @brief The (relative) path of the config file at execution.
#define CONFIG_FILE_PATH "config.cfg"


/// @fn template <typename TYPE> TYPE ReadVariable (const std::string &KFileName, const std::string &KVariableName);
/// @param KFileName File path of the configuration file.
/// @param KVariableName Name of the parsed variable.
/// @returns The parsed value of the variable.
/// @brief Configuration file parser for one variable.
/// @details The function will parse the file we give him in first place parameter.
/// To achieve this, it will read the variable's value in the configuration file and return the value.
/// It uses a template to be able to parse any type using operator >>
template <typename TYPE> TYPE ReadVariable (const std::string &KFileName, const std::string &KVariableName);

/// @fn template <typename TYPE> void WriteVariable (const std::string &KFileName, const std::string &KVariableName, const TYPE &KVariableValue, bool EraseFile);
/// @param KFileName File path of the configuration file.
/// @param KVariableName Name of the variable to inject.
/// @param KVariableValue Value of the variable to inject.
/// @param EraseFile Set if the file must be erased before being writed.
/// @brief Configuration file writer for one variable.
/// @details The function will write the file we give him in first place parameter and her value we give in second place parameter.
/// To achieve this, it will write the variable and then value in the configuration file.
/// It uses a template to be able to write any type properly using operator >>
template <typename TYPE> void WriteVariable (const std::string &KFileName, const std::string &KVariableName, const TYPE &KVariableValue, bool EraseFile);

/// @fn Player ReadStartingPlayer ();
/// @returns The starting Player.
/// @brief Reads the starting Player in the config file.
/// @details The function will return which player will begin to play. It uses the ReadVariable Function.
/// The path of the config file is specified in a define made in confmanager.hpp
Player ReadStartingPlayer ();

/// @fn Coor ReadBoardDimensions ();
/// @brief Reads the dimensions of the board in the config file.
/// @returns The dimensions of the board.
/// @details The function will return the dimensions of the board as set in the configuration file.
/// It uses the ReadVariable function.
/// The path of the config file is specified in a define made in confmanager.hpp
Coor ReadBoardDimensions ();

/// @fn int ReadPlayerColor (Player player);
/// @param player Player to get the color of.
/// @returns The Player's color equivalent as an ncurses define.
/// @brief Reads the player color in the config file.
/// @details The function will return the color of the player whose name is the parameter.
/// It uses the ReadVariable function to read the configuration file.
/// The path of the config file is specified in a define made in confmanager.hpp
int ReadPlayerColor (Player player);

/// @fn int ReadItemColor ();
/// @returns The Item's color equivalent as an ncurses define.
/// @brief Reads the item color in the config file.
/// @details It uses the ReadVariable function to read the configuration file.
/// The path of the config file is specified in a define made in confmanager.hpp
int ReadItemColor ();

/// @fn ReadBarrierApparitionFrequency ();
/// @returns The apparition frequency of barriers.
/// @brief Reads the apparition frequency of barriers.
/// @details The returned value is between 0 and 1.
float ReadBarrierApparitionFrequency ();

/// @fn ReadItemApparitionFrequency ()
/// @returns The apparition frequency of items.
/// @brief Reads the apparition frequency of items.
/// @details The returned value is between 0 and 1.
float ReadItemApparitionFrequency ();

/// @fn ReadDotsForBackground ();
/// @returns If the background has dots or not.
/// @brief Read if the background display dots or not.
/// @details The returned value is a booleen that will set the background character to none or dots.
bool ReadDotsForBackground ();

/// @fn void WriteFloatInFile (const std::string &KVariableName, char* VariableValue);
/// @param KVariableName The name of the variable to inject.
/// @param VariableValue The value of the variable to inject.
/// @brief Write a float number in the configuration file
/// @details The function will write the name of the float variable and her value thanks to the WriteVariable template.
void WriteFloatInFile (const std::string &KVariableName, char* VariableValue);

/// @fn void WriteIntInFile (const std::string &KVariableName, char* VariableValue);
/// @param KVariableName Name of the variable to inject.
/// @param VariableValue Value of the variable to inject.
/// @brief Write an integer number in the configuration file
/// @details The function will write the name of the integer variable and her value thanks to the WriteVariable template.
void WriteIntInFile (const std::string &KVariableName, char* VariableValue);

/// @fn void WriteCommentInFile (const std::string &KComment, bool EraseFile = false);
/// @param KComment The comment to inject.
/// @param EraseFile Set if the configuration file have to be erased.
/// @brief Write a comment in the configuration file
/// @details The function will write the the comment gave in parameters thanks to the WriteVariable template
void WriteCommentInFile (const std::string &KComment, bool EraseFile = false);

#endif
