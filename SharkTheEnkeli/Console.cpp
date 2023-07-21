#include "Console.h"
#include "Game.h"
#include "VersionCommand.h"
#include "HelpCommand.h"

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

bool Console::stringToCommand(std::string command)
{
    std::transform(command.begin(), command.end(), command.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if (!command.compare("help") || !command.compare("?")) {
        Command* cmd = new HelpCommand();
        return game->executeCommand(cmd);
    }
    if (!command.compare("version")) {
        Command* cmd = new VersionCommand(game->getVersion());
        return game->executeCommand(cmd);
    }
    return false;
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
            ImGui::TextColored(textColorPair.second, ": %s", textColorPair.first.c_str());
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
            if (!stringToCommand(callbackBuffer)) {
                std::string text = "Command: ";
                text += callbackBuffer;
                text += " not found";
                ImVec4 color(1.0f, 0.0f, 0.0f, 1.0f);
                history.emplace_back(text, color);
            }
            else {
                ImVec4 color(1.0f, 1.0f, 1.0f, 1.0f);
                history.emplace_back(callbackBuffer, color);
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
