#include "Object.h"

namespace bunny {
	void Object::Read(const json_t& value) {
		READ_DATA(value, name);
	}
}