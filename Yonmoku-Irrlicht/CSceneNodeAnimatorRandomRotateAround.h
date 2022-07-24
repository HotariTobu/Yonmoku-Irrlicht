#pragma once

#ifndef __C_SCENE_NODE_ANIMATOR_RANDOM_ROTATE_AROUND_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_RANDOM_ROTATE_AROUND_H_INCLUDED__

#include <ISceneNode.h>

namespace irr {
	namespace scene {
		class CSceneNodeAnimatorRandomRotateAround : public ISceneNodeAnimator {
		public:
			CSceneNodeAnimatorRandomRotateAround(core::vector3df* centerPos = new core::vector3df(), f32 rotateSpeed = 0.7f, f32 zoomSpeed = 0.3f) : centerPos(centerPos), rotateSpeed(rotateSpeed), zoomSpeed(zoomSpeed), Dragging(false), Zooming(false), invert(false), wheel(0), level(0), shift(false), ctrl(false) {}

			virtual void animateNode(ISceneNode* node, u32 timeMs) override;

			virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager = 0) override;

			virtual bool isEventReceiverEnabled() const override {
				return true;
			}

			virtual bool OnEvent(const SEvent& event) override;

			core::vector3df* centerPos;
			f32 rotateSpeed, zoomSpeed;

		private:
			bool Dragging;
			bool Zooming;
			bool invert;
			core::vector2di dif;
			f32 wheel, level;
			bool shift;
			bool ctrl;
		};
	}
}

#endif // !__C_SCENE_NODE_ANIMATOR_RANDOM_ROTATE_AROUND_H_INCLUDED__
