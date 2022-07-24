#include "Scenes.h"

#include "CSceneNodeAnimatorFishing.h"

namespace irr {
	Play::Play() : statusLabel(0), box(0) {
		
	}

	Play::~Play() {
		delete device->getEventReceiver();
		env->clear();
	}

	void Play::init() {
		IEventReceiver* queue = 0;

		for (s32 x4y = 0; x4y < 16; x4y++) {
			Filled[x4y] = false;
		}
		for (s32 x = 0; x < 4; x++) {
			for (s32 y = 0; y < 4; y++) {
				for (s32 z = 0; z < 4; z++) {
					Block* block = &(Blocks[x][y][z]);
					block->State = BlockState::Empty;
					if (block->Stone) {
						block->Stone->addAnimator(new scene::CSceneNodeAnimatorFishing(500, 5));
					}
					block->Stone = 0;
				}
			}
		}

		gui::IGUIElement* root = env->getRootGUIElement();

		statusLabel = env->addStaticText(L"", core::recti(0, 0, Resolution.Width, 50), true, false, root, GUI_IDs::StatusLabel, true);
		statusLabel->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);

		/*gui::IGUIButton* backButton = */env->addButton(core::recti(0, Resolution.Height - 50, 50, Resolution.Height), root, GUI_IDs::BackButton, L"←", L"スタートメニューに戻ります。");

		queue = (IEventReceiver*)(new utils::MainEventReceiver(device, [=](const SEvent& event) {
			switch (event.EventType) {
			case EET_GUI_EVENT:
				switch (event.GUIEvent.Caller->getID()) {
				case GUI_IDs::BackButton:
					if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED) {
						box = env->addMessageBox(L"確認", L"スタートメニューに戻ります。", true, gui::EMBF_OK | gui::EMBF_CANCEL, root, GUI_IDs::BackMessage);
						box->setDraggable(false);

					}
					break;

				case GUI_IDs::BackMessage:
					switch (event.GUIEvent.EventType) {
					case gui::EGET_MESSAGEBOX_OK:
						changeScene((IScene*)new StartMenu());
						break;

					case gui::EGET_MESSAGEBOX_CANCEL:
						box->remove();
						break;
					}
				}
				break;

			case EET_KEY_INPUT_EVENT:
				switch (event.KeyInput.Key) {
				case EKEY_CODE::KEY_ESCAPE:
					if (!event.KeyInput.PressedDown) {

					}
					break;
				}

			default:
				break;
			}

			return onEvent(event);
			}));

		if (queue) {
			device->setEventReceiver(queue);
		}
	}

	void Play::update(f32 delta) {

	}

	void Play::draw() {

	}
}