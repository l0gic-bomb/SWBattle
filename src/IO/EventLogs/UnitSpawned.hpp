#include <cstdint>
#include <string>
#include "Event.hpp"


namespace sw::io
{
	struct UnitSpawned : public Event<UnitSpawned> {
        UnitSpawned(uint32_t id, std::string type, uint32_t x, uint32_t y)
            : unitId(id), unitType(std::move(type)), x(x), y(y) {}

        constexpr static const char* Name = "UNIT_SPAWNED";

		uint32_t unitId {};
		std::string unitType {};
		uint32_t x {};
		uint32_t y {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("unitType", unitType);
			visitor.visit("x", x);
			visitor.visit("y", y);
		}
	};
}