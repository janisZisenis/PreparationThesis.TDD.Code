#ifndef CROSSNATIVE_CREATECOMPONENTSTRATEGY_H
#define CROSSNATIVE_CREATECOMPONENTSTRATEGY_H

#include <memory>
#include <string>

class CNCreationCanceledException : public std::exception {
    const char *what() const throw() override {
        return std::string("The creation was canceled!").c_str();
    }
};

class CNComponent;

class CNCreateComponentStrategy;
typedef std::shared_ptr<CNCreateComponentStrategy> CNCreateComponentStrategyPtr;

class CNCreateComponentStrategy {
public:
    virtual ~CNCreateComponentStrategy() {}
protected:
    CNCreateComponentStrategy() {}

public:
    virtual std::shared_ptr<CNComponent> createComponent() = 0;
};

#endif //CROSSNATIVE_CREATECOMPONENTSTRATEGY_H
