#include "Forest.h"

Forest::Forest():
	mTrees(0)
{
}

#include <Ogre.h>
#include <PagedGeometry.h>
#include <TreeLoader2D.h>
#include <ImpostorPage.h>
#include <WindBatchPage.h>
void Forest::create_trees(Ogre::Camera* mCamera, Ogre::SceneManager* mSceneMgr)
{
	mTrees = new Forests::PagedGeometry(mCamera);
    mTrees->addDetailLevel<Forests::WindBatchPage>(1000, 200);  
    mTrees->addDetailLevel<Forests::ImpostorPage>(1500, 200);

	Forests::TreeLoader2D *treeLoader = new Forests::TreeLoader2D(mTrees, Forests::TBounds(-300, -300, 300, 300));
    mTrees->setPageLoader(treeLoader);

    treeLoader->setColorMap("terrain_lightmap.jpg"); 

    Ogre::Entity *tree1 = mSceneMgr->createEntity("Tree1", "fir05_30.mesh");
    Ogre::Entity *tree2 = mSceneMgr->createEntity("Tree2", "fir14_25.mesh");
	Ogre::Entity *tree3 = mSceneMgr->createEntity("Tree3", "fir06_30.mesh");

    mTrees->setCustomParam(tree1->getName(), "windFactorX", 15);  
    mTrees->setCustomParam(tree1->getName(), "windFactorY", 0.01f);
    mTrees->setCustomParam(tree2->getName(), "windFactorX", 22);
    mTrees->setCustomParam(tree2->getName(), "windFactorY", 0.013f);
   	
	treeLoader->addTree(tree1, Ogre::Vector3(-50,0,0),   Ogre::Degree(0),   Ogre::Real(0.2));
	treeLoader->addTree(tree2, Ogre::Vector3(50,0,-50),  Ogre::Degree(90),  Ogre::Real(0.2));
	treeLoader->addTree(tree3, Ogre::Vector3(100,0,100), Ogre::Degree(-34), Ogre::Real(0.2));
	treeLoader->addTree(tree2, Ogre::Vector3(60,0,-55),  Ogre::Degree(78),  Ogre::Real(0.2));
	treeLoader->addTree(tree1, Ogre::Vector3(90,0,70),   Ogre::Degree(57),  Ogre::Real(0.2));
	treeLoader->addTree(tree3, Ogre::Vector3(-50,0,-50), Ogre::Degree(-34), Ogre::Real(0.1));
	treeLoader->addTree(tree2, Ogre::Vector3(-60,0, 55), Ogre::Degree(78),  Ogre::Real(0.15));
	treeLoader->addTree(tree3, Ogre::Vector3(10,0,-70),  Ogre::Degree(17),  Ogre::Real(0.14));
}

void Forest::release(Ogre::SceneManager* mSceneMgr)
{
	if(mTrees){
        delete mTrees->getPageLoader();
        delete mTrees;
        mTrees = 0;
    }

	if(mSceneMgr){
		mSceneMgr->destroyEntity("Tree1");
		mSceneMgr->destroyEntity("Tree2");
		mSceneMgr->destroyEntity("Tree3");
	}
}

void Forest::update()
{
	if(mTrees) mTrees->update();
}
