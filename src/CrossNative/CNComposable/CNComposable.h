#ifndef CROSSNATIVE_COMPOSABLE_H#define CROSSNATIVE_COMPOSABLE_H#include <memory>#include <string>#include <vector>#include <CrossNative/CrossNative_EXPORT.h>class CNChildNotFoundException : public std::exception {    const char *what() const throw() override {        return std::string("The removed component was not found in children!").c_str();    }};class CNComposer;class CNComponent;class CNComposable;typedef std::shared_ptr<CNComposable> CNComposablePtr;class CrossNative_EXPORT CNComposable {public:    static CNComposablePtr getNewInstance(std::shared_ptr<CNComposer> composer);    virtual  ~CNComposable();protected:    CNComposable(std::shared_ptr<CNComposer> composer);public:    virtual void add(std::shared_ptr<CNComponent> child);    virtual void remove(std::shared_ptr<CNComponent> child);private:    std::shared_ptr<CNComposer> composer;    std::vector< std::shared_ptr<CNComponent> > children;};#endif //CROSSNATIVE_COMPOSABLE_H