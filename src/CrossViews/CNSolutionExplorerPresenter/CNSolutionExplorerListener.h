#ifndef CROSSNATIVE_SOLUTIONEXPLORERLISTENER_H
#define CROSSNATIVE_SOLUTIONEXPLORERLISTENER_H

#include <memory>

class CNSolutionExplorerListener;
typedef std::shared_ptr<CNSolutionExplorerListener> CNSolutionExplorerListenerPtr;

class CNSolutionExplorerListener {
public:
    virtual ~CNSolutionExplorerListener() {}
protected:
    CNSolutionExplorerListener() {}

public:
    virtual void onSelectionChanged() = 0;
};

#endif //CROSSNATIVE_SOLUTIONEXPLORERLISTENER_H