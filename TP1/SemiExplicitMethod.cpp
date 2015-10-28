/*
 * SemiExplicitMethod.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#include "SemiExplicitMethod.h"

void CerebroSemiExplicitMethod::start(){
	printf("Staring SemiImplicit method \n");


}

void CerebroSemiExplicitMethod::setInitialCondition(uint initialCancerSize /* cm3 */, double initialConcentration, uint xCancerLocation, uint yCancerLocation, uint zCancerLocation){
	printf("Setting initial values  \n");
	auto shape = this->disfusion.shape(); // x, y and z sizes
	Matrix3D initialConcentrationMatrix(boost::extents[shape[0]][shape[1]][shape[2]]);

	for(uint i = xCancerLocation; i < xCancerLocation + initialCancerSize; i++)
		for(uint j = yCancerLocation; j < yCancerLocation + initialCancerSize; j++)
			for(uint k = zCancerLocation; k < zCancerLocation + initialCancerSize; k++){
				this->getConcentration()[i][j][k] = initialConcentration;
			}

	this->concentration = std::make_shared<Matrix3D>(initialConcentrationMatrix);

	MatlabHelper::WriteToVtk(this->getConcentration(), "cancer.vtk");
}

std::shared_ptr<Matrix3D> CerebroSemiExplicitMethod::ResolveItarativeStep(){
	auto shape = this->getConcentration().shape(); // x, y and z sizes
	Matrix3D newC(boost::extents[shape[0]][shape[1]][shape[2]]); // create an empty matrix with the same size


	for (double i = 1; i < shape[0] -1; i ++ ){ // NOTE: border condition: not evaluating the border rows&cols (starting in 1 and finishing -1)
			for (double j = 1; j < shape[1] - 1; j ++ ){
				for (double k = 1; k < shape[2] - 1; k ++ ){
					double xPart = (this->disfusion[i+1][j][k] - this->disfusion[i-1][j][k]) * (this->getConcentration()[i+1][j][k]- this->getConcentration()[i-1][j][k]) +
							this->disfusion[i][j][k] * (this->getConcentration()[i+1][j][k] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i-1][j][k]);
					double yPart = (this->disfusion[i][j+1][k] - this->disfusion[i][j-1][k]) * (this->getConcentration()[i][j+1][k]- this->getConcentration()[i][j-1][k]) +
												this->disfusion[i][j][k] * (this->getConcentration()[i][j+1][k] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i][j-1][k]);
					double zPart = (this->disfusion[i][j][k+1] - this->disfusion[i][j][k-1]) * (this->getConcentration()[i][j][k+1]- this->getConcentration()[i][j][k-1]) +
												this->disfusion[i][j][k] * (this->getConcentration()[i][j][k+1] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i][j][k-1]);


				}
			}
	}



	return NULL;
}
