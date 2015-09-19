/**
 *
 * @file form.cpp
 *
 * @authors : J. Saffi, Y. Vidal, Y. Roux, A. Torres Aurora Dugo
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Implementation of the Form class.
 *
 * @see form.hpp
 *
 **/

#include "form.hpp"


CForm::CForm (const std::vector <std::string> &KVariableNames, const std::vector <FIELDTYPE*> &KFieldTypes, std::vector <void*> VariablesValuesPt)
{
    FieldCount = KVariableNames.size ();

    // Init the VarNamesVector an RightFieldTypes
    for (unsigned i (0); i < FieldCount; ++i)
        VarNamesVector.push_back (KVariableNames[i]);

    for (unsigned i (0); i < FieldCount; ++i)
        RightFieldTypes.push_back (KFieldTypes[i]);

    // generating the new fields
    fields = new FIELD * [FieldCount + 1];


    // Generate the new form window
    formwin = newwin (LINES, COLS, 0, 0);
    keypad (formwin, true);

    // Generate the fields
    unsigned Line = 5;

    for (unsigned i (0); i < FieldCount ; ++i)
    {
        fields[i] = new_field (1, 20, Line, 40, 0, 0);

        field_opts_off (fields[i], O_AUTOSKIP);
        field_opts_off (fields[i], O_NULLOK);
        field_opts_on (fields[i], O_BLANK);


        // Set the type of the field
        set_field_type (fields[i], TYPE_INTEGER, 0, 0);


        // Fill the fields with the curents values
        std::string VarToDisplay;

        if (KFieldTypes[i] == TYPE_INTEGER)
            VarToDisplay = std::to_string ( *( (int*) (VariablesValuesPt[i])));

        else if (KFieldTypes[i] == TYPE_NUMERIC)
            VarToDisplay = std::to_string (int ( 100 * ( *( (float*) (VariablesValuesPt[i])))));

        else
            VarToDisplay = "Unknow";

        set_field_buffer (fields[i], 0, VarToDisplay.c_str ());

        ++Line;
    }

    // must set the last field to NULL
    fields[FieldCount] = NULL;


    // Generate the form
    CurrentField = 0;

    settingsform = new_form (fields);
    set_field_back (fields[CurrentField], COLOR_PAIR(3) | A_REVERSE);



    // Get the dimensions of the form
    int rows;
    int cols;
    scale_form (settingsform, &rows, &cols);

    // Display settings
    set_form_win (settingsform, formwin);
    set_form_sub (settingsform, derwin (formwin, rows, cols, 0, 0));
    post_form (settingsform);
}

CForm::~CForm ()
{
    unpost_form (settingsform);
    free_form (settingsform);

    for (unsigned i (0); i < FieldCount - 1; ++i)
        free_field (fields[i]);

    delete fields;


    delwin (formwin);	
    refresh ();

}

void CForm::Display ()
{
    int Line = 1;

    // Generate the display info
    mvwprintw (formwin, Line, COLS / 2 - 8, "Settings");
    mvwprintw (formwin, Line + 2, 1, "Up / Down to change field, q to quit.");

    for (unsigned i (0); i < VarNamesVector.size (); ++i)    	
        mvwprintw (formwin, Line + i + 4, 1, VarNamesVector[i].c_str ());

    int c = 0;

    form_driver (settingsform, REQ_END_FIELD);

    do
    {
        set_field_back (fields[CurrentField], COLOR_PAIR(3) | A_REVERSE);

        box (formwin, 0, 0);

        refresh ();

        c = wgetch (formwin);

        switch (c)
        {
            case KEY_UP:
                form_driver (settingsform, REQ_PREV_FIELD);
                form_driver (settingsform, REQ_END_FIELD);

                if (CurrentField > 0 && form_driver (settingsform, REQ_VALIDATION) == E_OK)
                {
                    mvwprintw (formwin, CurrentField + 5, COLS - 13, "             ");
                    set_field_back (fields[CurrentField], 0);	
                    --CurrentField;
                }
                else if (form_driver (settingsform, REQ_VALIDATION) == E_OK)
                {
                    mvwprintw (formwin, CurrentField + 5, COLS - 13, "             ");
                    set_field_back (fields[CurrentField], 0);	
                    CurrentField = FieldCount - 1;
                }
                else
                {
                    mvwprintw (formwin, CurrentField + 5, COLS - 13, "Wrong value");
                }

                break;

            case KEY_DOWN:
                form_driver (settingsform, REQ_NEXT_FIELD);
                form_driver (settingsform, REQ_END_FIELD);

                if (CurrentField < FieldCount - 1 && form_driver (settingsform, REQ_VALIDATION) == E_OK)
                {
                    mvwprintw (formwin, CurrentField + 5, COLS - 13, "             ");
                    set_field_back (fields[CurrentField], 0);	
                    ++CurrentField;
                }
                else if (form_driver (settingsform, REQ_VALIDATION) == E_OK)
                {
                    mvwprintw (formwin, CurrentField + 5, COLS - 13, "             ");
                    set_field_back (fields[CurrentField], 0);	
                    CurrentField = 0;
                }
                else
                {
                    mvwprintw (formwin, CurrentField + 5, COLS - 13, "Wrong value");
                }
                break;

            case KEY_BACKSPACE: case 127:
                form_driver (settingsform, REQ_PREV_CHAR);
                form_driver (settingsform, REQ_DEL_CHAR);

                break;

            case 27 : // ESC
                throw user_exit ();

            default:
                form_driver (settingsform, c);


        }

    } while (c != 'q' && c != 'Q' && c != KEY_ENTER);

    // validate the last field that have been modified
    form_driver (settingsform, REQ_VALIDATION);

    // write the configuration file
    WriteCommentInFile ("Configuration file", true);





    for (unsigned i (0); i < VarNamesVector.size (); ++i)
    {
        if (RightFieldTypes[i] == TYPE_INTEGER)	
            WriteIntInFile (VarNamesVector[i], field_buffer (fields[i], 0));
        else if (RightFieldTypes[i] == TYPE_NUMERIC)
            WriteFloatInFile (VarNamesVector[i], field_buffer (fields[i], 0));
    }

    clear ();
    refresh ();

}
