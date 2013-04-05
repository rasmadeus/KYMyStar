#pragma once

class Telemetry;

#include "../Object3D/Object3D.h"

namespace Ogre
{
	class Camera;
	class ParticleSystem;
	class SceneManager;
}

class Missile: public Object3D
{
public:
	Missile();
	~Missile();

	void setCamera(Ogre::Camera* mCamera);

    void create(std::string scene_name, std::string group_name, std::string body_name);

	void move();
	void updateTail(Ogre::Degree angle);

	void loadTelemetry(const std::string& path);

	void stop();
	void toBeginPos();
	void incSpeed();
	void decSpeed();

	void setGrabCamera();
private:
	void setMissileParts();

	void setFirstWheel(Ogre::Degree angle);
	void setSecondWheel(Ogre::Degree angle);
	void setThirdWheel(Ogre::Degree angle);
	void setFourthWheel(Ogre::Degree angle);
	void setMissilePower(Ogre::Real power);
	
	void createFireAndSmoke();
	void createOrigin();
private:
	Telemetry* mTelemetry;

	Ogre::Node* mTail;
	Ogre::Node* mFirstWheel;
	Ogre::Node* mSecondWheel;
	Ogre::Node* mThirdWheel;
	Ogre::Node* mFourthWheel;	

	bool grabCamera;
	Ogre::Camera* mCamera;
	Ogre::Vector3 cameraMissileDistance;

	Ogre::ParticleSystem* mFire;
	Ogre::ParticleSystem* mSmoke;
};

