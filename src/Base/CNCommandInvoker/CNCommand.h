#ifndef CROSSNATIVE_COMMAND_H
#define CROSSNATIVE_COMMAND_H

#include <memory>


class CNCommand;
typedef std::shared_ptr<CNCommand> CNCommandPtr;
class CNCommand {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

#endif //CROSSNATIVE_COMMAND_H