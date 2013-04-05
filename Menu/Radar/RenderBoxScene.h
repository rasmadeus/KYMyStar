/*!
	@file
	@author		Evmenov Georgiy
	@date		01/2008
	@module
*/

#ifndef __RENDER_BOX_WRAP_H__
#define __RENDER_BOX_WRAP_H__

#include <Ogre.h>
#include "RenderBox.h"

namespace wraps
{

	class RenderBoxScene : public RenderBox
	{
	public:
		RenderBoxScene() :
			mScene(nullptr),
			mNode(nullptr),
			mCameraNode(nullptr),
			mCamera(nullptr),
			mEntity(nullptr),
			mMouseRotation(false),
			mLastPointerX(0),
			mMousePressed(false),
			mFrameAdvise(false)
		{
		}

		virtual ~RenderBoxScene()
		{
		}


		/** Add mesh to scene and remove previous one
			@param
				_meshName The name of the Mesh it is to be based on (e.g. 'ogrehead.mesh').
				
		*/
		
		void injectPoint(){			
			Ogre::ManualObject* manual = mScene->createManualObject("pointM");
			manual->begin("PointM/pointM", Ogre::RenderOperation::OT_TRIANGLE_LIST);
			manual->position(5.0, 0.0, 0.0);
			manual->textureCoord(1,1);
			manual->position(-5.0, 10.0, 0.0);
			manual->textureCoord(0,0);
			manual->position(-5.0, 0.0, 0.0);
			manual->textureCoord(0,1);
			manual->position(5.0, 0.0, 0.0);
			manual->textureCoord(1,1);
			manual->position(5.0, 10.0, 0.0);
			manual->textureCoord(1,0);
			manual->position(-5.0, 10.0, 0.0);
			manual->textureCoord(0,0);
			manual->end();
			pointM = mScene->getRootSceneNode()->createChildSceneNode("pointMM");
			pointM->attachObject(manual);
			pointM->setPosition(-0.15, -3.8, 9.9);
			pointM->scale(0.05, 0.05, 0.05);
		}

		void setMissilePos(Ogre::Vector3 pos){
			pointM->setPosition(-pos.z *0.0002 - 0.15, pos.x * 0.0002  - 3.8, 9.9);
		}

		void injectObject()
		{
			clearScene();
			Ogre::ManualObject* manual = mScene->createManualObject("wayVIL");
			manual->begin("PI/put", Ogre::RenderOperation::OT_TRIANGLE_LIST);
			manual->position(5.0, 0.0, 0.0);
			manual->textureCoord(1,1);
			manual->position(-5.0, 10.0, 0.0);
			manual->textureCoord(0,0);
			manual->position(-5.0, 0.0, 0.0);
			manual->textureCoord(0,1);
			manual->position(5.0, 0.0, 0.0);
			manual->textureCoord(1,1);
			manual->position(5.0, 10.0, 0.0);
			manual->textureCoord(1,0);
			manual->position(-5.0, 10.0, 0.0);
			manual->textureCoord(0,0);
			manual->end();
			Ogre::SceneNode* wayVIL = mScene->getRootSceneNode()->createChildSceneNode("wayVIL");
			wayVIL->attachObject(manual);
			wayVIL->setPosition(0, -4, 10);
			wayVIL->roll(Ogre::Degree(20));
			wayVIL->yaw(Ogre::Degree(180));
			injectPoint();

			mCameraNode->setPosition(0,0,0);
			mCamera->lookAt(0,0,10);
		}

		/** Run mesh animation if animation with such name exist (else print warning in log).
			To stop animation use empty string.
		*/
	

		/** Clear scene */
		void clearScene()
		{

			if (mScene)
			{
				mScene->destroyAllEntities();
				mNode->removeAndDestroyAllChildren();
			}

			mEntity = nullptr;

		}

	
		/** Set possibility to rotate mesh by mouse drag. */
		void setMouseRotation(bool _value)
		{
			mMouseRotation = _value;
		}

		/** Get mouse rotation flag */
		bool getMouseRotation()
		{
			return mMouseRotation;
		}

		virtual void setCanvas(MyGUI::Canvas* _value)
		{
			RenderBox::setCanvas(_value);

			mCanvas->eventMouseDrag += newDelegate(this, &RenderBoxScene::notifyMouseDrag);
			mCanvas->eventMouseButtonPressed += newDelegate(this, &RenderBoxScene::notifyMouseButtonPressed);
			mCanvas->eventMouseButtonReleased += newDelegate(this, &RenderBoxScene::notifyMouseButtonReleased);

			createScene();
		}

