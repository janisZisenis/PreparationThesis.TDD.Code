#ifndef CROSSVIEWS_HIERARCHYINDEX_H
#define CROSSVIEWS_HIERARCHYINDEX_H

#include <vector>

class HierarchyIndex {
public:
    HierarchyIndex(std::vector<int> child = std::vector<int>()) : childPath(child) {}
    HierarchyIndex(HierarchyIndex parent, int childPos) : childPath(parent.childPath) {
        childPath.push_back(childPos);
    }

    HierarchyIndex parent() const {
        std::vector<int> parentPath = childPath;
        parentPath.pop_back();
        return HierarchyIndex(parentPath);
    }

    bool isValid() const {
        return depth() > 0;
    }

    int depth() const {
        return (int)childPath.size();
    }
    int childPosition() const {
        return childPath.back();
    }
    int operator[](int i) const {
        return childPath[i];
    }

    bool operator==(HierarchyIndex index) const {
         if(depth() != index.depth()) return false;

        for(int i = 0; i < childPath.size(); i++) {
            if(childPath[i] != index.childPath[i]) return false;
        }

        return true;
    }

    std::string toString() const {
        std::string s = "{";

        if(!isValid()) {
            s += "invalid";
        } else {
            for (int i = 0; i < depth(); i++) {
                s += std::to_string(childPath[i]);
                if(i != depth() - 1)
                    s+= "; ";
            }
        }

        s += "}";

        return s;
    }

private:
    std::vector<int> childPath;
};

#endif //CROSSVIEWS_HIERARCHYINDEX_H
