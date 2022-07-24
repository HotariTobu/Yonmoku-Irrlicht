#pragma once

#ifndef __ALTERNATING_PLAY_H_INCLUDED__
#define __ALTERNATING_PLAY_H_INCLUDED__

#include "Play.h"

namespace irr {
	class AlternatingPlay : public Play {
	public:
		AlternatingPlay();
		~AlternatingPlay();

		virtual void update(f32 delta) override;
		virtual void draw() override;
		virtual bool onEvent(const SEvent& event) override;

	private:
		void turnYellow(s32 x, s32 y, s32 z);

		video::SColor black, white, yellow;

		bool player1;
		bool hit;
		bool complete;
		core::vector2di point;
		video::SMaterial shadowMaterial;
	};
}

#endif // !__ALTERNATING_PLAY_H_INCLUDED__
