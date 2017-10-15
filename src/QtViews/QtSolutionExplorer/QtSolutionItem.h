#ifndef QTVIEWS_QTSOLUTIONITEM_H
#define QTVIEWS_QTSOLUTIONITEM_H

#include <memory>
#include <vector>
#include <string>

class QtSolutionItem;
typedef std::shared_ptr<QtSolutionItem> QtSolutionItemPtr;
class QtSolutionItem : public std::enable_shared_from_this<QtSolutionItem> {
public:
    static QtSolutionItemPtr getNewInstance(std::string name, std::string type) {
        return QtSolutionItemPtr(new QtSolutionItem(name, type));
    }
    virtual ~QtSolutionItem() {};
private:
    QtSolutionItem(std::string name, std::string type) : name(name), type(type) {};

public:
    virtual QtSolutionItemPtr getParent() {
        return parent.lock();
    }
    virtual void setParent(QtSolutionItemPtr parent) {
        this->parent = parent;
    }
    virtual int getChildCount() {
        return (int)children.size();
    }
    virtual int getRow() {
        if (!this->getParent()) return -1;

        return getParent()->childPos(me());
    }
    virtual QtSolutionItemPtr getChildAt(int index) {
        return children[index];
    }
    virtual std::string getName() {
        return name;
    }
    virtual std::string getType() {
        return type;
    }
    virtual void insertChild(QtSolutionItemPtr child, int index) {
        children.insert(children.begin()+index, child);
        child->setParent(me());
    }
    virtual void removeChild(int index) {
        children.erase(children.begin()+index);
    }

private:
    virtual int childPos(QtSolutionItemPtr item) {
        int pos = (int) (std::find(children.begin(), children.end(), item) - children.begin());
        return pos >= getChildCount() ? -1 : pos;
    }
    QtSolutionItemPtr me() {
        return std::dynamic_pointer_cast<QtSolutionItem>(this->shared_from_this());
    }


private:
    std::weak_ptr<QtSolutionItem> parent;
    std::vector<QtSolutionItemPtr> children;
    std::string name;
    std::string type;
};

#endif //QTVIEWS_QTSOLUTIONITEM_H