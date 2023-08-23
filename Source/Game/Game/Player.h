#pragma once
#include "Framework/Actor.h"
#include "Weapon.h"
#include "Framework/Components/PhysicsComponent.h"

namespace bunny {
	class Player : public Actor {
	public:
		CLASS_DECLARATION(Player)

		/*Player() = default;
		Player(float speed, float turnRate, const Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{}*/

		bool Initialize() override;
		void Update(float dt) override;
		void onCollision(Actor* actor) override;

		float m_health = 3;
	private:
		float m_speed = 0;
		float m_turnRate = 0;
		int m_toggle = 1;

		PhysicsComponent* m_physics = nullptr;
	};
}