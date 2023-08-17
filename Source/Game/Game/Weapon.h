#pragma once
#include "Framework/Actor.h"

namespace bunny {
	class Weapon : public Actor {
	public:
		/*
		~Weapon() = default;
		Weapon(float speed, const bunny::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }
		{
			lifespan = 2.0f;
		}
		*/

		bool Initialize() override;
		void Update(float dt) override;
		void onCollision(Actor* actor);
		void Read(const json_t& value);
	private:
		float speed = 0;
	};
}