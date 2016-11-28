#include "Data.h"

/*      Circuit     */

//  public:
    void Circuit::Read()
    {
        // loop:
        //      addd node with number
        //      loop:
        //          add elements
        //      stop on x
        //  stop on xx

        cout << "Enter circuit's nodes\nWhen node is entered, type x \nWhen finished the circuit, type xx\n\n";

        for (int i = 1;; i++)
        {
            // new node with num = i
            Node* n = new Node;

            cout << "Node " << i << ":\n";

            while (true)
            {
                // read line
                string line; 
                cin.getline(line);
                // end node if x, return if xx
                if (line[0] == 'x')
                {
                    if (line[1] == 'x')
                        return;
                    else 
                        break;
                }

                // parse line into variables 
                // check if line is valid

                // new element with variables
            }
        }
    }
