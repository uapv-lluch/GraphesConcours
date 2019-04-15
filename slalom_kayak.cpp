/*******
 * Read input from cin
 * Use cout << ... to output your result to STDOUT.
 * Use cerr << ... to output debugging information to STDERR
 * ***/
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include "exercise.hpp"

using namespace std;

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

void ContestExerciseImpl::main() {
   std::string line;
   int n = 0;
   int taille;
   vector<vector<int>> poids;
   vector<vector<int>> dist;
	while (std::getline(std::cin, line))
	{
		/*Lisez les données ici et effectuez votre traitement ici */
		if (n == 0) {
		    taille = stoi(line);
		    poids.resize(taille, vector<int>(taille));
		    dist.resize(taille, vector<int>(taille));
		} else {
		    for (int i = 0 ; i < taille ; ++i) {
		        poids[n-1][i] = line[i] == 'X';   
		    }
		}
		++n;
	}
	/* Vous pouvez aussi effectuer votre traitement une fois que vous avez lu toutes les données.*/
	for (int i = 0 ; i < taille ; ++i) {
	    for (int j = 0 ; j < taille ; ++j) {
	        dist[i][j] = 0;
            if (i > 0) {
                dist[i][j] = max(dist[i-1][j], dist[i][j]);
            }
            if (j > 0) {
                dist[i][j] = max(dist[i][j-1], dist[i][j]);
            }
            dist[i][j] += poids[i][j];
	    }   
	}
	cerr << "main" << endl;
    cerr << dist[taille-1][taille-1] << endl;
}