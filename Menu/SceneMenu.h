#pragma once

namespace tools{
    class OpenSaveFileDialog;
	class Dialog;
}

class Missile;
class KYMyStar;

#include <MyGUI/MyGUI.h>

class SceneMenu
{
public:
	enum State{
		MENU_IS_ACTIVE,
		MENU_IS_PASSIVE
	};
	SceneMenu(KYMyStar* mApp, MyGUI::Gui* mGui, Missile* mMissile);
	~SceneMenu();
	bool isActive() const;
	bool isPassive() const;
	bool isLoadingTm() const;
	void show();
	void hide();
private:
	void createGui();
	void createChildren();
	void menuToCenter();
	void exit(MyGUI::WidgetPtr widget);
	void resume(MyGUI::WidgetPtr widget);
	void moveToCenter(MyGUI::WidgetPtr window);
	void showFileSelectionDialog(MyGUI::WidgetPtr widget);
	void loadTelemetry(tools::Dialog* mOpenTm, bool);
private:
	MyGUI::Gui* mGui;
	tools::OpenSaveFileDialog* mOpenTm;
	State state;
	MyGUI::Window* mWindow;
	KYMyStar* mApp;
	Missile* mMissile;
	bool mIsLoadingTm;
};

