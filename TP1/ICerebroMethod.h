/*
 * AbstractMethod.h
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#ifndef ICerebroMethod_H_
#define ICerebroMethod_H_

#include "Helpers/CvsParser.h"
#include "Helpers/MatlabHelpers.h"

#include <math.h>       /* log */


class ICerebroMethod {
protected:
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

	ICerebroMethod(double deltaT /* dias*/ , double deltaSpace /* mm */, Matrix3D disfusion /*mm2/dia*/,
								double maxConcentration /*celulas/mm 3 */, double proliferationRate /*celulas/dia*/, double radiotherapyRate /* s=celulas/dia */) :
		deltaT(deltaT),
		deltaSpace(deltaSpace),
		disfusion(disfusion),
		maxConcentration(maxConcentration),
		proliferationRate(proliferationRate),
		radiotherapyRate(radiotherapyRate){
	}

	virtual ~ICerebroMethod() {};

	void start(double endTime /*days*/);
	void setInitialCondition(uint initialCancerSize /* cm3 */, uint xCancerLocation, uint yCancerLocation, uint zCancerLocation);
protected:
	Matrix3D& getConcentration() { return *this->concentration; }
	double getDiscretizationFactor() { return this->deltaT / std::pow(this->deltaSpace,2); }

	/**
	 * This method resolves the discretization function in each iteration
	 */
	virtual std::shared_ptr<Matrix3D> ResolveItarativeStep() =0;

};

#endif /* SemiExplicitMethod_H_ */
