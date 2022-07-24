#include "Scenes.h"

namespace irr {
	StartMenu::StartMenu() {
		
	}

	StartMenu::~StartMenu() {
		delete device->getEventReceiver();
		env->clear();
	}

	void StartMenu::init() {
		IEventReceiver* queue = 0;

		//define
		const s32 panelWidth = 500;
		const s32 margin = 10;
		const s32 buttonHeight = 70;
		const core::dimension2du buttonSize(panelWidth - margin * 2, buttonHeight);

		s32 index = 0;

		//main
		const s32 panel1ButtonCount = 3;
		const core::dimension2di panel1Size(panelWidth, buttonHeight * panel1ButtonCount + margin * (panel1ButtonCount + 1));
		gui::CGUIPanel* panel1 = new gui::CGUIPanel(env, core::recti(core::vector2di((Resolution.Width - panel1Size.Width) / 2, (Resolution.Height - panel1Size.Height) / 2), panel1Size));
		panel1->setVisible(true);

		gui::IGUIButton* singlePlayButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel1, GUI_IDs::SinglePlayButton, L"１人プレイ");
		gui::IGUIButton* multiPlayButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel1, GUI_IDs::MultiPlayButton, L"２人プレイ");
		gui::IGUIButton* exitButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel1, GUI_IDs::ExitButton, L"終了");

		index = 0;

		//sub1
		const s32 panel2ButtonCount = 3;
		const core::dimension2di panel2Size(panelWidth, buttonHeight * panel2ButtonCount + margin * (panel2ButtonCount + 1));
		gui::CGUIPanel* panel2 = new gui::CGUIPanel(env, core::recti(core::vector2di((Resolution.Width - panel2Size.Width) / 2, (Resolution.Height - panel2Size.Height) / 2), panel2Size));

		gui::IGUIButton* pvcButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel2, GUI_IDs::_PVCButton, L"Player vs Computer");
		gui::IGUIButton* cvcButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel2, GUI_IDs::_CVCButton, L"Computer vs Computer");
		gui::IGUIButton* cancelButton1 = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel2, GUI_IDs::_CancelButton, L"キャンセル");

		index = 0;

		//sub2
		const s32 panel3ButtonCount = 4;
		const core::dimension2di panel3Size(panelWidth, buttonHeight * panel3ButtonCount + margin * (panel3ButtonCount + 1));
		gui::CGUIPanel* panel3 = new gui::CGUIPanel(env, core::recti(core::vector2di((Resolution.Width - panel3Size.Width) / 2, (Resolution.Height - panel3Size.Height) / 2), panel3Size));

		gui::IGUIButton* alternatingPlayButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel3, GUI_IDs::_AlternatingPlayButton, L"交互にプレイ");
		gui::IGUIButton* bluetoothPlayButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel3, GUI_IDs::_BluetoothPlayButton, L"Bluetooth通信プレイ");
		gui::IGUIButton* networkPlayButton = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel3, GUI_IDs::_NetworkPlayButton, L"インターネット通信プレイ");
		gui::IGUIButton* cancelButton2 = env->addButton(core::recti(core::vector2di(margin, buttonHeight * index++ + margin * index), buttonSize), panel3, GUI_IDs::_CancelButton, L"キャンセル");

		queue = (IEventReceiver*)(new utils::MainEventReceiver(device, [=](const SEvent& event) {
			switch (event.EventType) {
			case EET_GUI_EVENT:
				if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED) {
					switch (event.GUIEvent.Caller->getID()) {
					case GUI_IDs::SinglePlayButton:
						panel1->setVisible(false);
						panel2->setVisible(true);
						break;

					case GUI_IDs::MultiPlayButton:
						panel1->setVisible(false);
						panel3->setVisible(true);
						break;

					case GUI_IDs::ExitButton:
						device->closeDevice();
						break;

					case GUI_IDs::_PVCButton:
						panel2->setVisible(false);
						break;

					case GUI_IDs::_CVCButton:
						panel2->setVisible(false);
						break;

					case GUI_IDs::_AlternatingPlayButton:
						panel3->setVisible(false);
						changeScene((IScene*)new AlternatingPlay());
						break;

					case GUI_IDs::_BluetoothPlayButton:
						panel3->setVisible(false);
						break;

					case GUI_IDs::_NetworkPlayButton:
						panel3->setVisible(false);
						break;

					case GUI_IDs::_CancelButton:
						panel1->setVisible(true);
						panel2->setVisible(false);
						panel3->setVisible(false);
						break;
					}
				}
				break;

			default:
				break;
			}
			return false;
			}));

		if (queue) {
			device->setEventReceiver(queue);
		}
	}

	void StartMenu::update(f32 delta) {

	}
	
	void StartMenu::draw() {

	}
}