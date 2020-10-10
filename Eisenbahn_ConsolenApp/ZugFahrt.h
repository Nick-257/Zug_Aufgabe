#pragma once

#include "ZugWaggon.h"

class ZugFahrt : public ZugWagon
{
protected:
	std::string Zugfuehrer;
	std::vector<int> ZugKonfiguration_data;
public:
	ZugFahrt(std::string Zugfuehrer);
	std::string getStatus(std::vector<int> ZugKonfiguration_data);
	std::vector<int> ZugZusammenStellen();
	bool getValidUserInput(const std::string& input);
};

