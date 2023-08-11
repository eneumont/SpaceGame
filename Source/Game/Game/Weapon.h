#pragma once
#include "Framework/Actor.h"

class Weapon : public bunny::Actor {
public:
	~Weapon() = default;
	Weapon(float speed, const bunny::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	bool Initialize() override;
	void Update(float dt) override;
	void onCollision(Actor* actor) override;
private:
	float m_speed = 0;
};