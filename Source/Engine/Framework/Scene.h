#pragma once
#include <list>
#include "Actor.h"

namespace bunny {
	class Renderer; //can use this instead of headers if just referencing
				    //if wanting to do Renderer.draw() would need to include the header

	class Scene {
	public:
		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& r);
		void Add(std::unique_ptr<Actor> a);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		template<typename T>
		T* GetActor();
		template<typename T = Actor>
		T* GetActorByName(const std::string name);

		//friend class Actor;
	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetActor() {
		for (auto& actor : m_actors) {
			T* result = dynamic_cast<T*>(actor.get());

			if (result) {
				return result;
			}
		}

		return nullptr;
	}
	template<typename T>
	inline T* Scene::GetActorByName(const std::string name) {
		for (auto& actor : m_actors) {
			if (actor->name == name) {
				T* result = dynamic_cast<T*>(actor.get());

				if (result) {
					return result;
				}
			}
		}

		return nullptr;
	}
}