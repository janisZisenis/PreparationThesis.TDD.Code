#ifndef global_h
#define global_h
#define ACCURACY 1

typedef float doubflo;

#define DEBUG 0
#define GLOB_NODE 53

#define DIMENSION 3

#ifdef __unix__
#define PATH_TO_DATA "/home/soeren/gridgen/DATA/"
#else
#define PATH_TO_DATA "/Users/Janis/GridGeneratorLight/DATA"
#endif

#define TESTSUITE "TESTSUITE/"
#define VTK_OUTPUT "VTK_OUTPUT/"
#define STL_OUTPUT "STL_OUTPUT/"
#define STL "STL/"

#define MASTERRANK 0

#include <sstream>

//#define SSTR( x ) static_cast< std::ostringstream & >( \
//        ( std::ostringstream() << std::dec << x ) ).str()

#define SSTR( x ) std::to_string(x)

#endif // !global_h
