#include "Properties.h"

IrrlichtDevice* device;

gui::ICursorControl* csr;
io::IFileSystem* fsy;
gui::IGUIEnvironment* env;
ILogger* lgr;
IOSOperator* opr;
IRandomizer* rdm;
scene::ISceneManager* mgr;
ITimer* tim;
video::IVideoDriver* drv;
scene::IMeshManipulator* mnp;
scene::ISceneCollisionManager* colmgr;
core::dimension2di Resolution;
IScene* sce;
gui::GUIAnimationCenter* gac;

scene::IAnimatedMeshSceneNode* StandNode;
Block Blocks[4][4][4];
bool Filled[16];
scene::IAnimatedMesh* StoneMesh;
scene::SMesh* StoneMeshST;

IScene* NextScene;
bool ChangeScene;
void changeScene(IScene* next) {
	if (next) {
		NextScene = next;
		ChangeScene = true;
	}
}