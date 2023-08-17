#pragma once
#include "Vector2.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Core/Json.h"

namespace bunny {
	class Transform {
	public:
		vec2 position;
		float rotation = 0.0f;
		float scale = 1.0f;

		Transform() = default;
		Transform(const vec2& p, float r, float s = 1.0f) : 
			position{ p }, 
			rotation{ r }, 
			scale{ s } 
		{}

		mat3 GetMatrix() const {
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);
			
			return mt * ms * mr;
		}

		void Read(const json_t& value);
	};
}