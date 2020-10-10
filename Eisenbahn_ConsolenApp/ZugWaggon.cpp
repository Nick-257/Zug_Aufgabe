#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include <chrono>
#include <thread>

#include "ZugWaggon.h"

using namespace std;

ZugWagon::ZugWagon() {
    cout << "Neue Zugfahrt wird erstellt!" << endl;
}

ZugWagon::ZugWagon(int WagonLaenge_, int AnzahlFenster_, int AnzahlAchsen_) {
        this->WagonLaenge_ = WagonLaenge_;
        this->AnzahlFenster_ = AnzahlFenster_;
        this->AnzahlAchsen_ = AnzahlAchsen_;
    }

//void ZugWagon::WagonsInitialisiern() {
//    ZugWagon Wagon1(2, 4, 2);
//    ZugWagon Wagon2(3, 6, 3);
//    ZugWagon Wagon3(4, 8, 4);
//    Wagon3.printWagon();
//
//}

void ZugWagon::printWagon() {
    cout << "WagonLaenge: " << WagonLaenge_ <<
        " AnzahlFenster: " << AnzahlFenster_ <<
        " AnzahlAchsen: " << AnzahlAchsen_ << endl;
}

int ZugWagon::getLaenge() { return WagonLaenge_; }
int ZugWagon::getAchsen() { return AnzahlAchsen_; }
int ZugWagon::getFenster() { return AnzahlFenster_; }



string ZugWagon::getStatus(vector<int> ZugKonfiguration_data) {

    stringstream result;

    ZugWagon Wagon1(2, 4, 2);
    ZugWagon Wagon2(3, 6, 3);
    ZugWagon Wagon3(4, 8, 4);

    int Gesamtlaenge = 0;
    int Fensteranzahl = 0;
    int Achsenzahl = 0;
    vector<string> ZugAufbau;
    ZugAufbau.push_back("Lok");
    int Wagennummer = 1;
    for (unsigned wagon = 0; wagon < ZugKonfiguration_data.size(); wagon++) {
        if (ZugKonfiguration_data.at(wagon) == 1) {
            Fensteranzahl += Wagon1.getFenster();
            Achsenzahl += Wagon1.getAchsen();
            Gesamtlaenge += Wagon1.getLaenge();
            string WagonKonfig = ("+ Wagon-" + std::to_string(Wagennummer));
            WagonKonfig +=  "-Typ-1";
            ZugAufbau.push_back(WagonKonfig);
            Wagennummer++;
        }
        else if (ZugKonfiguration_data.at(wagon) == 2) {
            Fensteranzahl += Wagon2.getFenster();
            Achsenzahl += Wagon2.getAchsen();
            Gesamtlaenge += Wagon2.getLaenge();
            string WagonKonfig = ("+ Wagon-" + std::to_string(Wagennummer));
            WagonKonfig += "-Typ-2";
            ZugAufbau.push_back(WagonKonfig);
            Wagennummer++;
        }
        else if (ZugKonfiguration_data.at(wagon) == 3) {
            Fensteranzahl += Wagon3.getFenster();
            Achsenzahl += Wagon3.getAchsen();
            Gesamtlaenge += Wagon3.getLaenge();
            string WagonKonfig = ("+ Wagon-" + std::to_string(Wagennummer));
            WagonKonfig += "-Typ-3";
            ZugAufbau.push_back(WagonKonfig);
            Wagennummer++;
        }
        else {
            continue;
        }
    }
    result << "Der Zug hat folgenden Aufbau:" << endl;
    std::copy(ZugAufbau.begin(), ZugAufbau.end(), std::ostream_iterator<std::string>(result, " "));
    result << "\n\n" << "Der Zug hat " << Fensteranzahl << " Fenster." << endl;
    result << "Der Zug hat " << Achsenzahl << " Achsen." << endl;
    result << "Der Zug ist " << Gesamtlaenge << " Meter lang." << "\n";

    return result.str();
}

bool ZugWagon::valideEingabeWagenTyp(int Num_WagonTyp, int Num_WagonNummer) {
    if (Num_WagonTyp <= 0) {
        cout << "Keine valide Angabe" << endl;
        return false;
    }
    else if (Num_WagonTyp > 3) {
        cout << "Keine valide Angabe!" << endl;
        return false;
    }
    else {
        return true;
    }
}

