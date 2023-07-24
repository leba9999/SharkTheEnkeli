#include "Console.h"
#include "Game.h"
#include "Commands/VersionCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/UnknownCommand.h"
#include "Commands/ClearCommand.h"
#include "Commands/CloseGameCommand.h"
#include "Commands/FullscreenCommand.h"

Console::Console()
{

}

Console* Console::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Console();
    }
    return pinstance_;
}

void Console::setGame(Game* game)
{
    this->game = game;
}

void Console::setVisiblity(bool visibility)
{
    show = visibility;
}

void Console::print(std::string text)
{
    if (history.size() > 999)
    {
        history.erase(history.begin());
    }
    ImVec4 color(1.0f, 1.0f, 1.0f, 1.0f);
    history.emplace_back(text, color);
}
void Console::print(std::string text, ImVec4 color)
{
    if (history.size() > 999)
    {
        history.erase(history.begin());
    }
    history.emplace_back(text, color);
}

std::vector<std::string> Console::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    size_t startPos = 0;
    size_t foundPos = input.find(delimiter);

    while (foundPos != std::string::npos) {
        result.push_back(input.substr(startPos, foundPos - startPos));
        startPos = foundPos + 1;
        foundPos = input.find(delimiter, startPos);
    }

    if (startPos < input.length())
        result.push_back(input.substr(startPos));

    return result;
}

Command* Console::stringToCommand(std::string argument)
{
    std::transform(argument.begin(), argument.end(), argument.begin(),
        [](unsigned char c) { return std::tolower(c); });

    std::vector<std::string> arguments = splitString(argument, '=');
    if (arguments.size() <= 1) {
        arguments = splitString(argument, ' ');
    }

    if (arguments.size() <= 1) {
        if (!argument.compare("help") || !argument.compare("?"))
            return new HelpCommand();
        if (!argument.compare("version"))
            return new VersionCommand(game->getVersion());
        if (!argument.compare("clear"))
            return new ClearCommand();
        if (!argument.compare("close") || !argument.compare("shutdown"))
            return new CloseGameCommand(game);
    }
    else if (arguments.size() == 2) {
        if (!arguments[0].compare("fullscreen") && (!arguments[arguments.size() - 1].compare("false") || !arguments[arguments.size() - 1].compare("0")))
            return new FullscreenCommand(game, false);
        if (!arguments[0].compare("fullscreen") && (!arguments[arguments.size() - 1].compare("true") || !arguments[arguments.size() - 1].compare("1")))
            return new FullscreenCommand(game, true);

    }

    return new UnknownCommand();
}

bool Console::executeCommand(Command* command)
{
    return command->execute();
}

void Console::update()
{
    if (show) {
        ImGui::Begin("Console", &show, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Clear"))
                {
                    this->clear();
                }
                if (ImGui::MenuItem("Close"))
                {
                    print("Close");
                    show = false;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
        for (const auto& textColorPair : history)
            ImGui::TextColored(textColorPair.second, "%s", textColorPair.first.c_str());
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
        ImGui::EndChild();
        ImGui::Separator();         
        if (ImGui::InputText("Input", callbackBuffer, sizeof(callbackBuffer),
            ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_EnterReturnsTrue,
            [](ImGuiInputTextCallbackData* data) -> int
            {
                if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
                {
                    std::cout << "TAB?" << std::endl;
                    data->InsertChars(data->CursorPos, "test");
                    // Handle tab-completion or other custom input handling here if needed
                    return 1;
                }
                return 0; // Return value of 0 means we have not handled the event
            }))
        {
            // Process the entered text here
            // The entered text will be available in the 'callbackBuffer' variable.
            Command* cmd = stringToCommand(callbackBuffer);
            UnknownCommand* helpCmd = dynamic_cast<UnknownCommand*>(cmd);
            std::string inputCommand = "> ";
            inputCommand += callbackBuffer;
            print(inputCommand);
            if (helpCmd) {
                std::string text = "Command: ";
                text += callbackBuffer;
                text += " not found";
                print(text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
            }
            else {
                if (!game->executeCommand(cmd)) {
                    std::string text = "Failed to execute: ";
                    text += callbackBuffer;
                    print(text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                }
            }
            callbackBuffer[0] = '\0';
        }

        ImGui::End();
    }
}



bool Console::clear()
{
    history.clear();
	return false;
}
