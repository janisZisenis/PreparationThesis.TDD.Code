#ifndef Distribution_H
#define Distribution_H

#define DIR_END_MAX 27

#include "global.h"
#include <vector>


#include "Core_EXPORT.h"

struct Distribution{
    doubflo* f;
    int *dirs;
    int dir_start;
    int dir_end;
    const char* name;
};

struct Grid;

class Core_EXPORT DistributionHelper
{
public:
    static struct Distribution getDistribution7();
    static struct Distribution getDistribution13();
    static struct Distribution getDistribution19();
    static struct Distribution getDistribution27();

    static struct Distribution getDistribution(std::string name);

public:
    static std::vector<std::vector<doubflo> > getQsWithoutRowsWithOnlyZeroValues(const struct Grid &grid, const struct Distribution &d);
    static std::vector<std::vector<doubflo> > getAllQsOnFluidNodes(const struct Grid &grid, const struct Distribution &d);
    static int getNeighborNodeIndexInGivenDirection(const struct Distribution &d, const struct Grid &grid, const int node, const int dir_index);
    static std::vector<std::vector<doubflo> > getVectorWithoutRowsWithOnlyZeroValues(std::vector<std::vector<doubflo> > qs);
    static void printQs(std::vector<std::vector<doubflo> > qs, int decimalPlaces);
};

#endif
