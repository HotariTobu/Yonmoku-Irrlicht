#pragma once

#ifndef __C_SCENE_NODE_ANIMATOR_FISHING_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_FISHING_H_INCLUDED__

#include <ISceneManager.h>
#include <IMeshManipulator.h>
#include <ISceneNode.h>
#include <IAnimatedMeshSceneNode.h>

#include "ISceneNodeAnimatorEnd.h"

namespace irr {
	namespace scene {
		class CSceneNodeAnimatorFishing : public ISceneNodeAnimatorEnd {
		public:
			CSceneNodeAnimatorFishing(u32 endTimeMs, f32 distance) : ISceneNodeAnimatorEnd(endTimeMs), distance(distance) {}
			virtual void begin(ISceneNode* node) override;
			virtual void animateNode(ISceneNode* node, u32 timeMs) override;
			virtual void end(ISceneNode* node) override;
			virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager = 0) override;

		private:
			f32 distance;
		};
	}
}

#endif // !__C_SCENE_NODE_ANIMATOR_FISHING_H_INCLUDED__
