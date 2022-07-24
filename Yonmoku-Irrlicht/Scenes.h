#pragma once

#ifndef __SCENES_H_INCLUDED__
#define __SCENES_H_INCLUDED__

#include "MyHead.h"

#include "Converter.h"
#include "MainEventReceiver.h"
#include "CGUIPanel.h"

namespace irr {
	class StartMenu : public IScene {
	public:
		StartMenu();
		~StartMenu();

		virtual void init() override;
		virtual void update(f32 delta) override;
		virtual void draw() override;

	private:

	};

	class Play : public IScene {
	public:
		Play();
		virtual ~Play();

		virtual void init() override;
		virtual void update(f32 delta) override;
		virtual void draw() override;

	protected:
		enum class Situations {
			Playing,
			Win,
			Lose,
			Tie,
		};

		virtual bool onEvent(const SEvent& event) = 0;

		gui::IGUIStaticText* statusLabel;

	private:
		gui::IGUIWindow* box;
	};

	class AlternatingPlay : public Play {
	public:
		AlternatingPlay();
		~AlternatingPlay();

		virtual void init() override;
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

#endif // !__SCENES_H_INCLUDED__
