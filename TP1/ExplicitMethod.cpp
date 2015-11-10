/*
 * SemiExplicitMethod.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#include "ExplicitMethod.h"

/**
 * This method resolves the discretization function in each iteration
 */
static int static_iteration = 0;
std::shared_ptr<Matrix3D> CerebroExplicitMethod::ResolveItarativeStep(){
	auto shape = this->getConcentration().shape(); // x, y and z sizes
	Matrix3D newConcentration(boost::extents[shape[0]][shape[1]][shape[2]]); // create an empty matrix with the same size

	// For debugging
	Matrix3D proliferationMatrix(boost::extents[shape[0]][shape[1]][shape[2]]); // create an empty matrix with the same size
	//Matrix3D radiotherapy(boost::extents[shape[0]][shape[1]][shape[2]]); // create an empty matrix with the same size

    double factor = this->getDiscretizationFactor();
	for (uint i = 1; i < shape[0] - 2; i ++ ){ // NOTE: border condition: not evaluating the border rows&cols (starting in 1 and finishing -1)
			for (uint j = 1; j < shape[1] - 2; j ++ ){
				for (uint k = 1; k < shape[2] - 2; k ++ ){
					//∇ · (D∇C)
					double xPart = (this->disfusion[i+1][j][k] - this->disfusion[i-1][j][k]) * (this->getConcentration()[i+1][j][k]- this->getConcentration()[i-1][j][k]) +
							this->disfusion[i][j][k] * (this->getConcentration()[i+1][j][k] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i-1][j][k]);
					double yPart = (this->disfusion[i][j+1][k] - this->disfusion[i][j-1][k]) * (this->getConcentration()[i][j+1][k] - this->getConcentration()[i][j-1][k]) +
												this->disfusion[i][j][k] * (this->getConcentration()[i][j+1][k] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i][j-1][k]);
					double zPart = (this->disfusion[i][j][k+1] - this->disfusion[i][j][k-1]) * (this->getConcentration()[i][j][k+1]- this->getConcentration()[i][j][k-1]) +
												this->disfusion[i][j][k] * (this->getConcentration()[i][j][k+1] - 2*this->getConcentration()[i][j][k] + this->getConcentration()[i][j][k-1]);

//					printf("[%i][%i][%i] yPart=%f ; D+1=%f ; D-1=%f;   C+1=%f ; C-1=%f ; D=%f; C+1=%f;  C=%f ; C-1=%f  \n", i,j,k, yPart, this->disfusion[i][j+1][k], this->disfusion[i][j-1][k], this->getConcentration()[i][j+1][k], this->getConcentration()[i][j-1][k],
//							this->disfusion[i][j][k], this->getConcentration()[i][j+1][k], this->getConcentration()[i][j][k], this->getConcentration()[i][j-1][k]);

					// proliferation term : ρ C ln (Cm / C)
					double currentConcentration = this->getConcentration()[i][j][k]; // just to keep it close
					double proliferation = 0;
					double proliferationConcentration = -1;
					if(currentConcentration > 0 && this->disfusion[i][j][k] > 0){ // NOTE: ρ = 0.107 c ́elulas/dia es la tasa neta de proliferaci ́on celular para sustancia gris y blanca. En otro caso ρ = 0.
						proliferationConcentration = std::min(log(maxConcentration/currentConcentration), std::numeric_limits<double>::max()); // NOTE: log might return INF

						proliferationConcentration = currentConcentration * proliferationConcentration;
						proliferation =  (this->proliferationRate - 1 + this->radiotherapyRate) * proliferationConcentration;

						proliferationMatrix[i][j][k] = proliferation;
						//printf("[%i][%i][%i] newProliferation=%f, proliferationConcentration=%f ; currentConcentration=%f ; log=%f \n", i,j,k,proliferationMatrix[i][j][k], proliferationConcentration, currentConcentration, log(maxConcentration/currentConcentration));
					}

					double newValue =  (factor * (xPart + yPart + zPart + proliferation)) + this->getConcentration()[i][j][k];
					//printf("[%i][%i][%i] xPart=%f ; yPart=%f ; zPart=%f ;  proliferation=%f;   getConcentration=%f ; factor=%f  \n",i, j, k, xPart, yPart, zPart, proliferation, this->getConcentration()[i][j][k], factor);
					//printf("newValue=%f  \n", newValue);

					// make sure we keep it consistent
					if(newValue == std::numeric_limits<double>::infinity() || newValue > this->maxConcentration + 0.5 || newValue < -0.5){
						printf("---------    newValue=%f  ------------- \n", newValue);
						printf("[%i][%i][%i] xPart=%f ; yPart=%f ; zPart=%f ;  proliferation=%f;   getConcentration=%f ; factor=%f  \n",i, j, k, xPart, yPart, zPart, proliferation, this->getConcentration()[i][j][k], factor);
						printf("[%i][%i][%i] yPart=%f ; D+1=%f ; D-1=%f;   C+1=%f ; C-1=%f ; D=%f; C+1=%f;  C=%f ; C-1=%f  \n", i,j,k, yPart, this->disfusion[i][j+1][k], this->disfusion[i][j-1][k], this->getConcentration()[i][j+1][k], this->getConcentration()[i][j-1][k],
													this->disfusion[i][j][k], this->getConcentration()[i][j+1][k], this->getConcentration()[i][j][k], this->getConcentration()[i][j-1][k]);
						printf("[%i][%i][%i] newProliferation=%f, proliferationConcentration=%f ; currentConcentration=%f ; log=%f \n", i,j,k,proliferationMatrix[i][j][k], proliferationConcentration, currentConcentration, log(maxConcentration/currentConcentration));

					}

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

	if((static_iteration % ((int)std::floor(1/this->deltaT))) == 0){
		char fileName[BUFSIZE];
		sprintf(fileName, "/tmp/%s_t%i.%s", "proliferation", static_iteration, "vtk");
		MatlabHelper::WriteToVtk(proliferationMatrix, fileName);

//		typedef boost::multi_array_types::index_range range;
//		Matrix3D::array_view<3>::type miniProliferacion = proliferationMatrix[ boost::indices[range(10, 20)][range(70, 80)][range(75, 85)] ];
//		sprintf(fileName, "/tmp/%s_t%i.%s", "proliferation_mini", static_iteration, "vtk");
//		MatlabHelper::WriteToVtk(miniProliferacion, fileName);

	}
	static_iteration++;

	return std::make_shared<Matrix3D>(newConcentration);
}
