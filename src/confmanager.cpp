/**
 *
 * @file confmanager.cpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Configuration file management implementation.
 *
 * @see confmanager.hpp
 *
 **/

#include "confmanager.hpp"
#include <iomanip>

template <typename TYPE> TYPE ReadVariable (const std::string &KFileName, const std::string &KVariableName) // template that read the configuration file
{
    std::ifstream FileToStore(KFileName, std::ios::in);

    if (! FileToStore)
        throw std::runtime_error ("No configuration file.");

    std::string TestBuffer;

    TYPE VariableValue;

    // While we didn't reach EOF or get the value, read the line
    while (FileToStore >> TestBuffer)
    {
        if (TestBuffer == KVariableName)
        {
            if(! (FileToStore >> VariableValue))
            {
                int Position = FileToStore.tellg ();

                throw std::runtime_error (
                        std::string ("Wrong value in configuration file at position ") +
                        std::to_string (Position));
            }


        }

    }

    FileToStore.close ();

    return VariableValue;
} // ReadVariable ()

template <typename TYPE> void WriteVariable (const std::string &KFileName, const std::string &KVariableName, const TYPE &KVariableValue, bool EraseFile) // template that write the configuration file
{
    std::ofstream FileToWrite;

    if (EraseFile)
        FileToWrite.open (KFileName, std::ios::out | std::ios::trunc);
    else
        FileToWrite.open (KFileName, std::ios::out | std::ios::app);

    if (! FileToWrite)
        throw std::runtime_error ("Unable to open or creat the configuration file (check your permissions).");

    FileToWrite << std::left << std::setw (40) << KVariableName << std::setw (6) << KVariableValue << '\n';

    FileToWrite.close ();
} // WriteVariable ()

Player ReadStartingPlayer () // this will return the starting player
{
    switch (ReadVariable <int> (CONFIG_FILE_PATH, "starting_player"))
    {
        case 1:
            return player1;
        case 2:
            return player2;
        default:
            return no_player;
    }
} // ReadStartingPlayer ()

Coor ReadBoardDimensions () // this will return the board dimensions
{
    unsigned x, y;
    x = ReadVariable <unsigned> (CONFIG_FILE_PATH, "board_width");
    y = ReadVariable <unsigned> (CONFIG_FILE_PATH, "board_height");

    return Coor (x, y);
} // ReadBoardDimensions ()

int ReadPlayerColor (Player player) // this uses the color defines of ncurses
{
    int color = 0;

    switch (player)
    {
        case player1:
            color = ReadVariable <int> (CONFIG_FILE_PATH, "color_player1");
            break;
        case player2:
            color = ReadVariable <int> (CONFIG_FILE_PATH, "color_player2");
            break;
        default: // no_player
            color = ReadVariable <int> (CONFIG_FILE_PATH, "color_empty");
    }

    return color;
} // ReadPlayerColor ()

int ReadItemColor () // this uses the color defines of ncurses
{
    return ReadVariable <int> (CONFIG_FILE_PATH, "color_item");
} // ReadItemColor ()

float ReadBarrierApparitionFrequency () // this will return the barrier apparition frequency
{
    float frequency = ReadVariable <float> (CONFIG_FILE_PATH, "barrier_apparition_frequency");

    if (frequency <= 1 && frequency >= 0)
        return frequency;
    else
        throw std::runtime_error ("Wrong number, please enter a number between 0 and 1.");
} // ReadBarrierApparitionFrequency ()

float ReadItemApparitionFrequency () // this will return the items apparition frequency
{
    float frequency = ReadVariable <float> (CONFIG_FILE_PATH, "item_apparition_frequency");

    if (frequency <= 1 && frequency >= 0)
        return frequency;
    else
        throw std::runtime_error ("Wrong number, please enter a number between 0 and 1.");
} // ReadItemApparitionFrequency ()

bool ReadDotsForBackground () // this will return the booleen that set if the background has dots
{
    return ReadVariable <bool> (CONFIG_FILE_PATH, "dots_for_background");
} // ReadDotsForBackground ()

void WriteFloatInFile (const std::string &KVariableName, char* VariableValue) // this will call the writevariable template for an integer
{
    std::string StrValue (VariableValue);

    if (std::stoi (VariableValue) >= 0)
        WriteVariable <float> (CONFIG_FILE_PATH, KVariableName, std::stof (VariableValue) / 100, false);
    else
        throw std::runtime_error ("Wrong value, must be equal or more than 0");

} // WriteFloatInFile ()

void WriteIntInFile (const std::string &KVariableName, char* VariableValue) // this will call the writevariable template for a float
{
    std::string StrValue (VariableValue);

    if (std::stof (VariableValue) >= 0)
        WriteVariable <int> (CONFIG_FILE_PATH, KVariableName, std::stoi (VariableValue), false);
    else
        throw std::runtime_error ("Wrong value, must be equal or more than 0");

} // WriteIntInFile ()

void WriteCommentInFile (const std::string &KComment, bool EraseFile /* = false */) // this will call the writevariable template for a comment
{
    std::string StartingChar = "#";
    WriteVariable <std::string> (CONFIG_FILE_PATH, StartingChar + ' ' + KComment, "\n", EraseFile);

} // WriteCommentInFile ()
