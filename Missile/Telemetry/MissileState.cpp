#include "MissileState.h"

#include "Split.h"
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreQuaternion.h>
#include <string>

MissileState::MissileState(): mData(12, 0)
{
    mData[3] = 1;
}

MissileState::MissileState(const std::string& row): mData(12, 0)
{
	std::vector<Ogre::Real> data = Split::split(row);
	int min_size = std::min<int>(12, data.size());
	for(int i=0; i<min_size; ++i) mData[i] = data[i];
}

Ogre::Quaternion MissileState::getOrientation() const
{
	return Ogre::Quaternion(mData[3], mData[4], mData[5], mData[6]);
}

Ogre::Vector3 MissileState::getPosition() const
{
    return Ogre::Vector3(mData[0], mData[1], mData[2]);
}

Ogre::Degree MissileState::getFirstWheel() const
{
	return static_cast<Ogre::Degree>(mData[7]);
}

Ogre::Degree MissileState::getSecondWheel() const
{
	return static_cast<Ogre::Degree>(mData[8]);
}

Ogre::Degree  MissileState::getThirdWheel() const
{
	return static_cast<Ogre::Degree>(mData[9]);
}

Ogre::Degree MissileState::getFourthWheel() const
{
	return static_cast<Ogre::Degree>(mData[10]);
}

Ogre::Real MissileState::getEnginePower() const
{
    return mData[11];	
}
