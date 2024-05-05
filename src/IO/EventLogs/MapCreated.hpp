#include <cstdint>
#include "Event.hpp"

namespace sw::io
{
	struct MapCreated : public Event<MapCreated> {
        MapCreated(uint32_t w, uint32_t h)
            : width(w), height(h) {}

        constexpr static const char* Name = "MAP_CREATED";

		uint32_t width {};
		uint32_t height {};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}
	};
}