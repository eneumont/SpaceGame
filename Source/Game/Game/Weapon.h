#pragma once
#include "Framework/Actor.h"

namespace bunny {
	class Weapon : public Actor {
	public:
		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float dt) override;
		void onCollision(Actor* actor);
		//void Read(const json_t& value);
	private:
		float speed = 0;
	};
}