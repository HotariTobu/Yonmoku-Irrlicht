#include "Scenes.h"

#include "CSceneNodeAnimatorFalling.h"

namespace irr {
	AlternatingPlay::AlternatingPlay() : Play() {
		black = video::SColor(255, 0, 0, 0);
		white = video::SColor(255, 255, 255, 255);
		yellow = video::SColor(255, 255, 255, 0);

		player1 = rdm->rand() % 2 == 0;
		hit = false;
		complete = false;
		shadowMaterial.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		shadowMaterial.DiffuseColor = white;
		shadowMaterial.AmbientColor = player1 ? black : white;
	}

	AlternatingPlay::~AlternatingPlay() {

	}

	void AlternatingPlay::init() {
		Play::init();

		statusLabel->setText(player1 ? L"プレイヤー１の番です。" : L"プレイヤー２の番です。");
	}

	void AlternatingPlay::update(f32 delta) {
		Play::update(delta);
	}

	void AlternatingPlay::draw() {
		Play::draw();

		if (hit && !complete) {
			drv->setTransform(video::ETS_WORLD, core::matrix4().setTranslation(core::vector3df(point.X * 0.5f + 0.25f, 1.35f, point.Y * 0.5f + 0.25f)));
			drv->setMaterial(shadowMaterial);

			if (StoneMeshST) {
				u32 meshBufferCount = StoneMeshST->getMeshBufferCount();
				for (u32 i = 0; i < meshBufferCount; i++) {
					scene::IMeshBuffer* meshBuffer = StoneMeshST->getMeshBuffer(i);
					drv->drawMeshBuffer(meshBuffer);
				}
			}
		}
	}

