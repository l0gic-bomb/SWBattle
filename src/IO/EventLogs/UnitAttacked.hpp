#include <cstdint>
#include <string>
#include "Event.hpp"

namespace sw::io
{
    struct UnitAttacked : public Event<UnitAttacked> {
        UnitAttacked(uint32_t attackId, uint32_t targetId, uint32_t damage, uint32_t targetHp)
            : attackerUnitId(attackId), targetUnitId(targetId), damage(damage), targetHp(targetHp) {}

        constexpr static const char* Name = "UNIT_ATTACKED";

		uint32_t attackerUnitId {};
		uint32_t targetUnitId {};
		uint32_t damage {};
		uint32_t targetHp {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("attackerUnitId", attackerUnitId);
			visitor.visit("targetUnitId", targetUnitId);
			visitor.visit("damage", damage);
			visitor.visit("targetHp", targetHp);
		}
	};
}