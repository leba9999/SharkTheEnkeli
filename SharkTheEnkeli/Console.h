#pragma once
#include <string>
#include <vector>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <mutex>
#include "Commands/Command.h"
class Game;

class Console
{
private:
	std::vector<std::pair<std::string, ImVec4>> history;
	bool show = true;
	static Console* pinstance_;
	static std::mutex mutex_;
	char callbackBuffer[254] = "";
	int count;
	char str1[128] = "";
	Game* game;
	std::vector<std::string> splitString(const std::string& input, char delimiter);
protected:
	Console();
public:
	Console(Console& other) = delete;
	void operator=(const Console&) = delete;
	static Console* getInstance();

	void setGame(Game* game);
	void setVisiblity(bool visibility);
	void print(std::string text);
	void print(std::string text, ImVec4 color);
	Command* stringToCommand(std::string command);
	bool executeCommand(Command* command);
	void update();
	bool clear();
};
