#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <list>
#include <set>
#include <unordered_set>

using namespace std;

struct arc {
    double poids;
    int sommetDepart;
    int sommetArrivee;

    bool operator <(const arc & arcObj) const {
        return poids < arcObj.poids;
    }
};

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

bool isCycle(set<arc> arcs, arc a) {
    // TODO
    return true;
}

void prim(int n) {
    vector<int> A(n);
    A.push_back(0);
    int i = 1;
    while (i != n) {

        ++i;
    }
}

unordered_set<int> kruskal(int n, list<arc> e) {
    unordered_set<int> A;
    set<arc> arcs;
    vector<int> departs;
    A.insert(0);

    for (list<arc>::iterator it = e.begin() ; it != e.end() ; ++it) {
        if (arcs.find(*it) == arcs.end() // si l'arete n'a pas ete choisie
            && A.find(it->sommetArrivee) == A.end()) { // si l'arete ne cree pas de cycle A REFAIRE
            A.insert(it->sommetArrivee);
            arcs.insert(*it);
            departs.push_back(it->sommetDepart);
            cout << setw(3) << it->sommetArrivee << ' ';
        }
    }
    cout << endl;
    for (int i = 0 ; i < departs.size() ; ++i) {
        cout << setw(3) << departs[i] << ' ';
    }
    double sum = 0;
    for (set<arc>::iterator it = arcs.begin() ; it != arcs.end() ; ++it) {
        sum += it->poids;
    }
    cout << endl << sum << endl;
    return A;
}

double kruskalPoids(int n, list<arc> e) {
    unordered_set<int> A;
//    A.insert(0);
    double poids = 0;
//    int i = 1;
    for (list<arc>::iterator it = e.begin() ; it != e.end() ; ++it) {
        if (it->sommetDepart != it->sommetArrivee && A.find(it->sommetArrivee) == A.end()) {
            A.insert(it->sommetArrivee);
            poids += it->poids;
        }
    }
    return poids;
}


int main() {
    ifstream file("../resources/deluge2.txt", ios::in);
    if (file) {
        string line;
        int n = 0;
        int nbSommets = 0;
        vector<vector<double>> sommets;
        vector<vector<double>> arcsMatrix;
        list<arc> arcsList; // { poids , sommetDepart, sommetArrivee }
        while (getline(file, line)) {
            // Lisez les données ici et effectuez votre traitement ici
            if (n == 0) { // Nombre de sommets
                nbSommets = stoi(line);
                sommets.resize(nbSommets, vector<double >(2));
                arcsMatrix.resize(nbSommets, vector<double>(nbSommets));
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
                double poids = sqrt(pow((sommets[j][0] - sommets[i][0]), 2) + pow((sommets[j][1] - sommets[i][1]), 2));
                arcsMatrix[i][j] = poids;
                if (i != j) {
                    arcsList.push_back({poids, i, j});
                }
//                cout << fixed << setprecision(0) << setw(6) << arcsMatrix[i][j] << ' ';
            }
//            cout << endl;
        }
        arcsList.sort();

        /*for (list<arc>::iterator it = arcsList.begin() ; it != arcsList.end() ; ++it) {
            cout << it->poids << ' ' << it->sommetDepart << ' ' << it->sommetArrivee << endl;
        }*/
        cout << endl;
        unordered_set<int> arbre = kruskal(nbSommets, arcsList);
        double poidsArbre = kruskalPoids(nbSommets, arcsList);
        cout << poidsArbre << endl;
        /*for (unordered_set<int>::iterator it = arbre.begin() ; it != arbre.end() ; ++it) {
            cout << *it << ' ';
        }*/
    } else {
        cerr << "Error file";
        return -1;
    }
    return 0;
}