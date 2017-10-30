#ifndef CROSSVIEWS_CREATECOMPONENTSTRATEGY_H
#define CROSSVIEWS_CREATECOMPONENTSTRATEGY_H

#include <memory>
#include <string>

class CreationCanceledException : public std::exception {
    const char *what() const throw() override {
        return std::string("The creation was canceled!").c_str();
    }
};

class CNComponent;

class CreateComponentStrategy;
typedef std::shared_ptr<CreateComponentStrategy> CreateComponentStrategyPtr;

class CreateComponentStrategy {
public:
    virtual ~CreateComponentStrategy() {}
protected:
    CreateComponentStrategy() {}

public:
    virtual std::shared_ptr<CNComponent> createComponent() = 0;
};

#endif //CROSSVIEWS_CREATECOMPONENTSTRATEGY_H
