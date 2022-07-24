#pragma once

#ifndef __START_MENU_H_INCLUDED__
#define __START_MENU_H_INCLUDED__

#include "MyHead.h"

#include "Converter.h"
#include "MainEventReceiver.h"
#include "CGUIPanel.h"

namespace irr {
	class StartMenu : public IScene {
	public:
		StartMenu();
		~StartMenu();

		virtual void update(f32 delta) override;
		virtual void draw() override;

	private:

	};
}

#endif // !__START_MENU_H_INCLUDED__
