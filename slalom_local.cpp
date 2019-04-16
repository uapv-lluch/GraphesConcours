#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

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

int main() {
    ifstream file("../resources/slalom/input4.txt", ios::in);
    std::string line;
    int n = 0;
    int taille = 0;
    vector<vector<int>> portes;
    vector<vector<int>> dist;
    vector<arc> arcs;
    while (std::getline(file, line))
    {
        /*Lisez les données ici et effectuez votre traitement ici */
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
    /* Vous pouvez aussi effectuer votre traitement une fois que vous avez lu toutes les données.*/
    arcs.push_back({ portes[0][0], 0, 1 });
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
    vector<int> L = bellmanLong(arcs, taille*taille+1);
    cout << L[L.size()-1];
    return 0;
}