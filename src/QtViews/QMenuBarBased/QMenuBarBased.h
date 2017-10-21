#ifndef QTVIEWS_QMENUBARBASED_H
#define QTVIEWS_QMENUBARBASED_H

#include <memory>

class QMenuBar;

class QMenuBarBased;
typedef std::shared_ptr<QMenuBarBased> QMenuBarBasedPtr;
class QMenuBarBased {
public:
    virtual ~QMenuBarBased() {};
protected:
    QMenuBarBased() {};

public:
    virtual QMenuBar* getQMenuBar() = 0;
};

#endif //QTVIEWS_QMENUBARBASED_H