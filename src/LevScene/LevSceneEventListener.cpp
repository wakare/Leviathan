#include "LevSceneEventListener.h"
#include "LevSceneData.h"
#include "LevCamera.h"
#include "LevScene.h"
#include "Event.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneEventListener::LevSceneEventListener(LevScene& scene):
			m_scene(scene)
		{

		}

		void LevSceneEventListener::Accept(Event & event)
		{
			switch (event.m_action)
			{
			case Event::RESIZE:
				_handleResize(event);
				break;

			case Event::KEYDOWN:
			case Event::MOVE:
				_handleCameraTransform(event);
				break;
			}

		}

		LevCamera & LevSceneEventListener::_camera()
		{
			return *m_scene.GetSceneData().GetCamera();
		}

		bool LevSceneEventListener::_handleResize(Event & event)
		{
			auto _width = event.m_context.m_windowResizeSize.width;
			auto _height = event.m_context.m_windowResizeSize.height;
			m_scene.SetViewport(_width, _height);

			return true;
		}

		bool LevSceneEventListener::_handleCameraTransform(Event& event)
		{
			// Update transform
			float fTranslate[3] = { 0.0f };
			if ((event.m_action == Event::InputAction::KEYDOWN || event.m_action == Event::InputAction::REPERT))
			{
				if (event.m_code == Event::InputCode::KEY_W)
				{
					fTranslate[1] += 0.02f;
				}

				if (event.m_code == Event::InputCode::KEY_S)
				{
					fTranslate[1] -= 0.02f;
				}

				if (event.m_code == Event::InputCode::KEY_A)
				{
					fTranslate[0] += 0.02f;
				}

				if (event.m_code == Event::InputCode::KEY_D)
				{
					fTranslate[0] -= 0.02f;
				}
			}

			if ((event.m_action == Event::InputAction::SCROLL))
			{
				fTranslate[2] += (event.m_context.m_mouseScrollState.y * 0.02f);
			}

			if (fTranslate[0] != 0.0f || fTranslate[1] != 0.0f || fTranslate[2] != 0.0f)
			{
				_camera().MouseTranslate(fTranslate[0], fTranslate[1], fTranslate[2]);
			}

			// Update camera rotation
			float fRotate[3] = { 0.0f, 0.0f, 0.0f };
			static MouseCoord lastMouseXY = MouseCoord(-1, -1);

			static bool bLMouseDown = false;
			if (event.m_action == Event::InputAction::KEYDOWN && event.m_code == Event::InputCode::MOUSE_LBUTTON) bLMouseDown = true;
			if (event.m_action == Event::InputAction::KEYUP && event.m_code == Event::InputCode::MOUSE_LBUTTON) bLMouseDown = false;

			if (bLMouseDown)
			{
				if (lastMouseXY.x >= 0 && lastMouseXY.y >= 0)
				{
					float delta[2] = { event.m_mouseCoord.x - lastMouseXY.x, event.m_mouseCoord.y - lastMouseXY.y };
					delta[0] = ANGLE_TO_RADIAN(delta[0] * 0.1f);
					delta[1] = ANGLE_TO_RADIAN(delta[1] * 0.1f);

					_camera().MouseRotate(delta[0], delta[1]);
				}
			}

			static bool bMMouseDown = false;
			if (event.m_action == Event::InputAction::KEYDOWN && event.m_code == Event::InputCode::MOUSE_SCROLLBUTTON) bMMouseDown = true;
			if (event.m_action == Event::InputAction::KEYUP && event.m_code == Event::InputCode::MOUSE_SCROLLBUTTON) bMMouseDown = false;

			if (bMMouseDown)
			{
				if (lastMouseXY.x >= 0 && lastMouseXY.y >= 0)
				{
					float delta[2] = { event.m_mouseCoord.x - lastMouseXY.x, event.m_mouseCoord.y - lastMouseXY.y };
					delta[0] = ANGLE_TO_RADIAN(delta[0] * 0.1f);
					delta[1] = ANGLE_TO_RADIAN(delta[1] * 0.1f);

					_camera().MouseDrag(delta[0], delta[1]);
				}
			}

			lastMouseXY = event.m_mouseCoord;

			// Update light position as camera move
			/*for (auto& pLight : m_scene.GetLightVec())
			{
				pLight->SetLightCoord({ m_scene.GetCamera().m_fEye[0], m_scene.GetCamera().m_fEye[1], m_scene.GetCamera().m_fEye[2] });
			}*/

			return true;
		}
	}
}