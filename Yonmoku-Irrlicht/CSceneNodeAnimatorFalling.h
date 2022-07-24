#pragma once

#ifndef __C_SCENE_NODE_ANIMATOR_FALLING_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_FALLING_H_INCLUDED__

#include "ISceneNodeAnimatorEnd.h"

namespace irr {
	namespace scene {
		class CSceneNodeAnimatorFalling : public ISceneNodeAnimatorEnd {
		public:
			CSceneNodeAnimatorFalling(f32 distance, f32 accelerator = 9.8f) : ISceneNodeAnimatorEnd(5000), distance(distance), accelerator(accelerator / 1000000.0f) {}
			virtual void begin(ISceneNode* node) override;
			virtual void animateNode(ISceneNode* node, u32 timeMs) override;
			virtual void end(ISceneNode* node) override;
			virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager = 0) override;

		private:
			f32 distance, accelerator;
		};
	}
}


#endif // !__C_SCENE_NODE_ANIMATOR_FALLING_H_INCLUDED__
