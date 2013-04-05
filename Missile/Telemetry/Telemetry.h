#pragma once
#include "MissileState.h"
#include <vector>

class Telemetry
{
private:
	std::vector<MissileState> telemetry;
	mutable int current_pos;
	MissileState start_pos;
	mutable int speed;
	static const int SPEED;
public:
	Telemetry();

	void loadTelemetry(const std::string& path);

	const MissileState& move()    const;
	const MissileState& toBegin() const;

	void incSpeed();
	void decSpeed();
	void stop();

	int getCurrentPos() const;
};