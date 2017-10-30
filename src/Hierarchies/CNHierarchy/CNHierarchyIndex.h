#ifndef CROSSNATIVE_HIERARCHYINDEX_H
#define CROSSNATIVE_HIERARCHYINDEX_H

#include <vector>
#include <string>

class CNHierarchyIndex {
public:
    CNHierarchyIndex(std::vector<int> child = std::vector<int>()) : childPath(child) {}
    CNHierarchyIndex(CNHierarchyIndex parent, int childPos) : childPath(parent.childPath) {
        childPath.push_back(childPos);
    }

    CNHierarchyIndex parent() const {
        std::vector<int> parentPath = childPath;
        parentPath.pop_back();
        return CNHierarchyIndex(parentPath);
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

    bool operator==(CNHierarchyIndex index) const {
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
                if(i < depth() - 1)
                    s+= ", ";
            }
        }

        s += "}";

        return s;
    }

private:
    std::vector<int> childPath;
};

#endif //CROSSNATIVE_HIERARCHYINDEX_H