vector<int> ZugWagon::ZugManuellBauen() {
    string SollKonfigGespeichertWerden = "Nein";
    while (SollKonfigGespeichertWerden == "Nein") {
        ZugWagon Wagon1(2, 4, 2);
        ZugWagon Wagon2(3, 6, 3);
        ZugWagon Wagon3(4, 8, 4);

        std::cout << "\nAus wie vielen Wagons soll der Zug bestehen: ";
        int WaggonAnzahl;
        cin >> WaggonAnzahl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "\nAus wie vielen Wagons soll der Zug bestehen: (Bitte eine ganze Zahl angeben): ";
            cin >> WaggonAnzahl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        std::cout << "Der Zug wird aus " << WaggonAnzahl << " Wagonteilen bestehen.\n\n" << endl;

        std::cout << "Folgende WagonTypen stehen zur Auswahl:\n\n" << "WagonTyp 1: \nLaenge: 2 Meter, \nFenster: 4, \nAchsen: 2\n" <<
            "\n\nWagonTyp 2: \nLaenge: 3 Meter, \nFenster: 6, \nAchsen: 3\n" <<
            "\n\nWagonTyp 3: \nLaenge: 4 Meter, \nFenster: 8, \nAchsen: 4\n\n\n";

        int WagonNummer = 1;
        vector<int> ZugKonfiguration;
        cout << "Bitte fuer alle Wagons im Folgenden den Typ festlegen!\n" << endl;
        while (WagonNummer <= WaggonAnzahl) {
            int WagonTyp;
            cout << "Bitte fuer Wagon " << WagonNummer << " den WagonTyp eingeben (1, 2 oder 3): ";
            cin >> WagonTyp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (!cin.good()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Bitte korrigieren Sie die Eingabe (1, 2 oder 3): ";
                cin >> WagonTyp;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            while (!valideEingabeWagenTyp(WagonTyp, WagonNummer)) {
                cout << "Bitte korrigieren Sie fur Wagon " << WagonNummer << " die Eingabe des WagonTyp (1, 2 oder 3): ";
                cin >> WagonTyp;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            WagonNummer++;
            ZugKonfiguration.push_back(WagonTyp);
        }
        cout << "\nSoll die Konfiguration gespeichert werden? (Ja/Nein): ";
        getline(cin, SollKonfigGespeichertWerden);
        if (SollKonfigGespeichertWerden == "Ja" || SollKonfigGespeichertWerden == "ja") {
            ZugWagon::ZugKonfigurationSpeichern(ZugKonfiguration);
            return ZugKonfiguration;
        }
        else if (SollKonfigGespeichertWerden == "Nein" || SollKonfigGespeichertWerden == "nein") {
            cout << "\nSoll der Prozess ohne Speichern fortgesetzt werden? (Ja/Nein): ";
            string SollFortgesetztWerden;
            getline(cin, SollFortgesetztWerden);
            if (SollFortgesetztWerden == "Ja" || SollFortgesetztWerden == "ja") {
                return ZugKonfiguration;
            }
            else {
                continue;
            }
        }
        else {
            cout << "\nFalsche Eingabe. Neustart der Konfiguration.\n" << endl;
            this_thread::sleep_for(chrono::milliseconds(15000));
            continue;
        }
    } 
}

bool ZugWagon::valideZugNamenEingabe(const char& RichtigeEingabe_data) {
    if (RichtigeEingabe_data != 'Y') {
        return false;
    }
    else {
        return true;
    }
}

vector<string> ZugWagon::getNamensVector() {
    ifstream file("ZugName.txt");
    string line;
    vector<string> ZugNamen;
    while (!file.eof()) {
        getline(file, line);
        ZugNamen.push_back(line);
    }
    file.close();
    return ZugNamen;
}

unsigned ZugWagon::getLoadLine() {
    ifstream file("ZugName.txt");
    string line;
    int counter_lines = 0;
    vector<string> ZugNamen = getNamensVector();
    cout << "Verfuegbare Zugkonfigurationen: " << endl;
    for (unsigned i = 0; i < ZugNamen.size(); i++) {
        cout << ZugNamen.at(i) << endl;
    }

    cout << "Welche Konfiguration soll verwendet werden: ";
    string KonfigToLoad;
    getline(std::cin, KonfigToLoad);
    unsigned loadLine;
    char RichtigeEingabe = 'n';

    while (!valideZugNamenEingabe(RichtigeEingabe)) {

        for (unsigned i = 0; i < ZugNamen.size(); i++) {
            if (KonfigToLoad == ZugNamen.at(i)) {
                loadLine = i;
                RichtigeEingabe = 'Y';
                return loadLine;
            }
            else {
                continue;
            }
        }
        cout << "Diese Konfiguration existiert nicht. Bitte Eingabe korrigieren: ";
        getline(std::cin, KonfigToLoad);
    }
}

bool ZugWagon::ZugNameSchonVergeben(const string& ZugNamenEingabe) {
    vector<string> ZugNamen = getNamensVector();

    for (unsigned i = 0; i < ZugNamen.size(); i++) {
        if (ZugNamenEingabe == ZugNamen.at(i)) {
            return true;
        }
        else {
            continue;
        }
    } 
    return false;
}

void ZugWagon::ZugKonfigurationSpeichern(const vector<int>& ZugKonfiguration_data) {
    cout << "Der Zug ist fertig zusammengestellt! Bitte geben Sie der Zug Konfiguration einen Namen: " << endl;
    string name;
    getline(std::cin, name);
    ifstream fileName("ZugName.txt");
    if (fileName.is_open()) {
        while (ZugNameSchonVergeben(name)) {
            cout << "Der Name ist schon vergeben! Bereits verwendete Namen:\n" << endl;
            vector<string> ZugNamen = getNamensVector();
            for (unsigned i = 0; i < ZugNamen.size(); i++) {
                cout << ZugNamen.at(i) << endl;
            }
            cout << "Bitte neuen Namen waehlen: ";
            cin.clear();
            getline(std::cin, name);
        }
    } else {
        int ZahlPuffer = 0;
    }

    cout << "Die Konfiguration wurde unter dem Namen " << name << " gespeichert!\n" << endl;
    std::ofstream ZugNameTxt("ZugName.txt", std::ios_base::app);
    ZugNameTxt << name << endl;
    ZugNameTxt.close();

    std::ofstream ZugKonfigTxt("ZugKonfig.txt", std::ios_base::app);
    for (vector<int>::const_iterator i = ZugKonfiguration_data.begin(); i != ZugKonfiguration_data.end(); ++i) {
        ZugKonfigTxt << *i;
    }
    ZugKonfigTxt << endl;
    ZugKonfigTxt.close();
}


void ZugWagon::displayEnde() {
    std::cout << "\n\n\nDer letzte Bahnhof wurde erreicht, alle Passagiere steigen hier aus!" << endl
    << "\n\n\nVielen Dank und bis zum naechsten Mal!" << endl
    << "\nDas Programm endet automatisch in 30 Sekunden." << endl;
    this_thread::sleep_for(chrono::milliseconds(30000));
}