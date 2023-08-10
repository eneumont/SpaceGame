#pragma once
#include "Vector2.h"

namespace bunny {
	class Matrix3x3 {
	public:
		vec3 rows[2];
		// [row][column]
		// rows[0] = vec3{ 0, 0, 0 }
		// rows[1] = vec3{ 0, 0, 0 }
		// rows[2] = vec3{ 0, 0, 0}

		Matrix3x3() = default;
		Matrix3x3(const vec3& row1, const vec3& row2, const vec3& row3) {
			rows[0] = row1;
			rows[1] = row2;
		}

		vec3  operator [] (size_t index) const { return rows[index]; }
		vec3& operator [] (size_t index) { return rows[index]; }

		vec3 operator * (const vec3& v);
		Matrix3x3 operator * (const Matrix3x3& mx);

		static Matrix3x3 CreateScale(const vec2& scale);
		static Matrix3x3 CreateScale(float scale);
		static Matrix3x3 CreateRotation(float radians);

		static Matrix3x3 CreateIdentity();
	};

	inline Matrix3x3 Matrix3x3::CreateIdentity() {
		return {
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		};
	}

	inline Matrix3x3 Matrix3x3::CreateScale(const vec2& scale) {
		Matrix3x3 mx = CreateIdentity();
		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(float scale) {
		Matrix3x3 mx = CreateIdentity();
		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateRotation(float radians) {
		float c = cos(radians);
		float s = sin(radians);

		Matrix3x3 mx = CreateIdentity();
		mx[0][0] = c; mx[0][1] = -s;
		mx[1][0] = s; mx[1][1] = c;

		return mx;
	}

	inline vec3 Matrix3x3::operator*(const vec3& v) {
		//| a b |   | x |
		//| c d | * | y |

		vec3 vv;
		vv.x = rows[0][0] * v.x + rows[0][1] * v.y;
		vv.y = rows[1][0] * v.x + rows[1][1] * v.y;

		return vv;
	}

	inline Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mx) {
		// | a b |   | e f |
		// | c d | * | g h |

		Matrix3x3 m;
		m[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		m[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		m[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		m[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return m;
	}

	using mat3 = Matrix3x3;
}