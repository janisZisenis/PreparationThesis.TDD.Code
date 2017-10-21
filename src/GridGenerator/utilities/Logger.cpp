#define _CRT_SECURE_NO_DEPRECATE
#include "Logger.h"
#include "mpi.h"

#include <global.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

FILE *Logger::file = 0;
Logger* Logger::instance = 0;
std::string Logger::modus = "a";
RankLogLevel Logger::level = ALLRANKS;

Logger* Logger::getInstance()
{
    if (!instance)
        initalInstane();

    return instance;
}

void Logger::initalInstane()
{
//	std::string path = PATH_TO_DATA;
//	std::string filePath = path + "/messages.log";
//
    instance = new Logger();
//    file = fopen(filePath.c_str(), modus.c_str());
//    if (!file) {
//        printf("can't open file. %s\n", filePath.c_str());
//        exit(1);
//    }
//    std::time_t t = std::time(0);
//    struct tm tm = *localtime(&t);
//    fprintf(file, "\n--START LOGGING : %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
//    fprintf(file, "grid; x; y; z; triangles; initalGPU; findNeighbor; copyNeighbor; copyTriangles; generateGridKernel; compleCPU; completeGPU; speedup");
}

void Logger::logTerminal(std::string message, RankLogLevel level)
{
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    std::stringstream ss;
//
//    if (level == MASTER)
//        ss << "  ";
//
//    ss << "[" << rank << "] " << message;
//
//    if (Logger::level == ALLRANKS && level == ALLRANKS)
//        printf(ss.str().c_str());
//
//    if (level == MASTER)
//        if (rank == MASTERRANK)
//            printf(ss.str().c_str());
}

void Logger::log(std::string message)
{
//    message += "; ";
//    fprintf(file, message.c_str());
}

void Logger::logFloat(doubflo value)
{
//    fprintf(file, "%2.5f; ", value);
}

void Logger::close()
{
//    fprintf(file, "--END OF LOG--\n");
//    fclose(file);
}

Logger::Logger(const Logger& logger)
{

}

Logger::Logger()
{

}
