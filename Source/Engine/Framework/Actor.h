#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
#include "Components/Component.h"

namespace bunny {
	class Actor {
	public:
		Actor() = default;
		Actor(const bunny::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(bunny::Renderer& r);

		void AddComponent(std::unique_ptr<Component> c);

		template<typename T>
		T* GetComponent();

		float getRadius() { return 30.0f; }
		virtual void onCollision(Actor* other) {}

		friend class Scene;
		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;

		bunny::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;
	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
	};

	template<typename T>
	inline T* Actor::GetComponent() {
		for (auto& component : m_components) {
			T* result = dynamic_cast<T*>(component.get());

			if (result) {
				return result;
			}
		}

		return nullptr;
	}
}