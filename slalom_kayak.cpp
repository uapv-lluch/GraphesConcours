/*******
 * Read input from cin
 * Use cout << ... to output your result to STDOUT.
 * Use cerr << ... to output debugging information to STDERR
 * ***/
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <iomanip>
#include "exercise.hpp"

using namespace std;

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

struct arc {
    int poids;
    int sommetDepart;
    int sommetArrivee;

    bool operator <(const arc & arcObj) const {
        return poids < arcObj.poids;
    }
};

vector<int> bellmanLong(const vector<arc>& arcs, int n) {
    int s = 0;
    vector<int> L(n);
    vector<int> Pred(n);
    L[s] = 0;
    for (int i = 0 ; i < n ; ++i) {
        if (i != s) {
            L[i] = -1;
        }
    }
    bool stop = false;
    while (!stop) {
        stop = true;
        for (auto it : arcs) {
            if (L[it.sommetArrivee] < L[it.sommetDepart] + it.poids) {
                L[it.sommetArrivee] = L[it.sommetDepart] + it.poids;
                Pred[it.sommetArrivee] = it.sommetDepart;
                stop = false;
            }
        }
    }
    return L;
}

int getSommet(int i, int j, int taille) {
    return i*taille + j + 1;
}

void ContestExerciseImpl::main() {
    std::string line;
    int n = 0;
    int taille = 0;
    vector<vector<int>> portes;
    vector<vector<int>> dist;
    vector<arc> arcs;
    while (std::getline(std::cin, line))
    {
        // On lit les données et on stocke la taille de la grille et les emplacements des portes dans une matrice
        if (n == 0) {
            taille = stoi(line);
            portes.resize(taille, vector<int>(taille));
            dist.resize(taille, vector<int>(taille));
        } else {
            for (int i = 0 ; i < taille ; ++i) {
                portes[n-1][i] = line[i] == 'X';
            }
        }
        ++n;
    }
    // On parcours tous les arcs possible et on les stocke avec leur poids
    arcs.push_back({ portes[0][0], 0, 1 }); // on créé l'arc qui part du sommetInitial au premier sommet de la grille
    for (int i = 0 ; i < taille ; ++i) {
        for (int j = 0 ; j < taille ; ++j) {
            int sommetCourant = getSommet(i, j, taille);
            if (i < taille-1 && j < taille -1) {
                arcs.push_back({ portes[i][j+1], sommetCourant, getSommet(i, j+1, taille) });
                arcs.push_back({ portes[i+1][j], sommetCourant, getSommet(i+1, j, taille) });
                arcs.push_back({ portes[i+1][j+1], sommetCourant, getSommet(i+1, j+1, taille) });
            } else {
                if (i == taille-1 && j < taille-1) {
                    arcs.push_back({ portes[i][j+1], sommetCourant, getSommet(i, j+1, taille) });
                }
                if (i < taille-1 && j == taille-1) {
                    arcs.push_back({ portes[i+1][j], sommetCourant, getSommet(i+1, j, taille) });
                }
            }
        }
    }
    vector<int> L = bellmanLong(arcs, taille*taille+1); // on utilise une variante de l'algorithme de Bellman pour le plus long chemin pour recuperer un tableau des distances au sommet initial
    cout << L[L.size()-1]; // on affiche la distance en prenant le plus long chemin du dernier sommet de la grille
}