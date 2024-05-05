#include <cstdint>
#include "Event.hpp"

namespace sw::io
{
	struct MarchEnded : public Event<MarchEnded> {
        MarchEnded(uint32_t id, uint32_t x, uint32_t y)
            : unitId(id), x(x), y(y) {}

        constexpr static const char* Name = "MARCH_ENDED";

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