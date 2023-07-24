#pragma once
#include <string>
class Command
{
public:
	virtual ~Command() = default;
	virtual bool execute() = 0;
	virtual void setShortDescription(std::string text) {
		this->shortDescription = text;
	};
	virtual std::string getShortDescription() {
		return shortDescription;
	};
	virtual void setDescription(std::string text) {
		this->description = text;
	};
	virtual std::string getDescription() {
		return description;
	}
protected:
	Command() = default;
private:
	std::string shortDescription;
	std::string description;
};

