#include "PlacaPetri.h"

void PlacaPetri::Start() {
	// Condiciones iniciales
	std::vector<std::vector<double> > C(discreteSteps);
	std::vector<std::vector<double> > D(discreteSteps);
	for (double i = 0; i < discreteSteps; i ++ ){
		C[i] = *(new std::vector<double>(discreteSteps)); // todo: lossing memory
		D[i] = *(new std::vector<double>(discreteSteps)); // todo: lossing memory

		for (double j = 0; j < discreteSteps; j ++ ){
			// C
			C[i][j] = 0;
			if(i == initialPerturbationX*discreteSteps && j == initialPerturbationY*discreteSteps){
				C[i][j] = initialValue;
			}

			// D
			D[i][j] = DizqValue;
			if(j >  discreteSteps/2 ){
				D[i][j] = DderValue;
			}
		}
	}
	//std::cout << "C:\n";
	//MatlabHelper::PrintMatrix(C, 0);
	//std::cout << "D:\n";
	//MatlabHelper::PrintMatrix(D, 0);

	char baseFileName[BUFSIZE];
	char fileName[BUFSIZE];
	sprintf(baseFileName, "petri_%f_%f_dt%f_dx%f", this->DderValue, this->DizqValue, this->dT, this->xMax / this->discreteSteps);

	sprintf(fileName, "%s_t%i.%s", baseFileName, 0, "vtk");
	MatlabHelper::WriteMatrixToVtk(C, fileName);

	// Iteraciones
	std::cout << "dX=" << this->xMax / this->discreteSteps << "\n";
	std::cout << "dt=" << this->dT << "\n";
	std::cout << "DizqValue=" << DizqValue << "\n";
	std::cout << "DderValue=" << this->DderValue << "\n";
	for (int iteration = 1; iteration < this->totalIterations; iteration++ ){
		ResolveItarativeStep(C, D);

		//MatlabHelper::PrintMatrix(C, iteration);
		sprintf(fileName, "temp/%s_t%i.%s", baseFileName, iteration, "vtk");
		MatlabHelper::WriteMatrixToVtk(C, fileName);

		if(iteration % 100 == 0){
			std::cout << "Finished iteration " << iteration << "\n";
		}
	}
}

std::vector<std::vector<double> > PlacaPetri::ResolveItarativeStep(std::vector<std::vector<double> >& newC, std::vector<std::vector<double> >& D) {
	std::vector<std::vector<double> > C = newC; // TODO: copy or reference??

	double dX = this->xMax / this->discreteSteps; //cm
	double discretizationFactor = this->dT / std::pow(dX,2);

	for (double i = 1; i < this->discreteSteps-1; i ++ ){
		for (double j = 1; j < this->discreteSteps-1; j ++ ){
			double xPart = (D[i+1][j] - D[i-1][j]) * (C[i+1][j]- C[i-1][j]) + D[i][j] * (C[i+1][j] - 2*C[i][j] + C[i-1][j]);
			double yPart = (D[i][j+1] - D[i][j-1]) * (C[i][j+1]- C[i][j-1]) + D[i][j] * (C[i][j+1] - 2*C[i][j] + C[i][j-1]);

			newC[i][j] = discretizationFactor * (xPart + yPart) + C[i][j];

			if(this->useConstantPerturbation && i == initialPerturbationX*discreteSteps && j == initialPerturbationY*discreteSteps){
				newC[i][j] = initialValue;
			}
		}
	}


	return newC;
}



