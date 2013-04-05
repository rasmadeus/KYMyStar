#pragma once

#include "Split.h"
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreQuaternion.h>

class MissileState{
private:
	//_data[0, 1, 2]      - x, y, z Missile's position
	//_data[3, 4, 5, 6]   - q0, q1, q2, q3 - Missile's orientation - quaternion components  
	//_data[7, 8, 9, 10]  - Missile's rule - d1, d2, d3, d4 
	//_data[11]           - Engine's power
	std::vector<Ogre::Real> mData;
public:
	MissileState();
	MissileState(const std::string& row);
	Ogre::Quaternion getOrientation() const;
	Ogre::Vector3    getPosition()    const;
	Ogre::Degree     getFirstWheel()  const;
	Ogre::Degree     getSecondWheel() const;
	Ogre::Degree     getThirdWheel()  const;
	Ogre::Degree     getFourthWheel() const;
	Ogre::Real       getEnginePower() const;    
	
};