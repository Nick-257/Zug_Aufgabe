/////////////////////////////////////////////////////////////////////////////
// Name:        ZugWaggon.h
// Purpose:     Konfiguration eines Zuges.
// Author:      Niklas Dausch
// Modified by: -
// Created:     Oct/2020
// Copyright:   (c) 2020, Nilas Dausch
// Licence:     -
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>

class ZugWagon {
public:
    int WagonLaenge_;       // Laenge des Wagons.
    int AnzahlFenster_;     // Anzahl Fenster im Wagon.
    int AnzahlAchsen_;      // Anzahl Achsen am Wagon.
public:
    ZugWagon();
    // Erstellen eines WagonTyps in Abhaengigkeit der oben genannten Parameter.
    ZugWagon(int WagonLaenge_, int AnzahlFenster_, int AnzahlAchsen_);
    // Ausgabe des Zuges.
    void printWagon();
    // Abfrage der Characteristiken eines WagonTyps.
    int getLaenge();
    int getAchsen();
    int getFenster();
    // Status des Zuges ausgeben.
    std::string getStatus(std::vector<int> ZugKonfiguration_data);
    // Validitätscheck einer Nutzereingabe.
    bool valideEingabeWagenTyp(int Num_WagonTyp, int Num_WagonNummer);
    // Manuelle Konfiguration eines Zuges aufrufen.
    std::vector<int> ZugManuellBauen();
    // Abfrage des Speicherzeile der Konfiguration.
    unsigned getLoadLine();
    std::vector<std::string> getNamensVector();
    // Speichern einer manuellen Konfiguration.
    void ZugKonfigurationSpeichern(const std::vector<int>& ZugKonfiguration_data);
    bool ZugNameSchonVergeben(const std::string& ZugNamenEingabe);
    // Validitaetscheck der Nutzereingabe.
    bool valideZugNamenEingabe(const char& RichtigeEingabe);
    // Ausgabe der Endanzeige.
    void displayEnde();
};
