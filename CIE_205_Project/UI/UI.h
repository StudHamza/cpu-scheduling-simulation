#pragma once
#include "Mode.h"

class UI
{
private:
	mode Mode;
	void setMode() {}	//cin mode
public:
	UI(mode m) { Mode = m; }
	UI() { }
	void Start() { setMode(); }	//Write output logic
	void End(){}
	
	
};
