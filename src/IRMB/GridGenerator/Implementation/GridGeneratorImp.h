#ifndef LVICE_GRIDGENERATORIMP_H
#define LVICE_GRIDGENERATORIMP_H

#include <LViCE/LViCE_EXPORT.h>
#include <vector>

#include "LViCE/GridGenerator/GridGenerator.h"

namespace CCore {
    class Acceptor;
    class Visitor;
}

class STLFile;
class GridKernelCPU;

class GridGeneratorImp;
typedef std::shared_ptr<GridGeneratorImp> GridGeneratorImpPtr;

class LViCE_EXPORT GridGeneratorImp : public GridGenerator, public std::enable_shared_from_this<GridGenerator> {
public:
    static GridGeneratorImpPtr getNewInstance(std::string name, double length, double width, double height, double delta, std::string distribution);
    virtual ~GridGeneratorImp();
protected:
    GridGeneratorImp(std::string name, double length, double width, double height, double delta, std::string distribution);

public:
    virtual std::string getName() override;

    virtual void addSTLFile(std::shared_ptr<STLFile> stlFile) override;
    virtual void removeSTLFile(std::shared_ptr<STLFile> stlFile) override;

    virtual void accept(std::shared_ptr<CCore::Visitor> visitor) override;

    virtual double getLength() override;
    virtual double getWidth() override;
    virtual double getHeight() override;
    virtual double getDelta() override;
    virtual std::string getDistribution() override;
    virtual Grid* generateGrid() override;
private:
    GridGeneratorImpPtr sharedFromThis();

    std::vector< std::shared_ptr<STLFile> > stlFiles;
    std::string name;
    double length;
    double width;
    double height;
    double delta;
    std::shared_ptr<GridKernelCPU> gridKernel;
    std::string distribution;
    std::shared_ptr<CCore::Acceptor> acceptor;
};

#endif //LVICE_GRIDGENERATORIMP_H
