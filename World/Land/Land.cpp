#include "Land.h"

#include <Ogre.h>
void Land::create_land(Ogre::SceneManager* mSceneMgr)
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
	Ogre::String plane_name = "plane";
	Ogre::String ent_name   = "ent";
	Ogre::MeshManager::getSingleton().createPlane(
		plane_name,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		getLength(),
		getLength(),
		200,
		200,
		true,
		1,
		5,
		5,
		Ogre::Vector3::UNIT_Z
	);
	Ogre::Entity* ent = mSceneMgr->createEntity(ent_name, plane_name);
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);
	node->setPosition(0, 0, 0);
	ent->setMaterialName("Examples/GrassFloor");
}

float Land::getLength()
{
	return 150000;
}