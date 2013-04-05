#pragma once

namespace Ogre{
	class Node;
	class SceneManager;
	class DotSceneLoader;
}

#include <OGRE/OgreVector3.h>

class Object3D
{
public:
	explicit Object3D(float scale);
	virtual ~Object3D();
	void setSceneMgr(Ogre::SceneManager* mSceneMgr);
	virtual void create(std::string scene_name, std::string group_name, std::string body_name);
	void setPosition(Ogre::Vector3 position);
	void setOrientation(const Ogre::Quaternion& orientation);
	Ogre::Node* getBody();
protected:
	Ogre::Node* mBody;
	Ogre::SceneManager* mSceneMgr;
	float scale;
private:
	Ogre::DotSceneLoader* mLoader;	
};

