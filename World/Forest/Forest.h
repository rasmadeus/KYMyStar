#pragma once

namespace Forests
{
	class PagedGeometry;
}

namespace Ogre
{
	class Camera;
	class SceneManager;
}

class Forest
{
public:
	Forest();
	void release(Ogre::SceneManager* mSceneMgr);
	void create_trees(Ogre::Camera* mCamera, Ogre::SceneManager* mSceneMgr);
	void update();
private:
	Forests::PagedGeometry *mTrees;
};

