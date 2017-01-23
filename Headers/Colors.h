/*  colors used by program  */

#if defined(_WIN32)
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