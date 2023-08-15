#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	virtual const char* getClassName() { return #classname; } \
	bool Read(const rapidjson::Value& value); \
	class Register { \
	public: \
		Register() { \
			Factory::Instance().Register<classname>(#classname); \
		} \
	};

#define CLASS_DEFINITION(classname) \
	classname::Register register_class;

namespace bunny {
	class Object {
	public:
		//or Obejct() {}
		Object() = default;
		Object(const std::string& name) : name{ name } {}
		~Object() { Destroy(); }

		CLASS_DECLARATION(Object)

		virtual bool Initialize() { return true; }
		virtual void Destroy() {}
	protected:
		std::string name;

	};
}