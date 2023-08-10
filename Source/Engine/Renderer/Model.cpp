#include "Model.h"
#include "Renderer.h"
#include <sstream>

namespace bunny {
	bool Model::Load(const std::string& filename) {
		std::string buffer;
		bunny::readFile(filename, buffer);

		std::istringstream stream(buffer);

		stream >> m_color;

		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);
		for (int i = 0; i < numPoints; i++) {
			vec2 point;
			stream >> point;
			m_points.push_back(point);
		}

		getRadius();

		return true;
	}

	void Model::Draw(Renderer& r, const vec2& p, float rotation, float scale) {
		if (m_points.empty()) {
			return;
		}

		r.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + p;
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + p;

			r.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Model::Draw(Renderer& r, const Transform& transform) {
		//Draw(r, transform.position, transform.rotation, transform.scale);

		if (m_points.empty()) {
			return;
		}

		mat3 mx = transform.GetMatrix();

		r.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = mx * m_points[i];
			vec2 p2 = mx * m_points[i + 1];

			r.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	float Model::getRadius() {
		if (m_radius != 0) {
			return m_radius;
		}

		for (auto point : m_points) {
			float length = point.Length();
			m_radius = Max(m_radius, length);
		}

		return m_radius;
	}

	bool Model::Create(std::string filename, ...) {
		return Load(filename);
	}
}