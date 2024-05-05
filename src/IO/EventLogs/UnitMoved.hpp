#include <cstdint>
#include <string>
#include "Event.hpp"

namespace sw::io
{
    struct UnitMoved : public Event<UnitMoved> {
		constexpr static const char* Name = "UNIT_MOVED";

        UnitMoved() = default;

        UnitMoved(uint32_t id, uint32_t x, uint32_t y)
            : unitId(id), x(x), y(y) {}

		uint32_t unitId {};
		uint32_t x {};
		uint32_t y {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
		}
	};
}