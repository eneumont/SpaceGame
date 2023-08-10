#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace bunny {
	void ModelRenderComponent::Update(float dt) {
	
	}

	void ModelRenderComponent::Draw(Renderer& r) {
		m_model->Draw(r, m_owner->m_transform);
	}
}