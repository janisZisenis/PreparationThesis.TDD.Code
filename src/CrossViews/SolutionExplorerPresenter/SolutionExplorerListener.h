#ifndef CROSSVIEWS_SOLUTIONEXPLORERLISTENER_H
#define CROSSVIEWS_SOLUTIONEXPLORERLISTENER_H

#include <memory>

class SolutionExplorerListener;
typedef std::shared_ptr<SolutionExplorerListener> SolutionExplorerListenerPtr;

class SolutionExplorerListener {
public:
    virtual ~SolutionExplorerListener() {}
protected:
    SolutionExplorerListener() {}

public:
    virtual void onSelectionChanged() = 0;
};

#endif //CROSSVIEWS_SOLUTIONEXPLORERLISTENER_H