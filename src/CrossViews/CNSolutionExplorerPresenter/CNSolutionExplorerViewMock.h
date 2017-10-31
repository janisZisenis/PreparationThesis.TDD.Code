#ifndef CROSSNATIVE_SOLUTIONEXPLORERVIEW_MOCK_H
#define CROSSNATIVE_SOLUTIONEXPLORERVIEW_MOCK_H

#include "CNSolutionExplorerView.h"

class CNSolutionExplorerViewMock;
typedef std::shared_ptr<CNSolutionExplorerViewMock> CNSolutionExplorerViewMockPtr;
class CNSolutionExplorerViewMock : public CNSolutionExplorerView {
public:
    static CNSolutionExplorerViewMockPtr getNewInstance() {
        return CNSolutionExplorerViewMockPtr (new CNSolutionExplorerViewMock());
    }
    virtual ~CNSolutionExplorerViewMock() {}

protected:
    CNSolutionExplorerViewMock() {}

public:
    virtual CNHierarchyIndex getSelectedIndex() override {
        return CNHierarchyIndex();
    };

    virtual void removeIndex(const CNHierarchyIndex& index) override {}
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) override {
        actualVisitable = visitable;
        actualParent = parent;
        actualChildPos = childPos;
    }
    virtual void accept(CNVisitorPtr visitor) override {}

    virtual void expectCalledInsertItem(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) {
        expectedVisitable = visitable;
        expectedParent = parent;
        expectedChildPos = childPos ;
    }

    virtual void verify() {
        verifyInsertItem();
    }

    virtual void setListener(std::shared_ptr<CNSolutionExplorerListener> listener) override {}

private:

    virtual void verifyInsertItem() {
        verifyVisitable();
        verifyParentIndex();
        verfiyChildPos();
    }

    virtual void verifyVisitable() {
        std::string errorMessage = "The CNSolutionExplorerViewMock should have received the CNVisitable during \"insertItem\", but it has not!";
        EXPECT_THAT(actualVisitable, testing::Eq(expectedVisitable)) << errorMessage;
    }
    virtual void verifyParentIndex() {
        std::string errorMessage = "The CNSolutionExplorerViewMock should have received the parent index " + expectedParent.toString() + " during \"insertItem\""
                                   + ". Instead it has received the index " + actualParent.toString();
        EXPECT_THAT(actualParent, testing::Eq(expectedParent)) << errorMessage;
    }
    virtual void verfiyChildPos() {
        std::string errorMessage = "The CNSolutionExplorerViewMock should have received the childPosition " + std::to_string(expectedChildPos) + " during \"insertItem\""
                                   +". Instead it has received the childPosition " + std::to_string(actualChildPos) + "!";
        EXPECT_THAT(actualChildPos, testing::Eq(expectedChildPos));
    }

private:
    CNVisitablePtr expectedVisitable;
    CNHierarchyIndex expectedParent;
    int expectedChildPos;

    CNVisitablePtr actualVisitable;
    CNHierarchyIndex actualParent;
    int actualChildPos;
};

#endif //CROSSNATIVE_SOLUTIONEXPLORERVIEW_MOCK_H