#ifndef COCOAVIEWS_HIERARCHYINDEX_H
#define COCOAVIEWS_HIERARCHYINDEX_H

#include <vector>

class CocoaModelIndex {
public:
    CocoaModelIndex(std::vector<int> child = std::vector<int>()) : childPath(child) {}
    CocoaModelIndex(CocoaModelIndex parent, int childPos) : childPath(parent.childPath) {
        childPath.push_back(childPos);
    }

    CocoaModelIndex parent() {
        std::vector<int> parentPath = childPath;
        parentPath.pop_back();
        return CocoaModelIndex(parentPath);
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

    bool operator==(CocoaModelIndex index) {
         if(depth() != index.depth()) return false;

        for(int i = 0; i < childPath.size(); i++) {
            if(childPath[i] != index.childPath[i]) return false;
        }

        return true;
    }

private:
    std::vector<int> childPath;
};

#endif //COCOAVIEWS_HIERARCHYINDEX_H
