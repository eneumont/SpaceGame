#pragma once
#include "PhysicsComponent.h"
#include "Renderer/Renderer.h"

namespace bunny {
	class EnginePhysicsComponent : public PhysicsComponent {
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)

		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
	};
}