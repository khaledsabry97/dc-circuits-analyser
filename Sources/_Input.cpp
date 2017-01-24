/*
        _Input source 
*/
#include "Data.h"

//    private:

void Circuit::_Input::_Command_Parse()
{
    switch (type)
    {
        case 'H':
            _cmd = Help;
            break;
        case 'X':
            // if user typed another x, it is EndAll
            if (sscanf(_line.c_str(), " x%c", &type) == 1)
            {
                // user typed another x
                if (toupper(type) == 'X')
                    _cmd = EndAll;
            }
            else 
                _cmd = EndNode;
            
            break;
        case 'P':
            _cmd = Print_Circuit;
            break;
        default: 
            input_type = INVALID;
            break;
    }
}

void Circuit::_Input::_Element_Parse()
{
    // requirements for line to represent an element:
        // id > 0
        // _Is_valid_type(type) == True
    
    // check it meets requirements
    if (id < 0 || !_Is_valid_type(type))
        input_type = INVALID;
}

//    public:

Circuit::_Input::_Input() 
{
    Reset();
}

// parse the line and detect whether it has a command or not
void Circuit::_Input::Get()
{
    int num_of_tokens = 0;

    while (true)
    {
        // print the prompt >>>
        cout << PROMPT;

        getline(cin, _line);

        // parse the line and store num of parsed items 
        num_of_tokens = sscanf(
                                _line.c_str(),        // line to parse
                                " %c %i %lf ",       // search's expression
                                &type, &id, &val    // variables to store tokens at
                        );

        type = toupper(type);

        // 0       --> ask again (continue)
        // 1       --> parse command
        // 3       --> parse element

        // default --> error
        switch (num_of_tokens)
        {
            case 0:
                continue;
            case 1:
                input_type = CMD;
                _Command_Parse();
                return;
            case 3:
                input_type = ELMNT;
                _Element_Parse();
                return;
            default: 
                input_type = INVALID;
                return;
        }
    }
}

bool Circuit::_Input::IsElement()
{
    return (input_type == ELMNT);
}

bool Circuit::_Input::IsCommand()
{
    return (input_type == CMD);
}

bool Circuit::_Input::IsInvalid()
{
    return (input_type == INVALID);
}

Command Circuit::_Input::GetCommand()
{
    return (_cmd);
}

void Circuit::_Input::Reset()
{
    input_type = UNKNOWN;
    type = '\0';
    id = val = -1;
    _cmd = InvalidCommand;
}