#include "SceneMenu.h"
#include "../Scene/KYMyStar.h"
#include "OpenSaveDialog/OpenSaveFileDialog.h"

SceneMenu::SceneMenu(KYMyStar* mApp, MyGUI::Gui* mGui, Missile* mMissile):
	state(MENU_IS_ACTIVE),
	mGui(mGui),
	mApp(mApp),
	mMissile(mMissile),
	mIsLoadingTm(false)
{
	createGui();
	createChildren();
	menuToCenter();
	mOpenTm->hide();
}

SceneMenu::~SceneMenu()
{
	delete mOpenTm;
}

bool SceneMenu::isActive() const
{
    return state == MENU_IS_ACTIVE;
}

bool SceneMenu::isPassive() const
{
    return state == MENU_IS_PASSIVE;
}

void SceneMenu::show()
{
	mWindow->setVisible(true);
	state = MENU_IS_ACTIVE;
	mGui->setVisiblePointer(true);
}

void SceneMenu::hide()
{
	mWindow->setVisible(false);
	state = MENU_IS_PASSIVE;
	mGui->setVisiblePointer(false);
}


void SceneMenu::createGui()
{
	MyGUI::VectorWidgetPtr widgets = MyGUI::LayoutManager::getInstance().loadLayout("main_menu.layout");
	mWindow = static_cast<MyGUI::Window*>(*widgets.begin());

	MyGUI::ButtonPtr button = static_cast<MyGUI::ButtonPtr>(mWindow->findWidget("ExitButton"));
	button->eventMouseButtonClick = MyGUI::newDelegate(this, &SceneMenu::exit); 

	button = static_cast<MyGUI::ButtonPtr>(mWindow->findWidget("ResumeButton"));
	button->eventMouseButtonClick = MyGUI::newDelegate(this, &SceneMenu::resume);

	button = static_cast<MyGUI::ButtonPtr>(mWindow->findWidget("Load"));
	button->eventMouseButtonClick = MyGUI::newDelegate(this, &SceneMenu::showFileSelectionDialog);
}

void SceneMenu::createChildren()
{
    mOpenTm = new tools::OpenSaveFileDialog();
	mOpenTm->eventEndDialog =  MyGUI::newDelegate(this, &SceneMenu::loadTelemetry);
}

void SceneMenu::menuToCenter()
{
	moveToCenter(mWindow);
	moveToCenter(mOpenTm->window());
}

void SceneMenu::exit(MyGUI::WidgetPtr widget)
{
    mApp->stop();
}

void SceneMenu::resume(MyGUI::WidgetPtr widget)
{
	mWindow->setVisible(false);
	state = MENU_IS_PASSIVE;
	mGui->setVisiblePointer(false);
}

void SceneMenu::showFileSelectionDialog(MyGUI::WidgetPtr widget)
{
	mWindow->setVisible(false);
	mOpenTm->show();
}

void SceneMenu::moveToCenter(MyGUI::WidgetPtr window)
{
	MyGUI::IntSize view = mGui->getViewSize();
	window->setPosition(view.width/2 - window->getWidth()/2, view.height/2 - window->getHeight()/2);
	MyGUI::ControllerFadeAlpha * controller = new MyGUI::ControllerFadeAlpha();
	window->setAlpha(0);
	MyGUI::ControllerManager::getInstance().addItem(window, controller);
}

#include "../Missile/Missile.h"
void SceneMenu::loadTelemetry(tools::Dialog* open_tm, bool)
{
	mIsLoadingTm = true;
	MyGUI::UString path = mOpenTm->getCurrentFolder() + "\\" + mOpenTm->getFileName();
	mMissile->loadTelemetry(path);
	mApp->moveCameraToBeginPos();
	mMissile->toBeginPos();
	mOpenTm->hide();
	mWindow->setVisible(true);
	mIsLoadingTm = false;
}

bool SceneMenu::isLoadingTm() const
{
	return mIsLoadingTm;
}