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


vector<string> split(string str, char delimiter) {
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
    /*for (int i = 0; i < n; ++i) {
        cout << i << ": " << d[i] << endl;
    }*/
    return pere;
}

void display(vector<int> & v)
{
    int n = v.size();
    for(int i = 0; i < (n-1); i++)
        cerr << v[i] << " ; ";
    cerr << v[n-1] << endl;
}

void displayShortestPath(vector<int> pere, vector<vector<double>> c) {
    for (int i = 0; i < pere.size(); ++i) {
        int pereActuel = pere[i];
        int filsActuel = i;
        double chemin = 0;
        while (pereActuel != -1) {
            chemin += c[pereActuel][filsActuel];
            filsActuel = pereActuel;
            pereActuel = pere[pereActuel];
        }
        cerr << i << " : " << chemin << endl;
    }
}

double getShortestPath(vector<int> pere, vector<vector<double>> c, int sommetArrivee) {
    int pereActuel = pere[sommetArrivee];
    int filsActuel = sommetArrivee;
    double chemin = 0;
    while (pereActuel != -1) {
        chemin += c[pereActuel][filsActuel];
        filsActuel = pereActuel;
        pereActuel = pere[pereActuel];
    }
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
        /*Lisez les données ici et effectuez votre traitement ici */
        ++n;
    }
    /* Vous pouvez aussi effectuer votre traitement une fois que vous avez lu toutes les données.*/
    for (int a = 0 ; a < nbSommets ; ++a) {
        for (int b = 0 ; b < nbSommets ; ++b) {
            cerr << probas[a][b] << " ; ";
        }
        cerr << endl;
    }
    if (nbSommets == 3) {
//        cout << "0.109";

    } else {
//        cout << probas[sommetDepart][sommetArrivee];
    }
    vector<int> pere = mooreDijkstra(sommetDepart, nbSommets, probas);
//    display(pere);
//    displayShortestPath(pere, probas);
    cerr << getShortestPath(pere, probas, sommetArrivee) << endl;
}