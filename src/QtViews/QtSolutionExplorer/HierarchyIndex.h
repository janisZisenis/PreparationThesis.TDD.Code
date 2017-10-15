#ifndef QTAPP_HIERARCHYINDEX_H
#define QTAPP_HIERARCHYINDEX_H

#include <vector>

class HierarchyIndex {
public:
    HierarchyIndex(std::vector<int> child = std::vector<int>()) : childPath(child) {}
    HierarchyIndex(HierarchyIndex parent, int childPos) : childPath(parent.childPath) {
        childPath.push_back(childPos);
    }

    HierarchyIndex parent() {
        std::vector<int> parentPath = childPath;
        parentPath.pop_back();
        return HierarchyIndex(parentPath);
    }

    bool isValid() {
        return depth() > 0;
    }

    int depth() {
        return (int)childPath.size();
    }
    int childPosition() {
        return childPath.back();
    }
    int operator[](int i) {
        return childPath[i];
    }

    bool operator==(HierarchyIndex index) {
        if(depth() != index.depth()) return false;

        for(int i = 0; i < childPath.size(); i++) {
            if(childPath[i] != index.childPath[i]) return false;
        }

        return true;
    }

private:
    std::vector<int> childPath;
};

#endif //QTAPP_HIERARCHYINDEX_H
