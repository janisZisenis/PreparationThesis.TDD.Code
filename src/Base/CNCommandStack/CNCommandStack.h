#ifndef CROSSNATIVE_COMMANDSTACK_H
#define CROSSNATIVE_COMMANDSTACK_H

#include "Base/CNCommandHistory/CNCommandHistory.h"
#include "Base/CNCommandInvoker/CNCommandInvoker.h"
#include <stack>
#include <string>

class CNNoExecutedCommandsException : public std::exception {
    const char *what() const throw() override {
        return std::string("There are no executed commands to be undone!").c_str();
    }
};

class CNNoUndoneCommandsException : public std::exception {
    const char *what() const throw() override {
        return std::string("There are no undone commands to be executed!").c_str();
    }
};

class CNSubject;
class CNCommand;

class CNCommandStack;
typedef std::shared_ptr<CNCommandStack> CNCommandStackPtr;
class CNCommandStack : public CNCommandInvoker, public CNCommandHistory {
public:
    static CNCommandStackPtr getNewInstance();
    virtual ~CNCommandStack();

protected:
    CNCommandStack();

public:
    virtual void invoke(std::shared_ptr<CNCommand> command) override;

    virtual void undo() override;
    virtual void redo() override;

    virtual bool undoIsPossible() override;
    virtual bool redoIsPossible() override;

    virtual void attach(std::shared_ptr<CNObserver> observer) override;
    virtual void detach(std::shared_ptr<CNObserver> observer) override;
private:
    virtual void removeUndoneCommands();
    virtual void executeCommand(std::shared_ptr<CNCommand> command);

    virtual void undoCommand();
    virtual void redoCommand();

    virtual void move(std::stack<std::shared_ptr<CNCommand> > &from, std::stack<std::shared_ptr<CNCommand> > &to);

    virtual void notifyObservers();

    std::shared_ptr<CNSubject> subject;
    std::stack< std::shared_ptr<CNCommand> > executedCommands;
    std::stack< std::shared_ptr<CNCommand> > undoneCommands;
};

#endif //CROSSNATIVE_COMMANDSTACK_H