#pragma once
#include "Component.h"

namespace bunny {
	class CollisionComponent : public Component {
	public:
		virtual bool checkCollision(CollisionComponent* collision) { return true; }

		float m_radius = 0;
	};
}