		virtual void destroy()
		{
			clearScene();

			if (mCanvas)
			{
				frameAdvise(false);

				mCanvas->eventMouseDrag -= newDelegate(this, &RenderBoxScene::notifyMouseDrag);
				mCanvas->eventMouseButtonPressed -= newDelegate(this, &RenderBoxScene::notifyMouseButtonPressed);
				mCanvas->eventMouseButtonReleased -= newDelegate(this, &RenderBoxScene::notifyMouseButtonReleased);
				mCanvas = nullptr;

				Ogre::Root* root = Ogre::Root::getSingletonPtr();
				if (root && mScene)
					root->destroySceneManager(mScene);
				mScene = nullptr;
				mNode = nullptr;
			}

			RenderBox::destroy();
		}

	private:
		void notifyMouseDrag(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
		{
			if (mMouseRotation)
			{
				if (mNode)
					mNode->yaw(Ogre::Radian(Ogre::Degree((float)_left - mLastPointerX)));
				mLastPointerX = _left;
			}
		}

		void notifyMouseButtonPressed(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
		{
			if (mMouseRotation)
			{
				if (_id == MyGUI::MouseButton::Left)
				{
					const MyGUI::IntPoint& point = MyGUI::InputManager::getInstance().getLastPressedPosition(MyGUI::MouseButton::Left);
					mLastPointerX = point.left;
					mMousePressed = true;
				}
				if (_id == MyGUI::MouseButton::Right)
				{
					const MyGUI::IntPoint& point = MyGUI::InputManager::getInstance().getLastPressedPosition(MyGUI::MouseButton::Right);
					mLastPointerX = point.left;
					mMousePressed = true;
				}
			}
		}

		void notifyMouseButtonReleased(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
		{
			mMousePressed = false;
		}

		void frameAdvise(bool _advise)
		{
			if (_advise && !mFrameAdvise)
			{
				MyGUI::Gui::getInstance().eventFrameStart += MyGUI::newDelegate(this, &RenderBoxScene::frameEntered);
				mFrameAdvise = true;
			}
			else if (!_advise && mFrameAdvise)
			{
				MyGUI::Gui::getInstance().eventFrameStart -= MyGUI::newDelegate(this, &RenderBoxScene::frameEntered);
				mFrameAdvise = false;
			}
		}

		void frameEntered(float _time)
		{
			
		}

		void createScene()
		{
			// создаем новый сцен менеджер
			mScene = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, MyGUI::utility::toString(this, "_SceneManagerRenderBox"));

			// создаем нод к которуму будем всякую дрянь атачить
			mNode = mScene->getRootSceneNode()->createChildSceneNode();

			mScene->setAmbientLight(Ogre::ColourValue(1, 1, 1));

			// главный источник света
			Ogre::Vector3 dir(0, 0, 0);
			dir.normalise();
			Ogre::Light* light = mScene->createLight(MyGUI::utility::toString(this, "_LightRenderBox"));
			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDirection(dir);
		


			std::string camera(MyGUI::utility::toString(this, "_CameraRenderBox"));
			mCamera = mScene->createCamera(camera);
			mCamera->setNearClipDistance(1);
		//mCamera->setFarClipDistance(1000);

			mCameraNode = mScene->getRootSceneNode()->createChildSceneNode(camera);
			mCameraNode->attachObject(mCamera);

			if (mCanvas->getHeight() == 0)
				mCamera->setAspectRatio(1);
			else
				mCamera->setAspectRatio( float(mCanvas->getWidth()) / float(mCanvas->getHeight()) );

			setViewport(mCamera);
		}
		

		virtual void requestUpdateCanvas(MyGUI::Canvas* _canvas, MyGUI::Canvas::Event _event)
		{
			RenderBox::requestUpdateCanvas(_canvas, _event);
		}
		public:
		Ogre::SceneNode* Node(){
			return mNode;
		}
	private:
		Ogre::SceneManager* mScene;
		Ogre::SceneNode* mNode;
		Ogre::SceneNode* mCameraNode;
		Ogre::SceneNode* pointM;
		Ogre::Camera* mCamera;
		Ogre::Entity* mEntity;
		
		bool mMouseRotation;
		int mLastPointerX;
		bool mMousePressed;

		bool mFrameAdvise;
	};

} // namespace wraps

#endif // __RENDER_BOX_WRAP_H__
