#include "Main.h"

#ifdef _DEBUG
gui::CGUIDebugBoard* DebugBoard;
#endif // _DEBUG

int main() {
	device = utils::getDevice();
	if (device == nullptr) {
		return 1;
	}

	device->setWindowCaption(L"‚à‚­‚à‚­Žl–Ú");

	csr = device->getCursorControl();
	fsy = device->getFileSystem();
	env = device->getGUIEnvironment();
	lgr = device->getLogger();
	opr = device->getOSOperator();
	rdm = device->getRandomizer();
	mgr = device->getSceneManager();
	tim = device->getTimer();
	drv = device->getVideoDriver();
	mnp = mgr->getMeshManipulator();
	colmgr = mgr->getSceneCollisionManager();
	Resolution = drv->getScreenSize();
	sce = (IScene*)new StartMenu();
	gac = new gui::GUIAnimationCenter(tim);

	sce->init();
	NextScene = 0;
	ChangeScene = false;

	/////////////////////////////////////////////////////////////////////
	video::ITexture* logo = drv->getTexture("Resources/Images/Logo.png");
	if (logo) {
		core::dimension2di logoSize(logo->getOriginalSize());
		drv->beginScene(true, false, video::SColor(255, 255, 255, 255));
		drv->draw2DImage(logo, core::vector2di((Resolution.Width - logoSize.Width) / 2, ((s32)Resolution.Height - logoSize.Height) / 2));
		drv->endScene();
	}
	/////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	core::vector3df origin = core::vector3df(1.0f, -0.2f, 1.0f);
	scene::ICameraSceneNode* camera = mgr->addCameraSceneNode(0, origin + core::vector3df(0, 2, -3), origin, SceneNode_IDs::Camera);
	camera->setNearValue(0.1f);
	camera->setFarValue(10.0f);

#ifdef _DEBUG
	DebugBoard = new gui::CGUIDebugBoard(env, core::recti(0, 0, 640, 480));
	DebugBoard->setVisible(false);
	gui::IGUIFont* debugFont = env->getFont("../../Debug_Font/Debug_Font.xml");
	if (debugFont) {
		DebugBoard->setFont(debugFont);
		DebugBoard->setColor(video::SColor(128, 255, 255, 255));

		env->getSkin()->setFont(debugFont);
	}

	camera->setPosition(core::vector3df(0, 2, -3));
	scene::CoordinateSystemCursor* node = new scene::CoordinateSystemCursor(mgr->getRootSceneNode(), mgr, 777);
	core::vector3df* lookat = (core::vector3df*) & (node->getPosition());
	camera->setTarget(*lookat);
	scene::CSceneNodeAnimatorCameraTPS* cameraAnimator = new scene::CSceneNodeAnimatorCameraTPS(lookat, true);
	if (cameraAnimator) {
		camera->addAnimator(cameraAnimator);
		cameraAnimator->drop();
	}
#else
	core::vector3df cameraTarget(1.0f, 0.7f, 1.0f);
	scene::CSceneNodeAnimatorCameraTPS* cameraAnimator = new scene::CSceneNodeAnimatorCameraTPS(&cameraTarget);
	if (cameraAnimator) {
		cameraAnimator->MinZoomIn = 1.8f;
		cameraAnimator->MaxZoomOut = 4.0f;
		camera->addAnimator(cameraAnimator);
		cameraAnimator->drop();
	}
#endif // _DEBUG
	/////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	mgr->setAmbientLight(video::SColorf(0.8f, 0.8f, 0.8f));
	mgr->addLightSceneNode(0, origin + core::vector3df(2.0f, 3.0f, 1.0f), video::SColorf(0.2f, 0.2f, 0.2f), 5.0f);

	scene::IAnimatedMesh* standMesh = mgr->getMesh("Resources/Models/Stand.obj");
	if (standMesh) {
		StandNode = mgr->addAnimatedMeshSceneNode(standMesh, 0, SceneNode_IDs::Stand, origin);
		if (StandNode) {
			video::ITexture* standTexture = drv->getTexture("Resources/Images/Stand.png");
			if (standTexture) {
				StandNode->setMaterialTexture(0, standTexture);
			}

			scene::ITriangleSelector* selector = mgr->createTriangleSelector(StandNode);
			if (selector) {
				StandNode->setTriangleSelector(selector);
				selector->drop();
			}
		}
		else {
			device->drop();
			return 2;
		}
	}

	StoneMesh = mgr->getMesh("Resources/Models/Stone.obj");
	if (StoneMesh) {
		StoneMeshST = mnp->createMeshCopy(StoneMesh);
		mnp->setVertexColorAlpha(StoneMeshST, 128);
	}
	else
	if (StoneMesh == nullptr) {
		device->drop();
		return 2;
	}

	gui::IGUIFont* font = env->getFont("Resources/Fonts/Font.xml");
	if (font) {
		env->getSkin()->setFont(font);
	}
	/////////////////////////////////////////////////////////////////////

	u32 count = 0, pn = 0;

	s32 lastFPS = -1;
	u32 then = tim->getTime();

	bool active = true;
	while (device->run()) {
		u32 now = tim->getTime();
		u32 time = now - then;
		f32 frameDeltaTime = (f32)time / 1000.0f;
		then = now;

		if (ChangeScene) {
			sce->drop();
			sce = NextScene;

			sce->init();
			NextScene = 0;
			ChangeScene = false;
		}

		if (device->isWindowActive()) {
			if (!active) {
				tim->start();
				active = true;
			}

			sce->update(frameDeltaTime);

			drv->beginScene(true, true, video::SColor(0, 100, 100, 100));

			mgr->drawAll();
			env->drawAll();

			sce->draw();

#ifdef _DEBUG
			DebugBoard->draw();
#endif // _DEBUG

			drv->endScene();
		}
		else {
			if (active) {
				tim->stop();
				active = false;
			}

			device->yield();
		}

		s32 fps = drv->getFPS();
		if (lastFPS != fps) {
			lastFPS = fps;
		}

#ifdef _DEBUG
		DebugBoard->appendLine(core::stringc("fps:") + utils::rn_to_str<c8>(fps));
		DebugBoard->appendLine(core::stringc("now:") + utils::rn_to_str<c8>(now));
#endif // _DEBUG
	}
	
	StoneMeshST->drop();

	sce->drop();
	gac->drop();
	
	device->drop();

	return 0;
}