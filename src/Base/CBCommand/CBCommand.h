#ifndef CODEBASE_COMMAND_H
#define CODEBASE_COMMAND_H

#include <memory>


class CBCommand;
typedef std::shared_ptr<CBCommand> CBCommandPtr;
class CBCommand {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

#endif //CODEBASE_COMMAND_H