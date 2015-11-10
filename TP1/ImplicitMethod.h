/*
 * ImplicitMethod.h
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#ifndef CerebroImplicitMethod_H_
#define CerebroImplicitMethod_H_

#include "Helpers/CvsParser.h"
#include "Helpers/MatlabHelpers.h"
#include "ICerebroMethod.h"

#include <math.h>       /* log */


class CerebroImplicitMethod : public ICerebroMethod {

public:
	CerebroImplicitMethod(double deltaT /* dias*/ , double deltaSpace /* mm */, Matrix3D disfusion /*mm2/dia*/,
								double maxConcentration /*celulas/mm 3 */, double proliferationRate /*celulas/dia*/, double radiotherapyRate /* s=celulas/dia */) :
				ICerebroMethod(deltaT, deltaSpace, disfusion, maxConcentration,
														proliferationRate, radiotherapyRate){

	}

protected:
	/**
	 * This method resolves the discretization function in each iteration
	 */
	std::shared_ptr<Matrix3D> ResolveItarativeStep();
};

#endif /* ImplicitMethod_H_ */
