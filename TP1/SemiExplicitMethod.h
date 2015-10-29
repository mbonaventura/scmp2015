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

#include <math.h>       /* log */


class CerebroSemiExplicitMethod {
private:
	// Parameters
	double deltaT; // dias
	double deltaSpace; //mm
	Matrix3D disfusion; //mm2/dia
	double maxConcentration; /* celulas/mm 3 */

	double proliferationRate; // celulas/dia
	double radiotherapyRate; /* s = e −αdose−β dose 2 */

	// variables
	std::shared_ptr<Matrix3D> concentration;

public:

	CerebroSemiExplicitMethod(double deltaT /* dias*/ , double deltaSpace /* mm */, Matrix3D disfusion /*mm2/dia*/,
								double maxConcentration /*celulas/mm 3 */, double proliferationRate /*celulas/dia*/, double radiotherapyRate /* s=celulas/dia */) :
		deltaT(deltaT),
		deltaSpace(deltaSpace),
		disfusion(disfusion),
		maxConcentration(maxConcentration),
		proliferationRate(proliferationRate),
		radiotherapyRate(radiotherapyRate){

		if(this->getDiscretizationFactor() > 0.5){
			printf("Invalid deltT / deltaX 2 for this method must be < 0.5. Configured at  %f \n", this->getDiscretizationFactor());
			throw new std::runtime_error("Invalid deltT / deltaX 2 for this method must be < 0.5.\n");
		}

	}

	virtual ~CerebroSemiExplicitMethod() {};

	void start(double endTime /*days*/);
	void setInitialCondition(uint initialCancerSize /* cm3 */, uint xCancerLocation, uint yCancerLocation, uint zCancerLocation);
private:
	Matrix3D& getConcentration() { return *this->concentration; }
	std::shared_ptr<Matrix3D> ResolveItarativeStep();


	double getDiscretizationFactor() { return this->deltaT / std::pow(this->deltaSpace,2); }


};

#endif /* SemiExplicitMethod_H_ */
