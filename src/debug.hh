#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

#define CERR(x) do { std::cerr << x; } while (0)

// http://stackoverflow.com/questions/12198449/cross-platform-macro-for-silencing-unused-variables-warning/12199209#12199209
#define MON_Internal_UnusedStringify(macro_arg_string_literal) #macro_arg_string_literal

#define MONUnusedParameter(macro_arg_parameter) _Pragma(MON_Internal_UnusedStringify(unused(macro_arg_parameter)))

#endif // DEBUG_H_
