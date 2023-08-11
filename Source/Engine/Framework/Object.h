#pragma once
#include <string>

namespace bunny {
	class Object {
	public:
		//or Obejct() {}
		Object() = default;
		Object(const std::string& name) : m_name{ name } {}
		~Object() { Destroy(); }

		virtual bool Initialize() { return true; }
		virtual void Destroy() {}
	protected:
		std::string m_name;

	};
}