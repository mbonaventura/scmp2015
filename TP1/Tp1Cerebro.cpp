//============================================================================
// Name        : Tp1Cerebro.cpp
// Author      : MatiasB
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "ExplicitMethod.h"
//#include "ImplicitMethod.h"
#include "Helpers/CvsParser.h"
#include "Helpers/MatlabHelpers.h"

// Representation size
#define SIZE_X 181
#define SIZE_Y 217
#define SIZE_Z 181
#define CELL_SIZE 1 // mm. Cells are all equal

//Cm = 1.10'8 celulas/mm 3 es la concentracion maxima de celulas
#define CANCER_CONCENTRATION_MAX 2.14358881 // celulas/mm 3
#define PROLIFERATION_RATE 0.107 // ćelulas/dia
#define RADIOTHERAPY_RATE 0.926386264 // s= e^(−α dose−β dose 2) = e −0,076464 = 0,926386264

// INITIAL VALUES
#define INITIAL_CANCER_SIZE 10 //mm
#define INITIAL_CANCER_LOCATION_X 100
#define INITIAL_CANCER_LOCATION_Y 100
#define INITIAL_CANCER_LOCATION_Z 130



int main(void) {
	printf("Starting to parse Cerebro .. \n");
	Matrix3D disfusionMatrix_total = CvsParser::parseCvs3DCerebro("Resources/Cerebro.csv", SIZE_X, SIZE_Y, SIZE_Z);
	printf("Finished parsing file  \n");

//	typedef boost::multi_array_types::index_range range;
//	Matrix3D::array_view<3>::type disfusionMatrix = disfusionMatrix_total[ boost::indices[range(95, 105)][range(95, 105)][range(125, 135)] ];
	Matrix3D disfusionMatrix = disfusionMatrix_total;

	//MatlabHelper::WriteToVtk(disfusionMatrix_total, "/tmp/cerebro_full.vtk");
	MatlabHelper::WriteToVtk(disfusionMatrix, "/tmp/cerebro.vtk");


	ICerebroMethod* method = new CerebroExplicitMethod(0.1, CELL_SIZE, disfusionMatrix, CANCER_CONCENTRATION_MAX, PROLIFERATION_RATE, RADIOTHERAPY_RATE);

	/** create initial conditions from TP:
	 * El dominio del problema es un cubo donde est ́a alojada la representaci ́on digital de un cerebro humano.
	 * Condiciones iniciales: C(x, y, z, 0) = 0 en todo el dominio, excepto en una esfera de radio 3cm centrada en un
	 * punto elegido por usted, que representa al esferoide seminal, el mismo debe estar en materia gris o blanca,
	 * C(x 0 , y 0 , z 0 , 0) = Cm/2.
	 */
	// initialize all 0s
	method->setInitialCondition(INITIAL_CANCER_SIZE, INITIAL_CANCER_LOCATION_X , INITIAL_CANCER_LOCATION_Y, INITIAL_CANCER_LOCATION_Z);

	method->start(30);
	//printf("Cerebro has %lu",  cerebro.shape());

	printf("Simulation Finished  \n");
	delete method; // just in case
	return EXIT_SUCCESS;
}
