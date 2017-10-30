#ifndef CROSSNATIVE_COMPOSERFACTORY_H
#define CROSSNATIVE_COMPOSERFACTORY_H

#include <memory>
#include <vector>

class CNComposer;
class CNVisitor;

class CNComposerFactory;
typedef std::shared_ptr<CNComposerFactory> CNComposerFactoryPtr;

class CNComposerFactory {
public:
    static CNComposerFactoryPtr getNewInstance();
    virtual ~CNComposerFactory();
private:
    CNComposerFactory();

public:
    virtual std::shared_ptr<CNComposer> makeCNNullComposer();
    virtual std::shared_ptr<CNComposer> makeCNVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);
};


#endif //CROSSNATIVE_COMPOSERFACTORY_H