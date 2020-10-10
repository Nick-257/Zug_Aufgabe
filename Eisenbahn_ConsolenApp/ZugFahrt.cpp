#include "ZugFahrt.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>

using namespace std;

ZugFahrt::ZugFahrt(std::string Zugfuehrer){
	cout << "Hallo " << Zugfuehrer << endl;
}

string ZugFahrt::getStatus(vector<int> ZugKonfiguration_data) {
    stringstream result;
    this->ZugKonfiguration_data = ZugKonfiguration_data;

    result << ZugWagon::getStatus(ZugKonfiguration_data) << endl;
    return result.str();
}

bool ZugFahrt::getValidUserInput(const string& input)
{
    if (input == "Yes" || input == "no") {
        return false;
    }
    else {
        cout << "Eingabe  Yes oder no: ";
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
        cout << "Soll eine vorhandene Zugkonfiguration geladen werden? (Yes/no): ";
        string input;
        getline(cin, input);
        while (getValidUserInput(input)) {
            getline(cin, input);
        }
        
        if (input == "Yes" || input == "yes") {

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
                cout << "Folgende Konfiguration wird verwendet: " << ZugKonfig.at(LoadLine) << endl;

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
