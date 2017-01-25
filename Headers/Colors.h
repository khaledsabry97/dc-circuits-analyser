/*  colors used by program  */

#if defined(_WIN32)
    // TODO: test this for windows
    #include "colorwin.hpp"
    using namespace colorwin;

    #define RED color(red)
    #define BLUE color(magenta)
    #define GREEN color(green)
    #define YELLOW color(yellow)
    #define CYAN color(cyan)

    #define WHITE color(white)
#else
    #define RED "\033[0;31m"
    #define BLUE "\033[0;34m"
    #define GREEN "\033[0;32m"
    #define YELLOW "\033[1;33m"
    #define CYAN "\033[0;36m"

    #define WHITE "\033[0m"
#endif