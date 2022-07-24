#include "CSceneNodeAnimatorFishing.h"

namespace irr {
	namespace scene {
		void CSceneNodeAnimatorFishing::begin(ISceneNode* node) {
			node->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
		}

		void CSceneNodeAnimatorFishing::animateNode(ISceneNode* node, u32 timeMs) {
			if (check(node, timeMs)) {
				core::vector3df pos = node->getPosition();
				pos.Y += modify(distance);
				node->setPosition(pos);

				if (node->getType() == scene::ESNT_ANIMATED_MESH) {
					node->getSceneManager()->getMeshManipulator()->setVertexColorAlpha(((IAnimatedMeshSceneNode*)node)->getMesh(), (u32)(255.0f * ((f32)(EndTimeMs - ElapsedTimeMs) / (f32)EndTimeMs)));
				}
			}
		}

		void CSceneNodeAnimatorFishing::end(ISceneNode* node) {
			node->getSceneManager()->addToDeletionQueue(node);
		}

		ISceneNodeAnimator* CSceneNodeAnimatorFishing::createClone(ISceneNode* node, ISceneManager* newManager) {
			CSceneNodeAnimatorFishing* clone = new CSceneNodeAnimatorFishing(EndTimeMs, distance);
			return clone;
		}
	}
}