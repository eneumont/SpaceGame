#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace bunny {
	CLASS_DEFINITION(ModelRenderComponent)

	void ModelRenderComponent::Update(float dt) {
	
	}

	void ModelRenderComponent::Draw(Renderer& r) {
		m_model->Draw(r, m_owner->m_transform);
	}
}