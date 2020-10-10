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

#include "ZugWaggon.h"
#include "ZugFahrt.h"

using namespace std;



#include <typeinfo>
bool valideEingabe(int Num_PassagiereOut, int Num_Belegung) {
    if (typeid(Num_PassagiereOut).name() == "int") {
        return false;
    }
    else if (Num_PassagiereOut < 0) {
        std::cout << "Keine Valide Zahl!" << endl;
        return false;
    }
    else if ((Num_Belegung - Num_PassagiereOut) < 0) {
        std::cout << "Es koennen nicht mehr Passagiere aussteigen, als eingestiegen sind!" << endl;
        return false;
    } else {
        return true;
    }
}


void ZugFahrtModellierung(ZugFahrt F2, vector<int> ZugKonfiguration_data) {
    std::cout << "\n\nAn wie vielen Bahnhoefen haelt der Zug: ";
    int AnzahlBahnhoefe;
    cin >> AnzahlBahnhoefe;
    while (!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout << "\n\nAn wie vielen Bahnhoefen haelt der Zug (Bitte eine ganze Zahl angeben): ";
        cin >> AnzahlBahnhoefe;
    }

    int BahnhofNummer = 1;
    int Belegung = 0;

    while (BahnhofNummer <= AnzahlBahnhoefe) {
        int MiliSeconds = rand() % 120000 + 200; // 2 Minuten sind 120000 Milisekunden
        int Steps = MiliSeconds / 10;
        double FahrZeit = (double)MiliSeconds / 1000;
        std::cout.precision(2);
        std::cout << "Die erwartete Fahrzeit betraegt " << fixed <<  FahrZeit << " Sekunden." << endl;
        std::cout << " /\\                                            /\\" << endl << "| |";
        int StepCounter = 0;
        while (StepCounter <= 10) {
            this_thread::sleep_for(chrono::milliseconds(Steps));
            std::cout << "____";
            StepCounter++;
        }
        std::cout << "| |" << endl << "\nDer naechste Bahnhof wurde erreicht!\n\n" << endl;

        string Aufgabe;
        while (Aufgabe != "Abfahrt" && Aufgabe != "Abf" && Aufgabe != "abf") {

            std::cout << "Bitte Keyword eingeben: Passagiere (P), Status (S), Belegung (B), Abfahrt (Abf), Abbruch (Abb)" << endl;
            cin >> Aufgabe;

            if (Aufgabe == "Status" || Aufgabe == "S" || Aufgabe == "s") {
                std::cout << F2.getStatus(ZugKonfiguration_data) << endl;
                std::cout << "Im Zug befinden sich momentan " << Belegung << " Passagiere." << endl << endl;
                continue;
            }
            else if (Aufgabe == "Passagiere" || Aufgabe == "P" || Aufgabe == "p") {
                std::cout << "Wie viele Passagiere sind eingestiegen: ";
                int PassagiereIn = 0;
                int PassagiereOut = 0;
                cin >> PassagiereIn;
                while (!cin.good()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> PassagiereIn;
                }
                Belegung += PassagiereIn;
                if (Belegung == 0 || BahnhofNummer == 1) {
                    // Wenn keine Passagiere im Zug sind, kann auch niemand aussteigen!
                    std::cout << "Keine Passagiere im Zug, die aussteigen koennten!" << endl;
                    continue;
                }
                else {
                    std::cout << "Wie viele Passagiere sind ausgestiegen: ";
                    cin >> PassagiereOut;
                    while (!cin.good()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        std::cout << "Bitte wiederholen Sie die Anzahl an ausgestiegenen Passagieren: ";
                        cin >> PassagiereOut;
                    }
                    while (!valideEingabe(PassagiereOut, Belegung)) {
                        std::cout << "Bitte wiederholen Sie die Anzahl an ausgestiegenen Passagieren: ";
                        cin >> PassagiereOut;
                        while (!cin.good()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            std::cout << "Bitte wiederholen Sie die Anzahl an ausgestiegenen Passagieren: ";
                            cin >> PassagiereOut;
                        }
                    }
                    Belegung -= PassagiereOut;
                }
                continue;
            }
            else if (Aufgabe == "Belegung" || Aufgabe == "B" || Aufgabe == "b") {
                std::cout << "Im Zug befinden sich momentan " << Belegung << " Passagiere" << endl;
                continue;
            }
            else if (Aufgabe == "Abbruch" || Aufgabe == "Abb" || Aufgabe == "abb") {
                std::cout << "Der Zug stoppt an diesem Bahnhof!" << endl;
                BahnhofNummer = AnzahlBahnhoefe;
                break;
            }
        }
        std::cout << "Der Zug verlaesst den Bahnhof!" << endl;
        BahnhofNummer++;
    }
}

bool getStarted(const string& StartInput) {
    if (StartInput == "no") {
        return false;
    }
    else {
        return true;
    }
}

int main(int argc, const char* argv[]) {


    // Neue Zugfahrt anlegen.
    std::cout << "Bitte den Namen des Zugfuhrers angeben: ";
    string Name_Lokfuehrer;
    getline(cin, Name_Lokfuehrer);
    ZugFahrt F1(Name_Lokfuehrer);

    vector<int> ZugKonfiguration = F1.ZugZusammenStellen();


    string StartInput = "no";
    while (!getStarted(StartInput)) {
        std::cout << "Die ausgewaehlte Konfiguration ist:\n\n " << endl
            << F1.getStatus(ZugKonfiguration) << "\n\n" << "Soll mit dieser Konfiguration gestartet werden? (Yes/no): ";
        getline(cin, StartInput);
        while (F1.getValidUserInput(StartInput)) {
            getline(cin, StartInput);
        }
        if (StartInput == "Yes") {
            break;
        }
        else {
            vector<int> ZugKonfiguration = F1.ZugZusammenStellen();
            continue;
        }
    }
        
    ZugFahrtModellierung(F1, ZugKonfiguration);

    std::cout << "\n\n\nDer letzte Bahnhof wurde erreicht, alle Passagiere steigen hier aus!" << endl;
    std::cout << "\n\n\nVielen Dank und bis zum naechsten mal!" << endl;
    std::cout << "\nDas Programm endet automatisch in 30 Sekunden." << endl;
    this_thread::sleep_for(chrono::milliseconds(30000));
     

    return 0;

}
