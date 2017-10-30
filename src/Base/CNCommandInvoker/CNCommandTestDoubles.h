#ifndef CROSSNATIVE_COMMAND_TESTDOUBLES_H
#define CROSSNATIVE_COMMAND_TESTDOUBLES_H

#include "CNCommand.h"
#include <string>

class CNCommandDummy;
typedef std::shared_ptr<CNCommandDummy> CNCommandDummyPtr;
class CNCommandDummy : public CNCommand {
public:
    static CNCommandDummyPtr getNewInstance() {
        return CNCommandDummyPtr(new CNCommandDummy());
    }

    virtual ~CNCommandDummy() {}

protected:
    CNCommandDummy() {}

public:
    virtual void execute() override {}
    virtual void undo() override {}
};

class CNCommandSpy;
typedef std::shared_ptr<CNCommandSpy> CNCommandSpyPtr;
class CNCommandSpy : public CNCommandDummy {
public:
    static CNCommandSpyPtr getNewInstance() {
        return CNCommandSpyPtr(new CNCommandSpy());
    }

    virtual ~CNCommandSpy() {}

protected:
    CNCommandSpy() {}

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

#endif //CROSSNATIVE_COMMAND_TESTDOUBLES_H