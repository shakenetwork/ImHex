#pragma once

#include <any>
#include <functional>
#include <vector>
#include <map>

#include <helpers/content_registry.hpp>
#include <helpers/event.hpp>
#include <views/view.hpp>

#include <imgui.h>
#include <nlohmann/json.hpp>

namespace hex { class SharedData; }

namespace hex::plugin::internal {
    void initializePlugin(SharedData &sharedData);
}

namespace hex {

    namespace prv { class Provider; }

    class SharedData {
        SharedData() = default;
    public:
        SharedData(const SharedData&) = delete;
        SharedData(SharedData&&) = delete;

        friend class Window;

        template<typename T>
        static T& getVariable(std::string variableName) {
            return std::any_cast<T&>(SharedData::sharedVariables[variableName]);
        }

        template<typename T>
        static void setVariable(std::string variableName, T value) {
            SharedData::sharedVariables[variableName] = value;
        }

    public:
        static std::vector<EventHandler> eventHandlers;
        static std::vector<std::function<void()>> deferredCalls;
        static prv::Provider *currentProvider;
        static std::map<std::string, std::vector<ContentRegistry::Settings::Entry>> settingsEntries;
        static nlohmann::json settingsJson;
        static std::map<std::string, Events> customEvents;
        static u32 customEventsLastId;
        static std::vector<ContentRegistry::CommandPaletteCommands::Entry> commandPaletteCommands;
        static std::map<std::string, ContentRegistry::PatternLanguageFunctions::Function> patternLanguageFunctions;
        static std::vector<View*> views;
        static std::vector<std::function<void()>> toolsEntries;
        static std::vector<ContentRegistry::DataInspector::Entry> dataInspectorEntries;

        static int mainArgc;
        static char **mainArgv;

        static ImVec2 windowPos;
        static ImVec2 windowSize;

    private:
        static std::map<std::string, std::any> sharedVariables;
    };

}