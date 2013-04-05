#include "Telemetry.h"
#include <OGRE/Ogre.h>

const int Telemetry::SPEED = 1;

Telemetry::Telemetry():
    current_pos(0),
	speed(0)
{
}

#include <fstream>
void Telemetry::loadTelemetry(const std::string& path)
{
	//Ogre::LogManager::getSingleton().logMessage("Hello from file loading " + path);
	std::ifstream in(path, std::ios::in);
	if(!in.is_open()) return;
	telemetry.clear();
	while(!in.eof()){
		std::string line;
		std::getline(in, line);
		if(!line.empty()) telemetry.push_back(MissileState(line));
	}
	in.close();
}

const MissileState& Telemetry::move() const
{
	if(telemetry.empty()) return start_pos;
	int temp = current_pos;
	current_pos += speed;

	if(temp < 0){
		if(speed < 0) current_pos = temp;
		return telemetry[0];
	}
	if(temp >= telemetry.size() - 1){
		if(speed > 0) current_pos = temp;
		return telemetry[telemetry.size() - 1];
	}
	return telemetry[temp];
}

const MissileState& Telemetry::toBegin() const
{
	current_pos = 0; 
	speed = 0;
	if(telemetry.empty()) return start_pos;
	return telemetry[0];
}

void Telemetry::incSpeed()
{
	speed += SPEED;
}

void Telemetry::decSpeed()
{
	speed -= SPEED;
}

void Telemetry::stop()
{
	speed = 0;
}

int Telemetry::getCurrentPos() const
{
	return current_pos;
}