/*  Formatting output to user  */
#ifndef __Format__
#define __Format__

#include <iostream>
using namespace std;

/*   colors   */

// to disable colors, uncomment this
// #define NOCOLOR

#if defined(_WIN32)
    #include "colorwin.hpp"
    using namespace colorwin;

    #define RED color(red)
    #define BLUE color(magenta)
    #define GREEN color(green)
    #define YELLOW color(yellow)
    #define CYAN color(cyan)

    #define WHITE color(white)
#elif defined(NOCOLOR)
    #define RED ""
    #define BLUE ""
    #define GREEN ""
    #define YELLOW ""
    #define CYAN ""

    #define WHITE ""
#else
    #define RED "\033[0;31m"
    #define BLUE "\033[0;34m"
    #define GREEN "\033[0;32m"
    #define YELLOW "\033[1;33m"
    #define CYAN "\033[0;36m"

    #define WHITE "\033[0m"
#endif


/*   info   */
void Print_Credits();
void Print_Prompt();
void Print_Help();

#endif /* __Format__ */