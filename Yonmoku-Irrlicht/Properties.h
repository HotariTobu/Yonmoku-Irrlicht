#pragma once

#ifndef __PROPERTIES_H_INCLUDED__
#define __PROPERTIES_H_INCLUDED__

#include "MyHead.h"

#include "IScene.h"
#include "GUIAnimationCenter.h"

extern IrrlichtDevice* device;

extern gui::ICursorControl* csr;
extern io::IFileSystem* fsy;
extern gui::IGUIEnvironment* env;
extern ILogger* lgr;
extern IOSOperator* opr;
extern IRandomizer* rdm;
extern scene::ISceneManager* mgr;
extern ITimer* tim;
extern video::IVideoDriver* drv;
extern scene::IMeshManipulator* mnp;
extern scene::ISceneCollisionManager* colmgr;
extern core::dimension2di Resolution;
extern IScene* sce;
extern gui::GUIAnimationCenter* gac;

extern scene::IAnimatedMeshSceneNode* StandNode;
enum class BlockState {
	Empty,
	Black,
	White,
};
struct Block {
	BlockState State = BlockState::Empty;
	scene::ISceneNode* Stone = 0;
};
extern Block Blocks[4][4][4];
extern bool Filled[16];
extern scene::IAnimatedMesh* StoneMesh;
extern scene::SMesh* StoneMeshST;

/*enum class Scenes {
	StartMenu,
	Loading,
	Play,
};*/

enum GUI_IDs {
	//StartMenu
	SinglePlayButton,
	_PVCButton,
	_CVCButton,
	MultiPlayButton,
	_AlternatingPlayButton,
	_BluetoothPlayButton,
	_NetworkPlayButton,
	ExitButton,
	_CancelButton,

	//Play
	StatusLabel,
	BackButton,

	//MessageBox
	ExitMessage,
	BackMessage,
};

enum SceneNode_IDs {
	Camera = 1000,
	Stand,
	Stone = 0b1000000,
};

extern IScene* NextScene;
extern bool ChangeScene;
void changeScene(IScene* next);

#endif // !__PROPERTIES_H_INCLUDED__
