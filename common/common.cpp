#include "common.h"

#include <sstream>

std::string bool_as_text(bool b)
{
    std::stringstream converter;
    converter << std::boolalpha << b;
    return converter.str();
}
