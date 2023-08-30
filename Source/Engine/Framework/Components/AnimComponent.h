#pragma once
#include "SpriteComponent.h"

namespace bunny {
	class AnimComponent : public SpriteComponent {
	public:
		struct AnimSequence {
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};

		CLASS_DECLARATION(AnimComponent)

		bool Initialize() override;
		void Update(float dt) override;
		//virtual float getRadius() { return m_texture->GetSize().Length() * 0.5f; }

		int frames = 0;
		float frameTimer = 0;

		void setSequence(const std::string& name, bool update = true);
		void updateSource();
	private:
		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> m_sequences;
		AnimSequence* m_sequence = nullptr;
	};
}