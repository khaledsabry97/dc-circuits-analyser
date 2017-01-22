/*
        _Input source 
*/
#include "Data.h"

//    private:
        void Circuit::_Input::Command_Parse()
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
                    break;
            }
        }

        void Circuit::_Input::_Element_Parse()
        {
            if (!Circuit::_Is_valid_type(type) || id < 0)
                _is_valid = false;
        }

//    public:
        Circuit::_Input::_Input() 
            :_is_valid(true), type('\0'), id(-1), val(-1), _cmd(NotCommand)
        {}
        
        // TODO: prevent adding invalid line like this j1 without val
        // TODO: when typing jj or tt it should be invalid not duplicate
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
                                        _line.c_str(),       // line to parse
                                        " %c%i %lf ",       // search's expression
                                        &type, &id, &val    // variables to store tokens at
                                );

                type = toupper(type);

                // 0    --> ask again (continue)
                // 1    --> parse command
                // 3    --> parse element

                // else --> error
                switch (num_of_tokens)
                {
                    case 0:
                        continue;
                    case 1:
                        Command_Parse();
                        return;
                    case 3:
                        _Element_Parse();
                        return;
                    default: 
                        _is_valid = false;
                        return;
                }
            }
        }

        bool Circuit::_Input::IsElement()
        {
            return (_is_valid && _cmd == NotCommand);
        }

        bool Circuit::_Input::IsCommand()
        {
            return (_cmd != NotCommand);
        }

        bool Circuit::_Input::IsInvalid()
        {
            return (!_is_valid);
        }

        Command Circuit::_Input::GetCommand()
        {
            return (_cmd);
        }

        void Circuit::_Input::Reset()
        {
            _Input();
        }