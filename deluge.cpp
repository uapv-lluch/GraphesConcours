#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector <string> result;
    size_t begin = 0;
    size_t index = str.find(delimiter);
    while (index != string::npos) {
        string sub = str.substr(begin, index-begin);
        result.push_back(sub);
        begin = index+1;
        index = str.find(delimiter, begin);
    }
    string sub = str.substr(begin, str.find('\n')-begin);
    result.push_back(sub);
    return result;
}

int main() {
    ifstream file("../resources/deluge.txt", ios::in);
    if (file) {
        string line;
        int n = 0;
        int nbSommets = 0;
        vector<vector<double>> sommets;
        vector<vector<double>> arcs;
        while (getline(file, line)) {
            // Lisez les données ici et effectuez votre traitement ici
            if (n == 0) { // Nombre de sommets
                nbSommets = stoi(line);
                sommets.resize(nbSommets, vector<double >(2));
                arcs.resize(nbSommets, vector<double>(nbSommets));
            } else { // Coordonnées
                vector<string> coordStr = split(line, ' ');
                sommets[n-1][0] = stod(coordStr[0]);
                sommets[n-1][1] = stod(coordStr[1]);
            }
            ++n;
        }
        // Vous pouvez aussi effectuer votre traitement une fois que vous avez lu toutes les données.
        for (int i = 0 ; i < sommets.size() ; ++i) {
            for (int j = 0 ; j < sommets.size() ; ++j) {
                arcs[i][j] = sqrt(pow((sommets[j][0] - sommets[i][0]), 2) + pow((sommets[j][1] - sommets[i][1]), 2));
                cout << fixed << setprecision(0) << setw(6) << arcs[i][j] << ' ';
            }
            cout << endl;
        }

        // TODO : Implémenter l'algo d'arbre couvrant minimum
    } else {
        cerr << "Error file";
        return -1;
    }
    return 0;
}