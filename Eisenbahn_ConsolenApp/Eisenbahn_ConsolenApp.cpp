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
    // Diese Funktion gibt die Begrueßungsmeldung aus.
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
    // Diese Funktion gibt true zurueck, sobald der Bediener "Ja" eingibt, um den Prozess weiter fortzuführen.
    if (StartInput == "Nein") {
        return false;
    }
    else {
        return true;
    }
}

int main(int argc, const char* argv[]) {
    // Ausgabe der Begrueßung
    displayGreeting();

    // Namen des Lokfuehrers abfragen.
    string Name_Lokfuehrer;
    getline(cin, Name_Lokfuehrer);
    // Aufrufen des Constructors und somit wird eine neuen Zugfahrt angelegt.
    ZugFahrt F1(Name_Lokfuehrer);

    // Aufrufen der Konfiguration bzw. manuellen Zusammenstellung des Zuges.
    // Ausgabe eines Vectors bestehend aus einer Zahlenfolge, die sowohl die verwendeten Wagons als auch deren Reihung
    // abbildet.
    vector<int> ZugKonfiguration = F1.ZugZusammenStellen();

    // Wenn die Konfiguration korrekt erfolgt ist, kann die Zugfahrt gestartet werden,
    string StartInput = "Nein";
    while (!getStarted(StartInput)) {
        std::cout << "Die ausgewaehlte Konfiguration ist:\n\n " << endl
            << F1.getStatus(ZugKonfiguration) << "\n\n" << "Soll mit dieser Konfiguration gestartet werden? (Ja/Nein): ";
        getline(cin, StartInput);
        // Nur auf Nutzereingabe des Wortes "Ja" als Bestaetigung, kann die Schleife gebrochen werden und der Zug 
        // verlaesst somit den "Bahnhof". Andernfalls wird die Konfiguration des Zuges erneut ausgefuehrt.
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
    
    // Aufrufen der Zugfahrt Modellierung.
    F1.ZugFahrtModellierung(F1, ZugKonfiguration);
    // Letztmalige Ausgabe der Fahrstrecke nach erreichen des letzten Bahnhofes.
    F1.printFahrt();
    // Ausgabe der Verabschiedungsnachricht und darauf folgendes Ende des Programmes.
    F1.displayEnde();

    return 0;
}
