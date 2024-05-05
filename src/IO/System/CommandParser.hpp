#pragma once

#include <string>
#include <sstream>
#include <functional>
#include <memory>
#include <queue>

#include "../Commands/Command.hpp"
#include "details/CommandVisitor.hpp"

namespace sw::io
{
	class CommandParser {
	private:
		std::unordered_map<std::string, std::function<std::unique_ptr<Command>(std::istream&)>> _parserCommands;

	public:
		template <class TCommandData>
		CommandParser& add(std::function<void(TCommandData)> handler)
		{
			std::string commandName = TCommandData::Name;
			auto [it, inserted] = _parserCommands.emplace(
				commandName, [handler = std::move(handler)](std::istream& stream)
				{
                    std::unique_ptr<TCommandData> data = std::make_unique<TCommandData>();
					CommandVisitor visitor(stream);
					data->visit(visitor);
					handler(*data);
                    return std::move(data);
				});
			if (!inserted) {
				throw std::runtime_error("Command already exists: " + commandName);
			}

			return *this;
		}

		void parse(std::istream& stream, std::queue<std::unique_ptr<Command>>& commands);
	};
}