#pragma once
#include "Framework/Actor.h"

namespace bunny {
	class Weapon : public Actor {
	public:
		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float dt) override;
		void onCollision(Actor* actor);
	private:
		float speed = 0;
	};
}