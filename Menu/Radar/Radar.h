#pragma once
#include "RenderBoxScene.h"
namespace Ogre{
	class Camera;
	class SceneManager;
}

class Radar
{
public:
	Radar(Ogre::SceneManager* mSceneMgr);
	~Radar(void);
	void setMissilePos(Ogre::Vector3 pos);
private:
	void createGui();
private:
	wraps::RenderBoxScene gRenderBoxScene;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
};

