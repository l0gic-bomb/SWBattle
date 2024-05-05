#include <cstdint>
#include "Event.hpp"

namespace sw::io
{
    struct MarchStarted : public Event<MarchStarted> {
        MarchStarted(uint32_t id, const unsigned int x, const unsigned int y, uint32_t targetX, uint32_t targetY)
            : unitId(id), x(x), y(y), targetX(targetX), targetY(targetY) {}

        constexpr static const char* Name = "MARCH_STARTED";

		uint32_t unitId {};
		uint32_t x {};
		uint32_t y {};
		uint32_t targetX {};
		uint32_t targetY {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	};
}