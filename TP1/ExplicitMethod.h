/*
 * ExplicitMethod.h
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#ifndef ExplicitMethod_H_
#define ExplicitMethod_H_

#include "Helpers/CvsParser.h"
#include "Helpers/MatlabHelpers.h"
#include "ICerebroMethod.h"

#include <math.h>       /* log */


class CerebroExplicitMethod : public ICerebroMethod {
public:

	CerebroExplicitMethod(double deltaT /* dias*/ , double deltaSpace /* mm */, Matrix3D disfusion /*mm2/dia*/,
								double maxConcentration /*celulas/mm 3 */, double proliferationRate /*celulas/dia*/, double radiotherapyRate /* s=celulas/dia */) :
			ICerebroMethod(deltaT, deltaSpace, disfusion, maxConcentration,
					proliferationRate, radiotherapyRate){

		if(this->getDiscretizationFactor() > 0.5){
			printf("Invalid deltT / deltaX 2 for this method must be < 0.5. Configured at  %f \n", this->getDiscretizationFactor());
			throw new std::runtime_error("Invalid deltT / deltaX 2 for this method must be < 0.5.\n");
		}
	}

protected:
	std::shared_ptr<Matrix3D> ResolveItarativeStep();

};

#endif /* SemiExplicitMethod_H_ */
