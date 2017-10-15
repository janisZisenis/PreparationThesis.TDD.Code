#ifndef QTAPP_QTPROPERTIESITEM_H
#define QTAPP_QTPROPERTIESITEM_H

#include <memory>
#include <vector>
#include <string>

class QtPropertiesItem;
typedef std::shared_ptr<QtPropertiesItem> QtPropertiesItemPtr;
class QtPropertiesItem : public std::enable_shared_from_this<QtPropertiesItem> {
public:
    static QtPropertiesItemPtr getNewInstance(std::string property, std::string value) {
        return QtPropertiesItemPtr(new QtPropertiesItem(property, value));
    }
    virtual ~QtPropertiesItem() {};
private:
    QtPropertiesItem(std::string property, std::string value) : property(property), value(value) {};

public:
    virtual QtPropertiesItemPtr getParent() {
        return parent.lock();
    }
    virtual void setParent(QtPropertiesItemPtr parent) {
        this->parent = parent;
    }

    virtual int getChildCount() {
        return (int)children.size();
    }
    virtual int getRow() {
        if (!this->getParent()) return -1;

        return getParent()->childPos(sharedFromThis());
    }
    virtual QtPropertiesItemPtr getChildAt(int index) {
        return children[index];
    }

    virtual std::string getValue() {
        return value;
    }

    virtual std::string getProperty() {
        return property;
    }

    virtual void appendChild(QtPropertiesItemPtr child) {
        children.push_back(child);
        child->setParent(sharedFromThis());
    }

    virtual void removeChild(int index) {
        children.erase(children.begin()+index);
    }

private:
    virtual int childPos(QtPropertiesItemPtr item) {
        int pos = (int) (std::find(children.begin(), children.end(), item) - children.begin());
        return pos >= getChildCount() ? -1 : pos;
    }

    QtPropertiesItemPtr sharedFromThis() {
        return std::dynamic_pointer_cast<QtPropertiesItem>(this->shared_from_this());
    }

    std::weak_ptr<QtPropertiesItem> parent;
    std::vector<QtPropertiesItemPtr> children;
    std::string property;
    std::string value;
};

#endif //QTAPP_QTPROPERTIESITEM_H