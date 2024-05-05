#include <cstdint>
#include <string>

#include "Event.hpp"

namespace sw::io
{
	struct UnitDied : public Event<UnitDied> {
        UnitDied(uint32_t id)
            : unitId(id) {}

        constexpr static const char* Name = "UNIT_DIED";

		uint32_t unitId {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
		}
	};
}