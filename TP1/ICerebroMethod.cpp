/*
 * ICerebroMethod.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#include "ICerebroMethod.h"

void ICerebroMethod::setInitialCondition(uint initialCancerSize /* cm3 */,  uint xCancerLocation, uint yCancerLocation, uint zCancerLocation){
	printf("Setting initial values  \n");
	auto shape = this->disfusion.shape(); // x, y and z sizes
	Matrix3D initialConcentrationMatrix(boost::extents[shape[0]][shape[1]][shape[2]]);

	for(uint i = xCancerLocation; i < xCancerLocation + initialCancerSize; i++){
		for(uint j = yCancerLocation; j < yCancerLocation + initialCancerSize; j++){
			for(uint k = zCancerLocation; k < zCancerLocation + initialCancerSize; k++){
				initialConcentrationMatrix[i][j][k] = this->maxConcentration;
			}
		}
	}

	printf("finished initialization \n");
	this->concentration = std::make_shared<Matrix3D>(initialConcentrationMatrix);

	MatlabHelper::WriteToVtk(this->getConcentration(), "/tmp/cancer_t0.vtk");
}

void ICerebroMethod::start(double endTime /*days*/){
	printf("Staring Explicit method with the following parameters\n");
	printf("proliferationRate=%f celulas/dia\n", this->proliferationRate);
	printf("radiotherapyRate (s)=%f \n", this->radiotherapyRate);
	printf("maxConcentration=%f \n", this->maxConcentration);
	printf("deltaT =%f (dias) \n", this->deltaT);
	printf("deltaSpace =%f (mm) \n", this->deltaSpace);

	printf("endTime =%f (dias)\n", endTime);

	// Iteraciones
	char fileName[BUFSIZE];
	int iteration = 1;
	for (double simuTime = this->deltaT; simuTime < endTime; simuTime += this->deltaT ){
		this->concentration = ResolveItarativeStep();

		//MatlabHelper::PrintMatrix(C, iteration);
		sprintf(fileName, "/tmp/%s_t%i.%s", "cancer", iteration, "vtk");

		printf("--------- Finished simuTime %f ---------- \n", simuTime);
		if(iteration % ((int)std::floor(1/this->deltaT)) == 0){ // one logging per day
			MatlabHelper::WriteToVtk(this->getConcentration(), fileName);
		}
		iteration++;
	}
}
