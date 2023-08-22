#pragma once
#include "string"
#include <variant>

namespace bunny {
	class Event {
	public:
		using id_t = std::string;
		using data_t = std::variant<int, bool, float, std::string>;
		
		Event() = default;
		Event(const id_t& id, data_t data) : 
			id{ id }, 
			data{ data } 
		{}

		id_t id;
		data_t data;
	};
}