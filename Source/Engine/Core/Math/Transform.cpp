#include "Transform.h"

namespace bunny {
	void bunny::Transform::Read(const json_t& value) {
		READ_DATA(value, position);
		READ_DATA(value, rotation);
		READ_DATA(value, scale);
	}
}
