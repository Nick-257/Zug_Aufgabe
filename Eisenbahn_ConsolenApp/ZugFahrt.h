/////////////////////////////////////////////////////////////////////////////
// Name:        ZugFahrt.h
// Purpose:     Modellierung einer Zugfahrt.
// Author:      Niklas Dausch
// Modified by: -
// Created:     Oct/2020
// Copyright:   (c) 2020, Nilas Dausch
// Licence:     -
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ZugWaggon.h"

class ZugFahrt : public ZugWagon
{
protected:
	std::string Zugfuehrer;						// Name des Zugfuehrers als string
	std::vector<int> ZugKonfiguration_data;		// Vector aus int um die Konfiguration des Zuges zu uebernehmen.
public:
	// ZugFahrt anlegen.
	ZugFahrt(std::string Zugfuehrer);
	// Status des Zuges abfragen.
	std::string getStatus(std::vector<int> ZugKonfiguration_data);
	// Zug manuell konfigurieren.
	std::vector<int> ZugZusammenStellen();
	// Eingabe des Nutzers auf Fehler pruefen.
	bool getValidUserInput(const std::string& input);
	bool valideEingabe(unsigned Num_PassagiereOut, unsigned Num_Belegung);
	// Zugfahrt modellieren.
	void ZugFahrtModellierung(ZugFahrt F2, std::vector<int> ZugKonfiguration_data);
	// Ausgabe der Fahrstrecke.
	void printFahrt();
};

