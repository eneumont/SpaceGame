#pragma once
#include "Vector2.h"
#include "Matrix2x2.h"

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

		mat2 GetMatrix() const {
			mat2 ms = mat2::CreateScale(scale);
			mat2 mr = mat2::CreateRotation(rotation);
			
			return ms * mr;
		}
	};
}