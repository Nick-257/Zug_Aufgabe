#include "ZugFahrt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>

#include <chrono>
#include <thread>

using namespace std;

ZugFahrt::ZugFahrt(std::string Zugfuehrer){
    // Constructor
	cout << "\n\nHallo " << Zugfuehrer << "\n\n" << endl;
}

string ZugFahrt::getStatus(vector<int> ZugKonfiguration_data) {
    stringstream result;
    this->ZugKonfiguration_data = ZugKonfiguration_data;

    result << ZugWagon::getStatus(ZugKonfiguration_data) << endl;
    return result.str();
}

bool ZugFahrt::getValidUserInput(const string& input)
{
    if (input == "Ja" || input == "Nein") {
        return false;
    }
    else {
        cout << "Eingabe entweder Ja oder Nein: ";
        return true;
    }
}


vector<int> ZugFahrt::ZugZusammenStellen() {

    ifstream file("ZugName.txt");

    if (!file.is_open()) {
        file.close();
        vector<int> Zugkonfiguration;
        Zugkonfiguration = ZugWagon::ZugManuellBauen();
        return Zugkonfiguration;
    }
    else {
        cout << "Soll eine vorhandene Zugkonfiguration geladen werden? (Ja/Nein): ";
        string input;
        getline(cin, input);
        while (getValidUserInput(input)) {
            getline(cin, input);
        }
        
        if (input == "Ja" || input == "ja") {

            unsigned LoadLine = ZugWagon::getLoadLine();

            vector<int> ZugKonfig;
            vector<int> ZugKonfig_Part;
            int value;
            ifstream file("ZugKonfig.txt");

            if (!file.is_open()) {
                cout << "Datei existiert nicht!" << endl;
            }
            else {
                while (file >> value) {
                    ZugKonfig.push_back(value);
                }
                file.close();

                std::stack<int> sd;

                while (ZugKonfig.at(LoadLine) > 0)
                {
                    int digit = ZugKonfig.at(LoadLine) % 10;
                    ZugKonfig.at(LoadLine) /= 10;
                    sd.push(digit);
                }
                vector<int> Konfig;
                while (!sd.empty())
                {
                    int digit = sd.top();
                    sd.pop();
                    Konfig.push_back(digit);

                }
                ZugKonfig = Konfig;
                return ZugKonfig;
            }
        }
        else {
            vector<int> Zugkonfiguration;
            Zugkonfiguration = ZugWagon::ZugManuellBauen();
            return Zugkonfiguration;
        }

    }

}

bool ZugFahrt::valideEingabe(unsigned Num_PassagiereOut, unsigned Num_Belegung) {
    if (typeid(Num_PassagiereOut).name() == "unsigned") {
        return false;
    }
    else if (Num_PassagiereOut < 0) {
        std::cout << "Keine Valide Zahl!" << endl;
        return false;
    }
    else if ((Num_Belegung - Num_PassagiereOut) < 0) {
        std::cout << "Es koennen nicht mehr Passagiere aussteigen, als eingestiegen sind!" << endl;
        return false;
    }
    else {
        return true;
    }
}

void ZugFahrt::printFahrt() {
    unsigned MiliSeconds = rand() % 300 + 200; // 2 Minuten sind 120000 Milisekunden
    unsigned Steps = MiliSeconds / 10;
    double FahrZeit = (double)MiliSeconds / 1000;
    std::cout.precision(2);
    std::cout << "\n\nDie erwartete Fahrzeit betraegt " << fixed << FahrZeit << " Sekunden.\n" << endl;
    std::cout << " /\\                                            /\\" << endl << "| |";
    unsigned StepCounter = 0;
    while (StepCounter <= 10) {
        this_thread::sleep_for(chrono::milliseconds(Steps));
        std::cout << "____";
        StepCounter++;
    }
    std::cout << "| |" << endl;
}


