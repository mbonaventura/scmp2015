#ifndef PLACA_PETRI_H_
#define PLACA_PETRI_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h> /* For strcmp() */
#include <stdlib.h> /* For EXIT_FAILURE, EXIT_SUCCESS */
#include <vector> /* For STL */
//#include "mat.h"
#include <cmath>

#include "MatlabHelpers.h"

using namespace std;



class PlacaPetri {
	#define BUFSIZE 256
	#define PETRI_FILE_NAME "petriConstDt001_t"


private:
	// Discretizacion
	int discreteSteps; // discretizacion del espacio (igual en X que en Y)
	double dT; // discretizacion del tiempo
	int totalIterations;
	double maxTime;

	// Parametros
	bool useConstantPerturbation;
	double xMax, yMax;
	double initialPerturbationY;
	double initialPerturbationX;
	double initialValue;
	double DizqValue;
	double DderValue;

public:
	PlacaPetri(double Dizq, double Dder){
		this->discreteSteps = 100; // discretizacion del espacio (igual en X que en Y)
		this->dT = 0.01; // discretizacion del tiempo en min
		this->maxTime = 30; //min
		this->totalIterations = maxTime / this->dT; // cantidad de iteraciones
		this->useConstantPerturbation = true;

		xMax = yMax=10; // cm
		initialPerturbationY = 0.5;
		initialPerturbationX = 0.5;
		initialValue = 2;
		DizqValue = Dizq; //0.1;
		DderValue = Dder; //0.05;
	}

	void Start();

private:
	std::vector<std::vector<double> > ResolveItarativeStep(std::vector<std::vector<double> >& newC, std::vector<std::vector<double> >& D) ;

};

#endif /* PLACA_PETRI_H_ */

