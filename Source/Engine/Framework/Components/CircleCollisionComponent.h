#pragma once
#include "CollisionComponent.h"

namespace bunny {
	class CircleCollisionComponent : public CollisionComponent {
	public:
		virtual void Update(float dt) override;
		virtual bool checkCollision(CollisionComponent* collision) override;
	};
}