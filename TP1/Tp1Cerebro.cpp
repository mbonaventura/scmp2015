//============================================================================
// Name        : Tp1Cerebro.cpp
// Author      : MatiasB
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "Helpers/CvsParser.h"
#include "Helpers/MatlabHelpers.h"
#include "SemiExplicitMethod.h"

// Representation size
#define SIZE_X 181
#define SIZE_Y 217
#define SIZE_Z 181

//Cm = 1.10'8 celulas/mm 3 es la concentracion maxima de celulas
#define CANCER_CONCENTRATION_MAX 2.14358881 // celulas/mm 3

// INITIAL VALUES
#define INITIAL_CANCER_SIZE 3
#define INITIAL_CANCER_LOCATION_X 100
#define INITIAL_CANCER_LOCATION_Y 100
#define INITIAL_CANCER_LOCATION_Z 130

#define CELL_SIZE 10 // cm. Cells are all equal

int main(void) {
	printf("Starting to parse Cerebro .. \n");
	Matrix3D disfusionMatrix = CvsParser::parseCvs3DCerebro("Resources/Cerebro.csv", SIZE_X, SIZE_Y, SIZE_Z);
	printf("Finished parsing file  \n");

	MatlabHelper::WriteToVtk(disfusionMatrix, "/tmp/cerebro.vtk");


	CerebroSemiExplicitMethod* method = new CerebroSemiExplicitMethod(0.1, 0.1, disfusionMatrix);

	/** create initial conditions from TP:
	 * El dominio del problema es un cubo donde est ́a alojada la representaci ́on digital de un cerebro humano.
	 * Condiciones iniciales: C(x, y, z, 0) = 0 en todo el dominio, excepto en una esfera de radio 3cm centrada en un
	 * punto elegido por usted, que representa al esferoide seminal, el mismo debe estar en materia gris o blanca,
	 * C(x 0 , y 0 , z 0 , 0) = Cm/2.
	 */
	// initialize all 0s
	method->setInitialCondition(INITIAL_CANCER_SIZE, CANCER_CONCENTRATION_MAX, INITIAL_CANCER_LOCATION_X, INITIAL_CANCER_LOCATION_Y, INITIAL_CANCER_LOCATION_Z);


	//printf("Cerebro has %lu",  cerebro.shape());

	delete method; // just in case
	return EXIT_SUCCESS;
}
