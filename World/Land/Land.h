#pragma once

namespace Ogre{
	class SceneManager;
}

class Land
{
public:
	void create_land(Ogre::SceneManager* mSceneMgr);
	static float getLength();
};

