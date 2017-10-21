#ifndef Logger_h
#define Logger_h

#include "global.h"
#include "Core_EXPORT.h"
#include <memory>
#include <string>

enum RankLogLevel {
    MASTER, ALLRANKS
};


class Logger
{
public:
    static Logger Core_EXPORT *getInstance();
    static void Core_EXPORT log(std::string message);
    static void Core_EXPORT logFloat(doubflo value);
    static void Core_EXPORT close();
    static void Core_EXPORT logTerminal(std::string message, RankLogLevel level = ALLRANKS);

    static RankLogLevel level;
private:
    static void initalInstane();


    static Logger* instance;
    static FILE *file;
    static std::string modus;
    static std::string path;

    

    Logger();
    Logger(const Logger&);
};

#endif
