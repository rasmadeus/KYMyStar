#include "Object3D.h"
#include <OGRE/Ogre.h>

#include "DotSceneLoader/DotSceneLoader.h"
Object3D::Object3D(float scale):
	mSceneMgr(0),
	mBody(0),
	scale(scale),
	mLoader(new Ogre::DotSceneLoader())
{
}

Object3D::~Object3D()
{
	delete mLoader;
}

void Object3D::setSceneMgr(Ogre::SceneManager* mSceneMgr)
{
	this->mSceneMgr = mSceneMgr;
}

void Object3D::create(std::string scene_name, std::string group_name, std::string body_name)
{
	if(!mSceneMgr) return;
	Ogre::SceneNode* node = mSceneMgr->createSceneNode(body_name);
	mSceneMgr->getRootSceneNode()->addChild(node);
	mLoader->parseDotScene(scene_name, group_name, mSceneMgr, node);
	mBody = mSceneMgr->getRootSceneNode()->getChild(body_name);
	if(scale != 1) node->scale(scale, scale, scale);

}

void Object3D::setPosition(Ogre::Vector3 position)
{
	if(!mBody) return;
	mBody->setPosition(position);
}

void Object3D::setOrientation(const Ogre::Quaternion& orientation)
{
	if(!mBody) return;
	mBody->setOrientation(orientation);
}

Ogre::Node* Object3D::getBody()
{
	return mBody;
}