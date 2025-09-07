#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger {
    public:
    template<typename type>
    static void info(const type &msg) {
    #ifndef NDEBUG
        std::cout << "[LOGS] INFO: " << msg << std::endl;
    #endif 
    }

    template<typename  type>
    static void error(const type &msg) {
    #ifndef NDEBUG 
        std::cout << "[LOGS] ERROR: " << msg << std::endl;
    #endif
    }
    
};

#endif // LOGGER_H
