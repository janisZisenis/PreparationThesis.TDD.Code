#ifndef IRMB_CREATEGRIDGENERATORSTRATEGY_H
#define IRMB_CREATEGRIDGENERATORSTRATEGY_H

#include <CrossViews/TransActions/AddAction/CreateComponentStrategy.h>

class GridGenerator;
class CNComposer;

class CreateGridGeneratorStrategy;
typedef std::shared_ptr<CreateGridGeneratorStrategy> CreateGridGeneratorStrategyPtr;

class CreateGridGeneratorStrategy : public CreateComponentStrategy {
public:
    static CreateGridGeneratorStrategyPtr getNewInstance();
    virtual ~CreateGridGeneratorStrategy();
private:
    CreateGridGeneratorStrategy();

public:
    virtual std::shared_ptr<CNComponent> createComponent() override;
};

#endif //IRMB_CREATEGRIDGENERATORSTRATEGY_H
