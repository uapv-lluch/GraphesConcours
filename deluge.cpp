#include <utility>

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

struct arete {
    double poids;
    int sommetDepart;
    int sommetArrivee;

    bool operator <(const arete & areteObj) const {
        return poids < areteObj.poids;
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

bool isCycle(int sommet, list<int> adj[], vector<bool> visited, int parent) {
    for (auto & it : adj[sommet]) {
        if (!visited[it]) {
            if (isCycle(it, adj, visited, sommet)) {
                return true;
            }
        } else if(it != parent) {
            return true;
        }
    }
    return false;
}


set<arete> kruskal(int n, list<arete> e) {
    set<int> sommets;
    set<arete> aretes;
    vector<bool> visited(n, false);
    list<int> adj[n];
    arete firstArc = *e.begin();
    aretes.insert(firstArc);
    sommets.insert(firstArc.sommetDepart);
    sommets.insert(firstArc.sommetArrivee);
    visited[firstArc.sommetDepart] = true;
    visited[firstArc.sommetArrivee] = true;
    adj[firstArc.sommetDepart].push_back(firstArc.sommetArrivee);
    adj[firstArc.sommetArrivee].push_back(firstArc.sommetDepart);
    while (sommets.size() < n) {
        for (auto & it : e) {
            if (aretes.find(it) == aretes.end() // si l'arete n'a pas ete choisie
                // si l'arete ne cree pas de cycle
                && visited[it.sommetDepart]
                && !visited[it.sommetArrivee]
                && !isCycle(it.sommetArrivee, adj, visited, -1)) {
                sommets.insert(it.sommetArrivee);
                visited[it.sommetArrivee] = true;
                adj[it.sommetDepart].push_back(it.sommetArrivee);
                adj[it.sommetArrivee].push_back(it.sommetDepart);
                aretes.insert(it);
                break;
            }
        }
    }
    return aretes;
}

double kruskalPoids(int n, list<arete> e, bool rounded=false) {
    double poids = 0;
    set<arete> arbre = kruskal(n, std::move(e));
    for (auto it : arbre) {
        poids += it.poids;
    }
    if (rounded) {
        return (int)poids;
    } else {
        return poids;
    }
}


int main() {
    ifstream file("../resources/deluge2.txt", ios::in);
    if (file) {
        string line;
        int n = 0;
        int nbSommets = 0;
        vector<vector<double>> sommets;
        vector<vector<double>> arcsMatrix;
        list<arete> aretesList; // { poids , sommetDepart, sommetArrivee }
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
                    aretesList.push_back({poids, i, j});
                }
            }
        }
        aretesList.sort();
        set<arete> arbre = kruskal(nbSommets, aretesList);
        double poidsArbre = kruskalPoids(nbSommets, aretesList, true);
        cout << poidsArbre << endl;
    } else {
        cerr << "Error file";
        return -1;
    }
    return 0;
}