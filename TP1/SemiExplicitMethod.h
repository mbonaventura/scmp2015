/*
 * SemiExplicitMethod.h
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#ifndef SemiExplicitMethod_H_
#define SemiExplicitMethod_H_

#include "Helpers/CvsParser.h"
#include "Helpers/MatlabHelpers.h"


class CerebroSemiExplicitMethod {
private:
	// Parameters
	double deltaT;
	double deltaSpace;
	Matrix3D disfusion;

	// variables
	std::shared_ptr<Matrix3D> concentration;

public:

	CerebroSemiExplicitMethod(double deltaT, double deltaSpace, Matrix3D disfusion) :
		deltaT(deltaT),
		deltaSpace(deltaSpace),
		disfusion(disfusion){

	}

	virtual ~CerebroSemiExplicitMethod() {};

	void start();
	void setInitialCondition(uint initialCancerSize /* cm3 */, double initialConcentration /* celulas/mm 3 */, uint xCancerLocation, uint yCancerLocation, uint zCancerLocation);
private:
	Matrix3D& getConcentration() { return *this->concentration; }
	std::shared_ptr<Matrix3D> ResolveItarativeStep();


private:

};

#endif /* SemiExplicitMethod_H_ */
