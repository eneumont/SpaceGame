#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace bunny {
	class ModelRenderComponent : public RenderComponent {
	public:
		void Update(float dt) override;
		void Draw(class Renderer& r) override;

		res_t<Model> m_model;
	};
}