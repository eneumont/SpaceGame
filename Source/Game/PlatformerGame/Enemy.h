#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace bunny {
	class Enemy : public Actor {
	public:
		CLASS_DECLARATION(Enemy)

			bool Initialize() override;
		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;
		void onCollisionExit(Actor* actor) override;
	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;

		PhysicsComponent* m_physics = nullptr;
	};
}