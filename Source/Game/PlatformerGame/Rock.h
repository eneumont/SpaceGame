#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace bunny {
	class Rock : public Actor {
	public:
		CLASS_DECLARATION(Rock)

		bool Initialize() override;
		void Update(float dt) override;
		void onCollisionEnter(Actor* actor);
	private:
		float speed = 0;
		PhysicsComponent* m_physics = nullptr;
	};
}