#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	virtual const char* getClassName() { return #classname; } \
	virtual void Read(const json_t& value); \
	virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); } \
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

		std::string name;
		bool active = true;
	protected:
		
	};
}