void ZugFahrt::ZugFahrtModellierung(ZugFahrt F2, vector<int> ZugKonfiguration_data) {
    std::cout << "\n\nAn wie vielen Bahnhoefen haelt der Zug: ";
    unsigned AnzahlBahnhoefe;
    cin >> AnzahlBahnhoefe;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout << "\n\nAn wie vielen Bahnhoefen haelt der Zug (Bitte eine ganze Zahl angeben): ";
        cin >> AnzahlBahnhoefe;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "\nDer Zug haelt an " << AnzahlBahnhoefe << " Bahnhoefen.\n\nDer Zug verlaesst nun den Rangierbahnhof!" << endl;
    
    unsigned BahnhofNummer = 1;
    unsigned Belegung = 0;

    while (BahnhofNummer <= AnzahlBahnhoefe) {
        F2.printFahrt();
        cout << "\nDer naechste Bahnhof wurde erreicht!\n\n" << endl;
        string Aufgabe;
        while (Aufgabe != "Abfahrt" && Aufgabe != "Abf" && Aufgabe != "abf") {

            std::cout << "Bitte Keyword eingeben: Passagiere (P), Status (S), Belegung (B), Abfahrt (Abf), Abbruch (Abb)" << endl;
            cin >> Aufgabe;

            if (Aufgabe == "Status" || Aufgabe == "S" || Aufgabe == "s") {
                std::cout << F2.getStatus(ZugKonfiguration_data) << endl;
                std::cout << "\nIm Zug befinden sich momentan " << Belegung << " Passagiere.\n" << endl << endl;
                continue;
            }
            else if (Aufgabe == "Passagiere" || Aufgabe == "P" || Aufgabe == "p") {
                std::cout << "\n\nWie viele Passagiere sind eingestiegen: ";
                unsigned PassagiereIn = 0;
                unsigned PassagiereOut = 0;

                cin  >> PassagiereIn;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    std::cout << "Bitte wiederholen Sie die Anzahl an eingestiegenen Passagieren: ";
                    cin >> PassagiereIn;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                Belegung += PassagiereIn;
                if (Belegung != 0 && BahnhofNummer == 1) {
                    // Am ersten Bahnhof steigen nur Leute zu.
                    std::cout << "\nAm ersten Bahnhof koennen nur Leute zusteigen." << endl;
                    continue;
                }
                else if (Belegung == 0 || BahnhofNummer == 1) {
                    // Wenn keine Passagiere im Zug sind, kann auch niemand aussteigen!
                    std::cout << "\nKeine Passagiere im Zug, die aussteigen koennten!" << endl;
                    continue;
                }
                else {
                    std::cout << "\nWie viele Passagiere sind ausgestiegen: ";
                    cin >> PassagiereOut;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!cin.good()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        std::cout << "Bitte wiederholen Sie die Anzahl an ausgestiegenen Passagieren: ";
                        cin >> PassagiereOut;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    while (!valideEingabe(PassagiereOut, Belegung)) {
                        std::cout << "Bitte wiederholen Sie die Anzahl an ausgestiegenen Passagieren: ";
                        cin >> PassagiereOut;
                        while (!cin.good()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            std::cout << "Bitte wiederholen Sie die Anzahl an ausgestiegenen Passagieren: ";
                            cin >> PassagiereOut;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    Belegung -= PassagiereOut;
                }
                continue;
            }
            else if (Aufgabe == "Belegung" || Aufgabe == "B" || Aufgabe == "b") {
                std::cout << "\nIm Zug befinden sich momentan " << Belegung << " Passagiere.\n" << endl;
                continue;
            }
            else if (Aufgabe == "Abbruch" || Aufgabe == "Abb" || Aufgabe == "abb") {
                std::cout << "\nDer Zug stoppt an diesem Bahnhof!" << endl;
                BahnhofNummer = AnzahlBahnhoefe;
                break;
            }
        }
        std::cout << "Der Zug verlaesst den Bahnhof!" << endl;
        BahnhofNummer++;
    }
}
