// Eisenbahn_ConsolenApp.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator> 
#include <sstream>

#include <chrono>
#include <thread>

#include <limits> // cin check

#include <stdlib.h> //rand

#include <stack> // convert int to digits

#include <limits>
#include <typeinfo>

#include "ZugWaggon.h"
#include "ZugFahrt.h"

using namespace std;

void displayGreeting() {
    std::cout << "\n\nHerzlich Willkommen zum Zug-Konfigurator.\n\n\n" << endl
        << "*                                                  ***** \n"
        "*                                                    **** \n"
        "* __________   __________   __________          _____  ***\n"
        "*|          | |          | |          |  ___.___|   |___\\/_,,\n"
        "*|__________| |__________| |__________| |_______||___________|\n"
        "* OO      OO   OO      OO   OO    OO     OO  OO ||  OO     OO\n\n\n" << endl
        << "\n\nBitte den Namen des Zugfuhrers angeben: ";
}

bool getStarted(const string& StartInput) {
    if (StartInput == "Nein") {
        return false;
    }
    else {
        return true;
    }
}

int main(int argc, const char* argv[]) {
    displayGreeting();

    string Name_Lokfuehrer;
    getline(cin, Name_Lokfuehrer);
    ZugFahrt F1(Name_Lokfuehrer);

    vector<int> ZugKonfiguration = F1.ZugZusammenStellen();


    string StartInput = "Nein";
    while (!getStarted(StartInput)) {
        std::cout << "Die ausgewaehlte Konfiguration ist:\n\n " << endl
            << F1.getStatus(ZugKonfiguration) << "\n\n" << "Soll mit dieser Konfiguration gestartet werden? (Ja/Nein): ";
        getline(cin, StartInput);
        while (F1.getValidUserInput(StartInput)) {
            getline(cin, StartInput);
        }
        if (StartInput == "Ja") {
            break;
        }
        else {
            vector<int> ZugKonfiguration = F1.ZugZusammenStellen();
            continue;
        }
    }
        
    F1.ZugFahrtModellierung(F1, ZugKonfiguration);
    F1.printFahrt();
    F1.displayEnde();

    return 0;
}
