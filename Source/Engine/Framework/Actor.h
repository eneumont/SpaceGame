#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
#include "Components/Component.h"
#include "Object.h"

namespace bunny {
	class Actor : public Object {
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const bunny::Transform& transform) :
			transform{ transform }
		{}

		virtual bool Initialize() override;
		virtual void Destroy() override;

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

		bunny::Transform transform;
		std::string tag;
		float lifespan = -1.0f;
	protected:
		std::vector<std::unique_ptr<Component>> components;
		bool destroyed = false;
	};

	template<typename T>
	inline T* Actor::GetComponent() {
		for (auto& component : components) {
			T* result = dynamic_cast<T*>(component.get());

			if (result) {
				return result;
			}
		}

		return nullptr;
	}
}