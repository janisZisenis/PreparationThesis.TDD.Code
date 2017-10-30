#ifndef CODEBASEIMP_COMMANDSTACK_H
#define CODEBASEIMP_COMMANDSTACK_H

#include "Base/CBCommandHistory/CBCommandHistory.h"
#include "Base/CBCommandInvoker/CBCommandInvoker.h"
#include <stack>
#include <string>

class CBNoExecutedCommandsException : public std::exception {
    const char *what() const throw() override {
        return std::string("There are no executed commands to be undone!").c_str();
    }
};

class CBNoUndoneCommandsException : public std::exception {
    const char *what() const throw() override {
        return std::string("There are no undone commands to be executed!").c_str();
    }
};

class CBSubject;
class CBCommand;

class CBCommandStack;
typedef std::shared_ptr<CBCommandStack> CBCommandStackPtr;
class CBCommandStack : public CBCommandInvoker, public CBCommandHistory {
public:
    static CBCommandStackPtr getNewInstance();
    virtual ~CBCommandStack();

protected:
    CBCommandStack();

public:
    virtual void invoke(std::shared_ptr<CBCommand> command) override;

    virtual void undo() override;
    virtual void redo() override;

    virtual bool undoIsPossible() override;
    virtual bool redoIsPossible() override;

    virtual void attach(std::shared_ptr<CBObserver> observer) override;
    virtual void detach(std::shared_ptr<CBObserver> observer) override;
private:
    virtual void removeUndoneCommands();
    virtual void executeCommand(std::shared_ptr<CBCommand> command);

    virtual void undoCommand();
    virtual void redoCommand();

    virtual void move(std::stack<std::shared_ptr<CBCommand> > &from, std::stack<std::shared_ptr<CBCommand> > &to);

    virtual void notifyObservers();

    std::shared_ptr<CBSubject> subject;
    std::stack< std::shared_ptr<CBCommand> > executedCommands;
    std::stack< std::shared_ptr<CBCommand> > undoneCommands;
};

#endif //CODEBASEIMP_COMMANDSTACK_H