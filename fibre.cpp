/*******
 * Read input from cin
 * Use cout << ... to output your result to STDOUT.
 * Use cerr << ... to output debugging information to STDERR
 * ***/
#include <iostream>
#include <limits>
#include <sstream>

#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>

#include "exercise.hpp"

using namespace std;

struct arete {
    double poids;
    int sommetDepart;
    int sommetArrivee;

    bool operator<(const arete & areteObj) const {
        return poids < areteObj.poids;
    }
    bool operator==(const arete & areteObj) const {
        return (sommetDepart == areteObj.sommetDepart && sommetArrivee == areteObj.sommetArrivee && poids == areteObj.poids);
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

vector<arete> kruskal(int n, list<arete> e) {
    set<int> sommets;
    vector<arete> aretes;
    vector<bool> visited(n, false);
    list<int> adj[n];
    arete firstArc = *e.begin();
    aretes.push_back(firstArc);
    sommets.insert(firstArc.sommetDepart);
    sommets.insert(firstArc.sommetArrivee);
    visited[firstArc.sommetDepart] = true;
    visited[firstArc.sommetArrivee] = true;
    adj[firstArc.sommetDepart].push_back(firstArc.sommetArrivee);
    adj[firstArc.sommetArrivee].push_back(firstArc.sommetDepart);
    while (sommets.size() < n) {
        for (auto & it : e) {
            if (find(aretes.begin(), aretes.end(), it) == aretes.end() // si l'arete n'a pas ete choisie
                // si l'arete ne cree pas de cycle
                && visited[it.sommetDepart]
                && !visited[it.sommetArrivee]
                && !isCycle(it.sommetArrivee, adj, visited, -1)) {
                sommets.insert(it.sommetArrivee);
                visited[it.sommetArrivee] = true;
                adj[it.sommetDepart].push_back(it.sommetArrivee);
                adj[it.sommetArrivee].push_back(it.sommetDepart);
                aretes.push_back(it);
                break;
            }
        }
    }
    return aretes;
}

double kruskalPoids(int n, list<arete> e, bool rounded=false) {
    double poids = 0;
    vector<arete> arbre = kruskal(n, std::move(e));
    for (auto it : arbre) {
        poids += it.poids;
    }
    if (rounded) {
        return (int)poids;
    } else {
        return poids;
    }
}

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

void ContestExerciseImpl::main() {
    std::string line;
    int n = 0;
    int nbSommets = 0;
    vector<vector<double>> sommets;
    list<arete> aretesList; // { poids , sommetDepart, sommetArrivee }
    while (std::getline(std::cin, line))
    {
        /*Lisez les données ici et effectuez votre traitement ici */
        if (n == 0) { // Nombre de sommets
            nbSommets = stoi(line);
            sommets.resize(nbSommets, vector<double >(2));
        } else { // Coordonnées
            vector<string> coordStr = split(line, ' ');
            sommets[n-1][0] = stod(coordStr[0]);
            sommets[n-1][1] = stod(coordStr[1]);
        }
        ++n;
    }
    /* Vous pouvez aussi effectuer votre traitement une fois que vous avez lu toutes les données.*/
    for (int i = 0 ; i < sommets.size() ; ++i) {
        for (int j = 0 ; j < sommets.size() ; ++j) {
            if (i != j) {
                double poids = sqrt(pow((sommets[j][0] - sommets[i][0]), 2) + pow((sommets[j][1] - sommets[i][1]), 2));
                aretesList.push_back({ poids, i, j });
            }
        }
    }
    aretesList.sort();
    double poidsArbre = kruskalPoids(nbSommets, aretesList);
    cout << setprecision(50) << poidsArbre;
}