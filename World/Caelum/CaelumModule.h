#pragma once

namespace Ogre{
	class SceneManager;
	class RenderWindow;
}

#include <Caelum/Caelum.h>

class CaelumModule {
public:
	void create_caelum(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mRenderWnd);
	Ogre::Vector3 get_sun_position(Ogre::Camera *mCamera) const;
	Ogre::ColourValue get_sun_colour() const;
	Ogre::ColourValue get_sun_light_colour() const;
private:
	Caelum::CaelumSystem* mCaelumSystem;
};
