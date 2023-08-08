#pragma once
#include <cmath>
#include <sstream>

namespace bunny {
	class Vector3 {
	public:
		float x, y, z;
	public:
		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y }, z{ (float)z } {}

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s, z - s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s, z / s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s, z * s); }

		Vector3& operator += (const Vector3& v) { Vector3(x += v.x, y += v.y, z += v.z); return *this; }
		Vector3& operator -= (const Vector3& v) { Vector3(x -= v.x, y -= v.y, z -= v.z); return *this; }
		Vector3& operator /= (const Vector3& v) { Vector3(x /= v.x, y /= v.y, z /= v.z); return *this; }
		Vector3& operator *= (const Vector3& v) { Vector3(x *= v.x, y *= v.y, z *= v.z); return *this; }

		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }
		float Length() const { return std::sqrt(LengthSqr()); }

		//maybe add inline to the distance and distancesqr
		inline float DistanceSqr(const Vector3& v) const { return (v - *this).LengthSqr(); }
		inline float Distance(const Vector3& v) const { return (v - *this).Length(); }

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		/*float Angle() const { return std::atan2f(y, x); }
		Vector3 Rotate(float radians) const;

		static float SignedAngle(const Vector3& v1, const Vector3& v2);
		static float Angle(const Vector3& v1, const Vector3& v2);*/
		static float Dot(const Vector3& v1, const Vector3& v2);
	};

	/*inline Vector3 Vector3::Rotate(float radians) const {
		float _x = x * std::cos(radians) - y * std::sin(radians);
		float _y = x * std::sin(radians) + y * std::cos(radians);

		return { _x, _y };
	}*/

	// get the unsigned angle in radians between the normalized v1 and normalized v2
	/*inline float Vector3::Angle(const Vector3& v1, const Vector3& v2) {
		return std::acos(Dot(v1, v2));
	}*/

	// get the signed counterclockwise angle in radians between v1 and v2
	/*inline float Vector3::SignedAngle(const Vector3& v1, const Vector3& v2) {
		float y = v1.x * v2.y - v1.y * v2.x;
		float x = v1.x * v2.x + v1.y * v2.y;

		return std::atan2(y, x);
	}*/

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vector3::Dot(const Vector3& v1, const Vector3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	inline std::istream& operator >> (std::istream& stream, Vector3& v) {
		std::string line;
		std::getline(stream, line);

		// { ##, ## }
		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);

		std::string zs = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.z = std::stof(zs);

		return stream;
	}

	using vec3 = Vector3;
}