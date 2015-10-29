/*
 * SemiExplicitMethod.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#include "SemiExplicitMethod.h"

void CerebroSemiExplicitMethod::start(double endTime /*days*/){
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
	for (double simuTime = 0; simuTime < endTime; simuTime += this->deltaT ){
		this->concentration = ResolveItarativeStep();

		//MatlabHelper::PrintMatrix(C, iteration);
		sprintf(fileName, "/tmp/%s_t%i.%s", "cancer_noRadioTherapy", iteration, "vtk");

		printf("Finished simuTime %f \n", simuTime);
		MatlabHelper::WriteToVtk(this->getConcentration(), fileName);
		//if(iteration % 100 == 0){

		//}
		iteration++;
	}
}

void CerebroSemiExplicitMethod::setInitialCondition(uint initialCancerSize /* cm3 */,  uint xCancerLocation, uint yCancerLocation, uint zCancerLocation){
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

	MatlabHelper::WriteToVtk(this->getConcentration(), "/tmp/cancer_noRadioTherapy.vtk");
}

/**
 * This method resolves the discretization function in each iteration
 */
static int static_iteration = 1;
std::shared_ptr<Matrix3D> CerebroSemiExplicitMethod::ResolveItarativeStep(){
	auto shape = this->getConcentration().shape(); // x, y and z sizes
	Matrix3D newConcentration(boost::extents[shape[0]][shape[1]][shape[2]]); // create an empty matrix with the same size
	Matrix3D proliferationMatrix(boost::extents[shape[0]][shape[1]][shape[2]]); // create an empty matrix with the same size
	Matrix3D radiotherapy(boost::extents[shape[0]][shape[1]][shape[2]]); // create an empty matrix with the same size

    double factor = this->getDiscretizationFactor();
	for (double i = 1; i < shape[0] -1; i ++ ){ // NOTE: border condition: not evaluating the border rows&cols (starting in 1 and finishing -1)
			for (double j = 1; j < shape[1] - 1; j ++ ){
				//∇ · (D∇C)
				for (double k = 1; k < shape[2] - 1; k ++ ){
					double xPart = (this->disfusion[i+1][j][k] - this->disfusion[i-1][j][k]) * (this->getConcentration()[i+1][j][k]- this->getConcentration()[i-1][j][k]) +
							this->disfusion[i][j][k] * (this->getConcentration()[i+1][j][k] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i-1][j][k]);
					double yPart = (this->disfusion[i][j+1][k] - this->disfusion[i][j-1][k]) * (this->getConcentration()[i][j+1][k]- this->getConcentration()[i][j-1][k]) +
												this->disfusion[i][j][k] * (this->getConcentration()[i][j+1][k] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i][j-1][k]);
					double zPart = (this->disfusion[i][j][k+1] - this->disfusion[i][j][k-1]) * (this->getConcentration()[i][j][k+1]- this->getConcentration()[i][j][k-1]) +
												this->disfusion[i][j][k] * (this->getConcentration()[i][j][k+1] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i][j][k-1]);

					// proliferation term : ρ C ln (Cm / C)
					double currentConcentration = this->getConcentration()[i][j][k]; // just to keep it close
					double proliferation = 0;
					if(currentConcentration > 0){
						double proliferationConcentration = currentConcentration * log(maxConcentration/currentConcentration);

						//proliferation = this->radiotherapyRate * proliferation;
						//printf("radiotherapyRate= %f \n", proliferationConcentration);
						// NOTE: ρ = 0.107 c ́elulas/dia es la tasa neta de proliferaci ́on celular para sustancia gris y blanca. En otro caso ρ = 0.
						if(this->disfusion[i][j][k] > 0){
							proliferation = this->proliferationRate * proliferationConcentration - proliferation;
							proliferationMatrix[i][j][k] =  proliferation;
						}
					}
					//printf("proliferationConcentration= %f \n", proliferation);

					double newValue =  (factor * (xPart + yPart + zPart + proliferation)) + this->getConcentration()[i][j][k];

					// make sure we keep it consistent
					if(newValue < 0) {
						newConcentration[i][j][k] = 0;
					} else if(newValue > this->maxConcentration){
						newConcentration[i][j][k] = this->maxConcentration;
					} else{
						newConcentration[i][j][k] = newValue;
					}
				}
			}
	}

	char fileName[BUFSIZE];
	sprintf(fileName, "/tmp/%s_t%i.%s", "proliferation", static_iteration++, "vtk");
	MatlabHelper::WriteToVtk(proliferationMatrix, fileName);

	return std::make_shared<Matrix3D>(newConcentration);
}
