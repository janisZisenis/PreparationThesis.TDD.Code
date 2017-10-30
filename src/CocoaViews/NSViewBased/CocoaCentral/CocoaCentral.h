#ifndef COCOAVIEWS_COCOACENTRAL_H
#define COCOAVIEWS_COCOACENTRAL_H

#include <Hierarchies/CNVisitable/CNVisitable.h>
#include "CocoaViews/NSViewBased/NSViewBased.h"

class CocoaCentral;

class CocoaCentral;
typedef std::shared_ptr<CocoaCentral> CocoaCentralPtr;

class CocoaCentral : public NSViewBased, public virtual CNVisitable {
public:
    virtual ~CocoaCentral() {}
protected:
    CocoaCentral() {}
};

#endif //COCOAVIEWS_COCOACENTRAL_H