#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace bunny {
	class ModelRenderComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(ModelRenderComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& r) override;
		virtual float getRadius() override { return m_model->getRadius(); }

		std::string modelName;
		res_t<Model> m_model;
	};
}