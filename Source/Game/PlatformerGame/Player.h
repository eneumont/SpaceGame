#pragma once
#include "Framework/Actor.h"

namespace bunny {
	class Player : public Actor {
	public:
		CLASS_DECLARATION(Player)

		bool Initialize() override;
		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;
		void onCollisionExit(Actor* actor) override;
	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;

		class PhysicsComponent* m_physics = nullptr;
		class AnimComponent* m_anim = nullptr;
	};
}
