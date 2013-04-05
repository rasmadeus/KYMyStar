#include "Missile.h"
#include <Ogre.h>
#include "Telemetry/Telemetry.h"

Missile::Missile() :
	Object3D(5),
	mTail(0),
	mFirstWheel(0),
	mSecondWheel(0),
	mThirdWheel(0),
	mFourthWheel(0),
	grabCamera(false),
	mCamera(0),
	mFire(0),
	mSmoke(0)
{
	mTelemetry = new Telemetry();
}

Missile::~Missile()
{
	delete mTelemetry;
}


void Missile::setCamera(Ogre::Camera* mCamera)
{
	this->mCamera = mCamera;
}

void Missile::create(std::string scene_name, std::string group_name, std::string body_name)
{
	Object3D::create(scene_name, group_name, body_name);
	setMissileParts();
	createFireAndSmoke();
	createOrigin();
}

#include "Telemetry/MissileState.h"
void Missile::move()
{
	const MissileState& state = mTelemetry->move();
	setPosition(Ogre::Vector3(state.getPosition().x * scale , state.getPosition().y * scale, state.getPosition().z * scale));
    setOrientation(state.getOrientation());
	setFirstWheel (state.getFirstWheel());
	setSecondWheel(state.getSecondWheel());
	setThirdWheel (state.getThirdWheel());
	setFourthWheel(state.getFourthWheel());
	setMissilePower(state.getEnginePower());
	if(grabCamera && mCamera){
		mCamera->setPosition(mBody->getPosition() + cameraMissileDistance);
	}
}


void Missile::updateTail(Ogre::Degree angle)
{
	if(mTail && mTelemetry->getCurrentPos()){
		mTail->pitch(angle);
	}
}

void Missile::loadTelemetry(const std::string& path)
{
	mTelemetry->loadTelemetry(path);
}

void Missile::stop()
{
	mTelemetry->stop();
}

void Missile::toBeginPos()
{
	mTelemetry->toBegin();
	if(mCamera){
		mCamera->setPosition(-10, 10, 0);
		mCamera->lookAt(0, 10, 0);
	}
}

void Missile::incSpeed()
{
	mTelemetry->incSpeed();
}

void Missile::decSpeed()
{
	mTelemetry->decSpeed();
}

void Missile::setGrabCamera()
{
	grabCamera = !grabCamera;
	if(grabCamera && mCamera){
		cameraMissileDistance = mCamera->getPosition() - mBody->getPosition();
	}
}

void Missile::setMissileParts()
{
	mTail        = mBody->getChild("tail");
	mFirstWheel  = mBody->getChild("rule1");
	mSecondWheel = mBody->getChild("rule2");
	mThirdWheel  = mBody->getChild("rule3");
	mFourthWheel = mBody->getChild("rule4");
}

void Missile::setFirstWheel(Ogre::Degree angle)
{
	if(mFirstWheel){
		mFirstWheel->setOrientation(Ogre::Quaternion(0.707107, 0.707107, 0, 0));
		mFirstWheel->roll(angle);
	}
}

void Missile::setSecondWheel(Ogre::Degree angle)
{
	if(mSecondWheel){
		mSecondWheel->setOrientation(Ogre::Quaternion(1, 0, 0, 0));
		mSecondWheel->roll(angle);
	}
}

void Missile::setThirdWheel(Ogre::Degree angle)
{
	if(mThirdWheel){
		mThirdWheel->setOrientation(Ogre::Quaternion(0.707107, -0.707107, 0, 0));
		mThirdWheel->roll(angle);
	}
}

void Missile::setFourthWheel(Ogre::Degree angle)
{
	if(mFourthWheel){
		mFourthWheel->setOrientation(Ogre::Quaternion(0, 1, 0, 0));
		mFourthWheel->roll(angle);
	}
}

void Missile::setMissilePower(Ogre::Real power)
{
	if(power > 0){
		mFire->setVisible(true);
		mSmoke->setVisible(false);
	}else
	if(power < 0){
		mFire->setVisible(false);
		mSmoke->setVisible(true);
	}else{
		mFire->setVisible(false);
		mSmoke->setVisible(false);
	}
}

void Missile::createFireAndSmoke()
{
	mFire = mSceneMgr->createParticleSystem("RRAEngine", "RRAEngine");
	Ogre::SceneNode* fire = mSceneMgr->createSceneNode("fire");
	fire->attachObject(mFire);
	mBody->addChild(fire);
	mFire->setVisible(false);
		
	mSmoke = mSceneMgr->createParticleSystem("RRAEngine_black", "RRAEngine_black");
	Ogre::SceneNode* smoke = mSceneMgr->createSceneNode("smoke");
	smoke->attachObject(mSmoke);
	mBody->addChild(smoke);
	mSmoke->setVisible(false);
}

void Missile::createOrigin()
{
	Ogre::SceneNode* origin = mSceneMgr->createSceneNode("Origin");
	origin->attachObject(mSceneMgr->createEntity("Origin", "Origin.mesh"));
	mSceneMgr->getRootSceneNode()->addChild(origin);
	origin->setPosition(0, 0, 0);
	origin->scale(0.1,0.1,0.1);	
	
}