	bool AlternatingPlay::onEvent(const SEvent& event) {
		switch (event.EventType) {
		case EET_MOUSE_INPUT_EVENT:
			switch (event.MouseInput.Event) {
			case EMIE_MOUSE_MOVED:
			{
				core::vector3df intersection;
				core::triangle3df hitTriangle;

				hit = colmgr->getSceneNodeAndCollisionPointFromRay(colmgr->getRayFromScreenCoordinates(device->getCursorControl()->getPosition()), intersection, hitTriangle, SceneNode_IDs::Stand) && intersection.Y > 0;
				if (hit) {
					point.X = (s32)(intersection.X / 0.5f);
					point.Y = (s32)(intersection.Z / 0.5f);

#ifdef _DEBUG
					DebugBoard->appendLine(core::stringw("(column, row) = ") + utils::vec2d_to_str<c8>(point));
#endif // _DEBUG

					if (point.X < 0 || point.X > 3 || point.Y < 0 || point.Y > 3 || Blocks[point.X][point.Y][3].Stone) {
						hit = false;
					}
				}
			}
			break;

			case EMIE_LMOUSE_LEFT_UP:
				if (hit && !complete) {
					s32 i = 0;
					for (; i < 4; i++) {
						if (Blocks[point.X][point.Y][i].Stone == nullptr) {
							break;
						}
					}

					BlockState checkState = BlockState::Empty;

					scene::IAnimatedMeshSceneNode* stoneNode = mgr->addAnimatedMeshSceneNode(StoneMesh, StandNode, (point.X << 4 | point.Y << 2 | i) | SceneNode_IDs::Stone, core::vector3df(point.X * 0.5f - 0.75f, 1.55f, point.Y * 0.5f - 0.75f));
					if (stoneNode) {
						if (i == 3) {
							Filled[point.X + point.Y * 4] = true;
						}
						Block* block = &(Blocks[point.X][point.Y][i]);
						block->Stone = stoneNode;

						video::SMaterial* material = &(stoneNode->getMaterial(0));
						material->DiffuseColor = white;

						if (player1) {
							checkState = BlockState::Black;

							material->AmbientColor = black;
							shadowMaterial.AmbientColor = white;

							statusLabel->setText(L"プレイヤー２の番です。");
						}
						else {
							checkState = BlockState::White;

							material->AmbientColor = white;
							shadowMaterial.AmbientColor = black;

							statusLabel->setText(L"プレイヤー１の番です。");
						}

						block->State = checkState;

						stoneNode->addAnimator(new scene::CSceneNodeAnimatorFalling(0.3f * (4 - i), 9.8f));
					}

					s32 x = 0, y = 0, z = 0;
					for (; x < 4 && Blocks[x][point.Y][i].State == checkState; x++);
					for (; y < 4 && Blocks[point.X][y][i].State == checkState; y++);
					for (; z < 4 && Blocks[point.X][point.Y][z].State == checkState; z++);

					if (x == 4) {
						complete = true;
						for (x = 0; x < 4; x++) {
							turnYellow(x, point.Y, i);
						}
					}

					if (y == 4) {
						complete = true;
						for (y = 0; y < 4; y++) {
							turnYellow(point.X, y, i);
						}
					}

					if (z == 4) {
						complete = true;
						for (z = 0; z < 4; z++) {
							turnYellow(point.X, point.Y, z);
						}
					}


					if (point.X == point.Y) {
						s32 xy = 0;
						for (; xy < 4 && Blocks[xy][xy][i].State == checkState; xy++);
						if (xy == 4) {
							complete = true;
							for (xy = 0; xy < 4; xy++) {
								turnYellow(xy, xy, i);
							}
						}

						if (point.X == i) {
							s32 xyz = 0;
							for (; xyz < 4 && Blocks[xyz][xyz][xyz].State == checkState; xyz++);
							if (xyz == 4) {
								complete = true;
								for (xyz = 0; xyz < 4; xyz++) {
									turnYellow(xyz, xyz, xyz);
								}
							}
						}
						else if (point.X == 3 - i) {
							s32 xyz = 0;
							for (; xyz < 4 && Blocks[xyz][xyz][3 - xyz].State == checkState; xyz++);
							if (xyz == 4) {
								complete = true;
								for (xyz = 0; xyz < 4; xyz++) {
									turnYellow(xyz, xyz, 3 - xyz);
								}
							}
						}
					}
					else if (point.X == 3 - point.Y) {
						s32 xy = 0;
						for (; xy < 4 && Blocks[xy][3 - xy][i].State == checkState; xy++);
						if (xy == 4) {
							complete = true;
							for (xy = 0; xy < 4; xy++) {
								turnYellow(xy, 3 - xy, i);
							}
						}

						if (point.X == i) {
							s32 xyz = 0;
							for (; xyz < 4 && Blocks[xyz][3 - xyz][xyz].State == checkState; xyz++);
							if (xyz == 4) {
								complete = true;
								for (xyz = 0; xyz < 4; xyz++) {
									turnYellow(xyz, 3 - xyz, xyz);
								}
							}
						}
						else if (point.X == 3 - i) {
							s32 xyz = 0;
							for (; xyz < 4 && Blocks[xyz][3 - xyz][3 - xyz].State == checkState; xyz++);
							if (xyz == 4) {
								complete = true;
								for (xyz = 0; xyz < 4; xyz++) {
									turnYellow(xyz, 3 - xyz, 3 - xyz);
								}
							}
						}
					}

					if (point.X == i) {
						s32 xz = 0;
						for (; xz < 4 && Blocks[xz][point.Y][xz].State == checkState; xz++);
						if (xz == 4) {
							complete = true;
							for (xz = 0; xz < 4; xz++) {
								turnYellow(xz, point.Y, xz);
							}
						}
					}
					else if (point.X == 3 - i) {
						s32 xz = 0;
						for (; xz < 4 && Blocks[xz][point.Y][3 - xz].State == checkState; xz++);
						if (xz == 4) {
							complete = true;
							for (xz = 0; xz < 4; xz++) {
								turnYellow(xz, point.Y, 3 - xz);
							}
						}
					}

					if (point.Y == i) {
						s32 yz = 0;
						for (; yz < 4 && Blocks[point.X][yz][yz].State == checkState; yz++);
						if (yz == 4) {
							complete = true;
							for (yz = 0; yz < 4; yz++) {
								turnYellow(point.X, yz, yz);
							}
						}
					}
					else if (point.Y == 3 - i) {
						s32 yz = 0;
						for (; yz < 4 && Blocks[point.X][yz][3 - yz].State == checkState; yz++);
						if (yz == 4) {
							complete = true;
							for (yz = 0; yz < 4; yz++) {
								turnYellow(point.X, yz, 3 - yz);
							}
						}
					}

					if (complete) {
						statusLabel->setText(player1 ? L"プレイヤー１の勝利です！" : L"プレイヤー２の勝利です！");
					}
					else if (i == 3) {
						s32 x4y = 0;
						for (; x4y < 16 && Filled[x4y]; x4y++);
						if (x4y == 16) {
							complete = true;
							statusLabel->setText(L"引き分けです。");
						}
					}

					player1 = !player1;
				}
				break;
			}
			break;
		}

		return false;
	}

	void AlternatingPlay::turnYellow(s32 x, s32 y, s32 z) {
		if (x < 0 || x > 3 || y < 0 || y > 3 || z < 0 || z > 3) {
			return;
		}

		scene::ISceneNode* stoneNode = Blocks[x][y][z].Stone;
		if (stoneNode) {
			stoneNode->getMaterial(0).AmbientColor = yellow;
		}
	}

}