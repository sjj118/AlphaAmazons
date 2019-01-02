#ifndef OPENINGGENERATE_LOGGER_H
#define OPENINGGENERATE_LOGGER_H

#include <string>

namespace Logger {
    extern std::string debug, data, globaldata;

    inline void clear() { debug = data = globaldata = ""; }

}


#endif //OPENINGGENERATE_LOGGER_H
