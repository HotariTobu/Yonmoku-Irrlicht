#include "CSceneNodeAnimatorFalling.h"

namespace irr {
	namespace scene {
		void CSceneNodeAnimatorFalling::begin(ISceneNode* node) {

		}

		void CSceneNodeAnimatorFalling::animateNode(ISceneNode* node, u32 timeMs) {
			if (check(node, timeMs)) {
				core::vector3df pos = node->getPosition();

				f32 dis = (ElapsedTimeMs * ElapsedTimeMs - LastElapsedTimeMs * LastElapsedTimeMs) * accelerator / 2.0f;
				pos.Y -= dis;

				distance -= dis;
				if (distance < 0) {
					pos.Y -= distance;
					end(node);
				}

				node->setPosition(pos);
			}
		}

		void CSceneNodeAnimatorFalling::end(ISceneNode* node) {
			node->removeAnimator(this);
		}

		ISceneNodeAnimator* CSceneNodeAnimatorFalling::createClone(ISceneNode* node, ISceneManager* newManager) {
			CSceneNodeAnimatorFalling* clone = new CSceneNodeAnimatorFalling(distance);
			clone->accelerator = accelerator;
			return clone;
		}
	}
}