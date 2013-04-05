#include "Radar.h"


Radar::Radar(Ogre::SceneManager* mSceneMgr):
	mSceneMgr(mSceneMgr)
{
	createGui();	
}


Radar::~Radar(void)
{
	gRenderBoxScene.destroy();
}

#include <MyGUI/MyGUI.h>
void Radar::createGui(){
	const MyGUI::IntSize& size = MyGUI::RenderManager::getInstance().getViewSize();
	MyGUI::Window* window = MyGUI::Gui::getInstance().createWidget<MyGUI::Window>("WindowCS", MyGUI::IntCoord(size.width - 10 - 350, 10, 350, 300), MyGUI::Align::Default, "Overlapped");
	window->setCaption(std::wstring(L"Путь Ильича"));
    window->setMinSize(MyGUI::IntSize(100, 100));
	MyGUI::Canvas* canvas = window->createWidget<MyGUI::Canvas>("Canvas", MyGUI::IntCoord(0, 0, window->getClientCoord().width, window->getClientCoord().height), MyGUI::Align::Stretch);
	gRenderBoxScene.setCanvas(canvas);
	gRenderBoxScene.injectObject();	
}

void Radar::setMissilePos(Ogre::Vector3 pos){
	gRenderBoxScene.setMissilePos(pos);
}