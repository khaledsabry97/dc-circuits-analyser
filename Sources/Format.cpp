#include "Format.h"

void Print_Credits()
{
    cout << YELLOW 

        << "Credits:\n"
        << "> Hadi Maher\tMahmoud Youssri\n"
        << "> Mohammed Magdi\tKhaled Sabri\tMahmoud Adas" 
        << "\n\n" 

        << WHITE;
}

void Print_Prompt()
{
    cout << BLUE << ">>> " << CYAN;
}

#define Point_str "----> "
void Print_Help()
{
    cout << GREEN 

        << "Enter the elements node by node" 
        << "\n\n" 

        << "Valid Commands:-\n" 
        << Point_str << "x \tend the node\n" 
        << Point_str << "xx \tend all nodes\n" 
        << Point_str << "h \thelp\n" 
        << Point_str << "c \tcredits\n" 
        << Point_str << "p \tprint the completed nodes\n" 
        << Point_str << "Ctrl+z or Ctrl+c\texit program\n" 
        << Point_str << "# \tmake a comment" 
        << "\n\n" 

        << "Valid Types:-\n" 
        << Point_str << "r \tResistance\n" 
        << Point_str << "e \tVoltage Source\n" 
        << Point_str << "j \tCurrent Source\n\n" 
        << "All commands/types could be written in upper or lower case" 
        << "\n\n"

        << WHITE;
}