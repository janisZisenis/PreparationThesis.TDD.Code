#ifndef CODEBASE_COMMAND_MOCKS_H
#define CODEBASE_COMMAND_MOCKS_H

#include "CBCommand.h"
#include <string>

class CBCommandDummy;
typedef std::shared_ptr<CBCommandDummy> CBCommandDummyPtr;
class CBCommandDummy : public CBCommand {
public:
    static CBCommandDummyPtr getNewInstance() {
        return CBCommandDummyPtr(new CBCommandDummy());
    }

    virtual ~CBCommandDummy() {}

protected:
    CBCommandDummy() {}

public:
    virtual void execute() override {}
    virtual void undo() override {}
};

class CBCommandSpy;
typedef std::shared_ptr<CBCommandSpy> CBCommandSpyPtr;
class CBCommandSpy : public CBCommandDummy {
public:
    static CBCommandSpyPtr getNewInstance() {
        return CBCommandSpyPtr(new CBCommandSpy());
    }

    virtual ~CBCommandSpy() {}

protected:
    CBCommandSpy() {}

public:
    virtual void execute() override {
        logString.append("e");
    }
    virtual void undo() override {
        logString.append("u");
    }

    virtual std::string getLogString() {
        return logString;
    }
private:
    std::string logString;
};

#endif //CODEBASE_COMMAND_MOCKS_H