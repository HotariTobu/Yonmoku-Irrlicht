#include "CSceneNodeAnimatorRandomRotateAround.h"

namespace irr {
	namespace scene {
		void CSceneNodeAnimatorRandomRotateAround::animateNode(ISceneNode* node, u32 timeMs) {
			if (!node || node->getType() != ESNT_CAMERA) {
				return;
			}

			if (!centerPos) {
				return;
			}

			ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);
			core::vector3df pos(camera->getPosition());

			core::vector2df XZ(pos.X, pos.Z);
			core::vector2df centerXZ(centerPos->X, centerPos->Z);
			f32 dis, theta;

			if (Dragging) {
				if (invert) {
					pos.rotateXZBy(dif.X * (f64)rotateSpeed, *centerPos);
				}
				else {
					pos.rotateXZBy(dif.X * (f64)-rotateSpeed, *centerPos);
				}

				XZ.X = pos.X;
				XZ.Y = pos.Z;
				dis = XZ.getDistanceFrom(centerXZ);
				if (dis != 0) {
					if (invert) {
						dis = -dis;
					}

					core::vector2df Y(core::vector2df(dis, pos.Y - centerPos->Y).rotateBy(dif.Y * (f64)rotateSpeed));

					bool modify = false;
					if (invert && Y.X > 0) {
						modify = true;
					}
					else if (!invert && Y.X < 0) {
						modify = true;
					}

					if (modify) {
						invert = !invert;
						camera->setUpVector(-camera->getUpVector());
					}

					pos.Y = Y.Y + centerPos->Y;
					XZ -= centerXZ;
					XZ *= Y.X / dis;
					XZ += centerXZ;
					pos.X = XZ.X;
					pos.Z = XZ.Y;
				}

				Dragging = false;
			}

			if (Zooming) {
				f32 move = wheel * zoomSpeed;
				core::vector3df addition;

				if (shift || ctrl) {
					if (shift) {
						dis = XZ.getDistanceFrom(centerXZ);
						if (dis != 0) {
							if (invert) {
								dis = -dis;
							}

							theta = atan2f(pos.Y - centerPos->Y, dis);
							addition.Y = move * cosf(theta);
							XZ -= centerXZ;
							XZ *= move * sinf(theta) / dis;
							addition.X = -XZ.X;
							addition.Z = -XZ.Y;
							XZ += centerXZ;

							pos += addition;
							*centerPos += addition;
						}
					}

					if (ctrl) {
						XZ -= centerXZ;
						theta = atan2f(XZ.Y, XZ.X);

						if (invert) {
							addition.X = -move * sinf(theta);
							addition.Z = move * cosf(theta);
						}
						else {
							addition.X = move * sinf(theta);
							addition.Z = -move * cosf(theta);
						}

						XZ += centerXZ;

						pos += addition;
						*centerPos += addition;
					}
				}
				else {
					dis = pos.getDistanceFrom(*centerPos);
					if (dis != 0 && dis > move) {
						pos -= *centerPos;
						pos *= (dis - move) / dis;
						pos += *centerPos;
					}
				}

				Zooming = false;
			}

			camera->setPosition(pos);
			camera->setTarget(*centerPos);
		}

		ISceneNodeAnimator* CSceneNodeAnimatorRandomRotateAround::createClone(ISceneNode* node, ISceneManager* newManager) {
			return new CSceneNodeAnimatorRandomRotateAround(centerPos, rotateSpeed, zoomSpeed);
		}

		bool CSceneNodeAnimatorRandomRotateAround::OnEvent(const SEvent& event) {
			if (event.EventType == EET_MOUSE_INPUT_EVENT) {
				static core::vector2di lastPos;
				static bool RButton = false;

				core::vector2di pos(event.MouseInput.X, event.MouseInput.Y);
				dif = pos - lastPos;
				lastPos = pos;

				wheel = event.MouseInput.Wheel;

				shift = event.MouseInput.Shift;
				ctrl = event.MouseInput.Control;

				switch (event.MouseInput.Event) {
				case EMIE_RMOUSE_PRESSED_DOWN:
					RButton = true;
					break;

				case EMIE_RMOUSE_LEFT_UP:
					RButton = false;
					break;

				case EMIE_MOUSE_MOVED:
					if (RButton) {
						Dragging = true;
					}
					break;

				case EMIE_MOUSE_WHEEL:
					Zooming = true;
					break;
				}
			}

			return false;
		}
	}
}