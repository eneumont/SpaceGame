#include "AnimComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Resource/ResourceManager.h"

namespace bunny {
	CLASS_DEFINITION(AnimComponent)

	bool AnimComponent::Initialize() {
		SpriteComponent::Initialize();
		setSequence(defaultSequenceName);
		if (source.w == 0 && source.h == 0) updateSource();
		return true;
	}

	void AnimComponent::Update(float dt) {
		frameTimer -= dt;
		if (frameTimer <= 0) {
			frameTimer = 1.0f / m_sequence->fps;
			frames++;
			if (frames > m_sequence->endFrame) {
				frames = (m_sequence->loop) ? m_sequence->startFrame : m_sequence->endFrame;
			}
		}

		updateSource();
	}

	void AnimComponent::Read(const json_t& value) {
		SpriteComponent::Read(value);

		// read in animation sequences
		if (HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray()) {
			for (auto& sequenceValue : GET_DATA(value, sequences).GetArray()) {
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, g_r);

				m_sequences[sequence.name] = sequence;
			}
		}

		if (!READ_DATA(value, defaultSequenceName)) {
			// if default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = m_sequences.begin()->first;
		}
	}

	void AnimComponent::setSequence(const std::string& name, bool update) {
		if (m_sequence && m_sequence->name == name) return;

		if (m_sequences.find(name) != m_sequences.end()) {
			m_sequence = &m_sequences[name];
			if (m_sequence->texture) m_texture = m_sequence->texture;
			frames = m_sequence->startFrame;
			frameTimer = 1.0f / m_sequence->fps;

			if (update) updateSource();
		}
	}

	void AnimComponent::updateSource() {
		vec2 cellsize = m_texture->GetSize() / vec2{ m_sequence->numColumns, m_sequence->numRows };
		int column = (frames - 1) % m_sequence->numColumns;
		int row = (frames - 1) / m_sequence->numColumns;
		source.x = (int)(column * cellsize.x);
		source.y = (int)(row * cellsize.y);
		source.w = (int)(cellsize.x);
		source.h = (int)(cellsize.y);
	}
}