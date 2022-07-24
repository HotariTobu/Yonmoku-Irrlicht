#pragma once

#ifndef __PLAY_H_INCLUDED__
#define __PLAY_H_INCLUDED__

#include "MyHead.h"

#include "MainEventReceiver.h"

#include "StartMenu.h"
#include "CSceneNodeAnimatorFalling.h"
#include "CSceneNodeAnimatorFishing.h"

namespace irr {
	enum Situations {
		Playing,
		Win,
		Lose,
		Tie,
	};

	class Play : public IScene {
	public:
		Play();
		virtual ~Play();

		virtual void update(f32 delta) override;
		virtual void draw() override;

	protected:
		virtual bool onEvent(const SEvent& event) = 0;

		gui::IGUIStaticText* statusLabel;

	private:
		//gui::IGUIWindow* box;
	};
}

#endif // !__PLAY_H_INCLUDED__
