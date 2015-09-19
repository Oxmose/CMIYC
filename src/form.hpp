/**
*
* @file form.hpp
*
* @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
*
* @date : 08/01/14
*
* @version : 1.0
*
* @brief Header of the Form class.
*
* @see form.cpp
*
**/

#ifndef _FORM_HEADER_GUARD_
#define _FORM_HEADER_GUARD_

#include "confmanager.hpp"

#include <vector>
#include <form.h>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <ncurses.h>

/// @class CForm form.hpp
/// @brief The form used as settings panel.
/// @details The fom will generate a setting window that will enable the user to set the option as wanted.
class CForm
{
    public:
        /// @fn CForm (const std::vector <std::string> &KVariableNames, const std::vector <FIELDTYPE*> &KFieldTypes, std::vector < void*> VariablesValuesPt);
        /// @param KVariableNames The names of the variables that appear in the form.
        /// @param KFieldTypes The types of the variables that appear in the form.
        /// @param VariablesValuesPt The values of the variables that appear in the form.
        /// @brief The constructor.
        /// @details Will create the form windows and generate all the fields according to the variables.
        /// we give in first, second and thirs place parameters.
        CForm (const std::vector <std::string> &KVariableNames, const std::vector <FIELDTYPE*> &KFieldTypes, std::vector < void*> VariablesValuesPt);

        /// @fn ~CForm ();
        /// @brief The destructor
        /// @details Will free the memory the fields used and remove the WINDOW.
        ~CForm ();

        /// @fn void Display ();
        /// @brief Displays the setting form.
        /// @details The method will diplay the setting form that the user is able to modify
        /// and will send the new values to the configuration manager.
        void Display ();

    private:

        /// @brief contain the values of the variables that appear in the fields
        std::vector <void*> variables;

        /// @brief contain the names of the variables that appear in the fields
        std::vector <std::string> VarNamesVector;

        /// @brief contain the types of the variables that appear in the fields
        std::vector <FIELDTYPE*> RightFieldTypes;

        /// @brief the fields of the form
        FIELD **fields;

        /// @brief the number of fields that appear in the form
        unsigned FieldCount;

        /// @brief the indice of the current field
        unsigned CurrentField;

        /// @brief the form that contains all the fields
        FORM *settingsform;

        /// @brief the windows that will contain the form
        WINDOW *formwin;

};


#endif

