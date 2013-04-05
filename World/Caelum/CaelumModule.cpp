#include "CaelumModule.h"

void CaelumModule::create_caelum(Ogre::SceneManager* mSceneMgr, Ogre::RenderWindow* mRenderWnd){
   Caelum::CaelumSystem::CaelumComponent componentMask = 
			static_cast<Caelum::CaelumSystem::CaelumComponent> (
			Caelum::CaelumSystem::CAELUM_COMPONENT_SUN      |				
			Caelum::CaelumSystem::CAELUM_COMPONENT_SKY_DOME |
			Caelum::CaelumSystem::CAELUM_COMPONENT_MOON     |
			Caelum::CaelumSystem::CAELUM_COMPONENT_CLOUDS );

		mCaelumSystem = new Caelum::CaelumSystem(Ogre::Root::getSingletonPtr(), mSceneMgr, componentMask);
		mCaelumSystem->setManageSceneFog(false);
		mCaelumSystem->setGlobalFogColourMultiplier(Ogre::ColourValue(0.9,0.9,0.9));
		mCaelumSystem->getCloudSystem()->getLayer(0)->setHeight(20000);
		mCaelumSystem->getCloudSystem()->getLayer(0)->setCloudCover(0.2);
		mCaelumSystem->setEnsureSingleShadowSource(true);
		mCaelumSystem->setEnsureSingleLightSource(true);	
		mCaelumSystem->setManageAmbientLight(true);
		mCaelumSystem->setMinimumAmbientLight(Ogre::ColourValue(1, 1, 1));
		mCaelumSystem->setSun(new Caelum::SphereSun(mSceneMgr, mCaelumSystem->getCaelumCameraNode()));
		mCaelumSystem->setEnsureSingleShadowSource(true);
		mCaelumSystem->setEnsureSingleLightSource(true);
		if (mCaelumSystem->getSun()){
			mCaelumSystem->getSun()->setAmbientMultiplier(Ogre::ColourValue(0.5, 0.5, 0.5));
			mCaelumSystem->getSun()->setDiffuseMultiplier(Ogre::ColourValue(3, 3, 2.7));
			mCaelumSystem->getSun()->setSpecularMultiplier(Ogre::ColourValue(5, 5, 5));
			mCaelumSystem->getSun()->setAutoDisable(true);
			mCaelumSystem->getSun()->setAutoDisableThreshold(0.1);
			mCaelumSystem->getSun()->getMainLight()->setCastShadows(true);
		}
		if (mCaelumSystem->getMoon()){
			mCaelumSystem->getMoon()->setAutoDisable(true);
			mCaelumSystem->getMoon()->setAutoDisableThreshold(0.5);	
			//mCaelumSystem->getMoon()->setPhase(1000);
		}
		mCaelumSystem->getUniversalClock()->setGregorianDateTime(2008, 4, 9, 6, 33, 0);
		mCaelumSystem->setObserverLongitude(Ogre::Degree(10));
		mCaelumSystem->setObserverLatitude(Ogre::Degree(10));
		mCaelumSystem->getUniversalClock()->setTimeScale(0);
		Ogre::Root::getSingleton().addFrameListener(mCaelumSystem);
		mRenderWnd->addListener(mCaelumSystem);
}

Ogre::Vector3  CaelumModule::get_sun_position(Ogre::Camera *mCamera) const{
	Ogre::Vector3 sunPosition = mCamera->getDerivedPosition();
	sunPosition -= mCaelumSystem->getSun()->getLightDirection() * 80000;
	return sunPosition;
}

Ogre::ColourValue CaelumModule::get_sun_colour() const{
	return mCaelumSystem->getSun()->getBodyColour();
}

Ogre::ColourValue CaelumModule::get_sun_light_colour() const{
	Caelum::LongReal mJulian = mCaelumSystem->getUniversalClock()->getJulianDay();
	return mCaelumSystem->getSunLightColour(mJulian, mCaelumSystem->getSunDirection(mJulian));
}