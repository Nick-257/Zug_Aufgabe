#pragma once

#include <string>
#include <vector>

class ZugWagon {
public:
    int WagonLaenge_;
    int AnzahlFenster_;
    int AnzahlAchsen_;
public:
    ZugWagon();
    ZugWagon(int WagonLaenge_, int AnzahlFenster_, int AnzahlAchsen_);
    void printWagon();
    int getLaenge();
    int getAchsen();
    int getFenster();
    std::string getStatus(std::vector<int> ZugKonfiguration_data);
    bool valideEingabeWagenTyp(int Num_WagonTyp, int Num_WagonNummer);
    std::vector<int> ZugManuellBauen();
    unsigned getLoadLine();
    void ZugKonfigurationSpeichern(const std::vector<int>& ZugKonfiguration_data);
    bool valideZugNamenEingabe(const char& RichtigeEingabe);
    bool ZugNameSchonVergeben(const std::string& ZugNamenEingabe);
    std::vector<std::string> getNamensVector();
};
