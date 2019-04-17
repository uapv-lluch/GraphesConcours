/*******
 * Read input from cin
 * Use cout << ... to output your result to STDOUT.
 * Use cerr << ... to output debugging information to STDERR
 * ***/
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <list>
#include "exercise.hpp"

using namespace std;


ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}


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

vector<int> mooreDijkstra(int s, int n, vector<vector<double>> c) {
    vector<int> C;
    list<int> Cbarre;
    for (int i = 0; i < n; ++i) {
        Cbarre.push_back(i);
    }
    C.push_back(s);
    Cbarre.remove(s);
    vector<double> d(n);
    vector<int> pere(n);
    for (int i = 0; i < n; ++i) {
        pere[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        d[i] = 99999;
    }
    d[s] = 0;
    int j = s;
    for (int l = 1; l < n; ++l) {
        for (list<int>::iterator it = Cbarre.begin(); it != Cbarre.end(); ++it) {
            if (c[j][*it] != 0) {
                if (1 - ((1-d[j]) * (1-c[j][*it])) < d[*it]) {
                    d[*it] = 1 - ((1-d[j]) * (1-c[j][*it]));
                    pere[*it] = j;
                }
            }
        }
        // Argmin
        double min = 99999;
        for (list<int>::iterator it = Cbarre.begin(); it != Cbarre.end(); ++it) {
            if (d[*it] < min) {
                min = d[*it];
                j = *it;
            }
        }
        C.push_back(j);
        Cbarre.remove(j);
    }
    return pere;
}

double getShortestPath(vector<int> pere, vector<vector<double>> c, int sommetArrivee) {
    int pereActuel = pere[sommetArrivee];
    int filsActuel = sommetArrivee;
    double chemin = 1;
    while (pereActuel != -1) {
        chemin = chemin * (1 - c[pereActuel][filsActuel]);
        filsActuel = pereActuel;
        pereActuel = pere[pereActuel];
    }
    chemin = 1 - chemin;
    return chemin;
}



void ContestExerciseImpl::main() {
    std::string line;
    int n = 0;
    int i = 0;
    int j = 0;
    int sommetDepart = 0;
    int sommetArrivee = 0;
    int nbSommets = 0;
    vector<vector<double>> probas;
    while (std::getline(std::cin, line))
    {
        // On lit les données et on stocke le nombre de sommets les sommets de depart et d'arrivée du chemin et les probabilité d'avalanches des pistes (poids des aretes)
        if (n == 0) { // Nombre de sommets
            nbSommets = stoi(line);
            probas.resize(nbSommets, vector<double>(nbSommets));
        } else if (n == 1) { // Sommets de départ et d'arrivée
            sommetDepart = stoi(split(line, ' ')[0]);
            sommetArrivee = stoi(split(line, ' ')[1]);
        } else { // Probabilités
            vector <string> splitted = split(line, ' ');
            for (j = 0 ; j < nbSommets ; ++j) {
                probas[i][j] = stod(splitted[j]);
            }
            ++i;
        }
        ++n;
    }
    vector<int> pere = mooreDijkstra(sommetDepart, nbSommets, probas); // on utilise l'algorithme de Moore-Dijkstra pour récupérer la liste des predecesseurs de chaque sommet par le plus court chemin
    cout << getShortestPath(pere, probas, sommetArrivee) << endl; // on affiche la probabilité d'avalanche du plus court chemin (la probabilité d'avalanche la plus faible pour aller d'un sommet A à un sommet B)
}