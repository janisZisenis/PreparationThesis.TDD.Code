#ifndef CROSSVIEWS_SOLUTIONEXPLORERVIEW_MOCK_H
#define CROSSVIEWS_SOLUTIONEXPLORERVIEW_MOCK_H

#include "SolutionExplorerView.h"

class SolutionExplorerViewMock;
typedef std::shared_ptr<SolutionExplorerViewMock> SolutionExplorerViewMockPtr;
class SolutionExplorerViewMock : public SolutionExplorerView {
public:
    static SolutionExplorerViewMockPtr getNewInstance() {
        return SolutionExplorerViewMockPtr (new SolutionExplorerViewMock());
    }
    virtual ~SolutionExplorerViewMock() {}

protected:
    SolutionExplorerViewMock() {}

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

private:

    virtual void verifyInsertItem() {
        verifyVisitable();
        verifyParentIndex();
        verfiyChildPos();
    }

    virtual void verifyVisitable() {
        std::string errorMessage = "The SolutionExplorerViewMock should have received the CNVisitable during \"insertItem\", but it has not!";
        EXPECT_THAT(actualVisitable, testing::Eq(expectedVisitable)) << errorMessage;
    }
    virtual void verifyParentIndex() {
        std::string errorMessage = "The SolutionExplorerViewMock should have received the parent index " + expectedParent.toString() + " during \"insertItem\""
                                   + ". Instead it has received the index " + actualParent.toString();
        EXPECT_THAT(actualParent, testing::Eq(expectedParent)) << errorMessage;
    }
    virtual void verfiyChildPos() {
        std::string errorMessage = "The SolutionExplorerViewMock should have received the childPosition " + std::to_string(expectedChildPos) + " during \"insertItem\""
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

#endif //CROSSVIEWS_SOLUTIONEXPLORERVIEW_MOCK_H