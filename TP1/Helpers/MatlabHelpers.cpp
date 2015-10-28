#include "MatlabHelpers.h"



void MatlabHelper::PrintVector(std::vector<double>& vec, double t){
	//std::cout << "Vector(t=" << t <<"): \n";
	for (uint i=0; i < vec.size(); i++){
		std::cout << vec[i] << ",";
	}
	std::cout << "\n";
}

void MatlabHelper::PrintMatrix(std::vector<std::vector<double> >& matrix, double t){
	std::cout << "Matrix(t=" << t <<"): \n";

	for (uint i=0; i < matrix.size(); i++){
		std::cout << "[" << i << "]: ";
		MatlabHelper::PrintVector(matrix[i], t);
	}
	std::cout << "\n";
}

//void MatlabHelper::WriteMatrixToMatLab(const std::vector<std::vector<double> >& matrix, std::string matrixName){
//	MATFile* file = matOpen(MATLAB_FILENAME, "u");
//
//	if (file == NULL) {
//		printf("Error creating file %s\n", MATLAB_FILENAME);
//		printf("(Do you have write permission in this directory?)\n");
//		throw EXIT_FAILURE;
//	}
//
//	// copy values to a matlab matrix
//	int rows = matrix[0].size(); // TODO: this assumes there is at least 1 row and that all rows are same size
//	mxArray *mx = mxCreateDoubleMatrix(rows,matrix.size(), mxREAL);
//	for (uint i=0; i < matrix.size(); i++){
//		std::copy(matrix[i].begin(), matrix[i].end(), mxGetPr(mx)+i*rows);
//	}
//
//	// write to file
//	int status = matPutVariable(file, matrixName.data(), mx);
//	if (status != 0) {
//	  printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
//	  throw EXIT_FAILURE;
//	}
//
//	/* clean up */
//	mxDestroyArray(mx);
//
//	if (matClose(file) != 0) {
//		printf("Error closing file %s\n",MATLAB_FILENAME);
//		throw EXIT_FAILURE;
//	}
//
//	std::cout << "added matrix " << matrixName << " to MATLAB file: " << MATLAB_FILENAME << "\n";
//}

void MatlabHelper::WriteMatrixToVtk(const std::vector<std::vector<double> >& matrix, std::string fileName){
	struct stat st = {0};

	std::cout << "creado dir";
	if (stat("mydirectory/mySub", &st) == -1) {
	    mkdir("mydirectory/mySub", 0700);
	}

	FILE * fid = fopen(fileName.data(), "wt");

	if (fid == NULL) {
		printf("Error creating file %s\n", fileName.data());
		printf("(Do you have write permission in this directory?)\n");
		throw EXIT_FAILURE;
	}

	uint nx = matrix.size();
	uint ny = matrix[0].size();
	uint nz = 1;

	// Write file header
	fprintf(fid, "# vtk DataFile Version 2.0\n");
	fprintf(fid, "Comment goes here\n");
	fprintf(fid, "ASCII\n");
	fprintf(fid, "\n");
	fprintf(fid, "DATASET STRUCTURED_POINTS\n");
	fprintf(fid, "DIMENSIONS    %d   %d   %d\n", nx, ny, nz);
	fprintf(fid, "\n");
	fprintf(fid, "ORIGIN    0.000   0.000   0.000\n");
	fprintf(fid, "SPACING    1.000   1.000   1.000\n");
	fprintf(fid, "\n");
	fprintf(fid, "POINT_DATA   %d\n", nx*ny*nz);
	fprintf(fid, "SCALARS scalars float\n");
	fprintf(fid, "LOOKUP_TABLE default\n");
	fprintf(fid, "\n");

	for (uint i=0; i < nx; i++){
		for (uint j=0; j < ny; j++){
			fprintf(fid, "%f ", matrix[i][j]);
		}
		fprintf(fid, "\n");
	}
	fclose(fid);
}

void MatlabHelper::WriteToVtk(const Matrix3D& matrix, std::string fileName){
	FILE * fid = fopen(fileName.data(), "wt");

	if (fid == NULL) {
		printf("Error creating file %s\n", fileName.data());
		printf("(Do you have write permission in this directory?)\n");
		throw EXIT_FAILURE;
	}

	uint nx = matrix.shape()[0];
	uint ny = matrix.shape()[1];
	uint nz = matrix.shape()[2];

	printf("Matrix Size= %i x %i x %i \n",nx, ny, nz);

	// Write file header
	fprintf(fid, "# vtk DataFile Version 2.0\n");
	fprintf(fid, "Comment goes here\n");
	fprintf(fid, "ASCII\n");
	fprintf(fid, "\n");
	fprintf(fid, "DATASET STRUCTURED_POINTS\n");
	fprintf(fid, "DIMENSIONS    %d   %d   %d\n", nx, ny, nz);
	fprintf(fid, "\n");
	fprintf(fid, "ORIGIN    0.000   0.000   0.000\n");
	fprintf(fid, "SPACING    1.000   1.000   1.000\n");
	fprintf(fid, "\n");
	fprintf(fid, "POINT_DATA   %d\n", nx*ny*nz);
	fprintf(fid, "SCALARS scalars float\n");
	fprintf(fid, "LOOKUP_TABLE default\n");
	fprintf(fid, "\n");

	for (uint i=0; i < nx; i++){
		for (uint j=0; j < ny; j++){
			for (uint k=0; k < nz; k++){
				fprintf(fid, "%f ", matrix[i][j][k]);
			}
		}
		fprintf(fid, "\n");
	}
	fclose(fid);
}

//void MatlabHelper::WriteVectorToMatLab(const std::vector<double>& vec, std::string vectorName){
//	MATFile* file = matOpen(MATLAB_FILENAME, "u");
//
//	if (file == NULL) {
//		printf("Error creating file %s\n", MATLAB_FILENAME);
//		printf("(Do you have write permission in this directory?)\n");
//		throw EXIT_FAILURE;
//	}
//
//	// copy values to a matlab matrix
//	mxArray *mx = mxCreateDoubleMatrix(1,vec.size(), mxREAL);
//	std::copy(vec.begin(), vec.end(), mxGetPr(mx));
//
//	// write to file
//	int status = matPutVariable(file, vectorName.data(), mx);
//	if (status != 0) {
//	  printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
//	  throw EXIT_FAILURE;
//	}
//	std::cout << "added vector " << vectorName << " to MATLAB file: " << MATLAB_FILENAME << "\n";
//
//	/* clean up */
//	mxDestroyArray(mx);
//
//	if (matClose(file) != 0) {
//		printf("Error closing file %s\n",MATLAB_FILENAME);
//		throw EXIT_FAILURE;
//	}
//}
//
//int test() {
//	 MATFile *pmat;
//	  mxArray *pa1, *pa2, *pa3;
//	  std::vector<int> myInts;
//	  myInts.push_back(1);
//	  myInts.push_back(2);
//	  printf("Accessing a STL vector: %d\n", myInts[1]);
//
//	  double data[9] = { 1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0 };
//	  const char *file = "mattest.mat";
//	  char str[BUFSIZE];
//	  int status;
//
//	  printf("Creating file %s...\n\n", file);
//	  pmat = matOpen(file, "w");
//	  if (pmat == NULL) {
//	    printf("Error creating file %s\n", file);
//	    printf("(Do you have write permission in this directory?)\n");
//	    return(EXIT_FAILURE);
//	  }
//
//	  pa1 = mxCreateDoubleMatrix(3,3,mxREAL);
//	  if (pa1 == NULL) {
//	      printf("%s : Out of memory on line %d\n", __FILE__, __LINE__);
//	      printf("Unable to create mxArray.\n");
//	      return(EXIT_FAILURE);
//	  }
//
//	  pa2 = mxCreateDoubleMatrix(3,3,mxREAL);
//	  if (pa2 == NULL) {
//	      printf("%s : Out of memory on line %d\n", __FILE__, __LINE__);
//	      printf("Unable to create mxArray.\n");
//	      return(EXIT_FAILURE);
//	  }
//	  memcpy((void *)(mxGetPr(pa2)), (void *)data, sizeof(data));
//
//	  pa3 = mxCreateString("MATLAB: the language of technical computing");
//	  if (pa3 == NULL) {
//	      printf("%s :  Out of memory on line %d\n", __FILE__, __LINE__);
//	      printf("Unable to create string mxArray.\n");
//	      return(EXIT_FAILURE);
//	  }
//
//	  status = matPutVariable(pmat, "LocalDouble", pa1);
//	  status = matPutVariable(pmat, "MyMAtrix", pa1);
//	  if (status != 0) {
//	      printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
//	      return(EXIT_FAILURE);
//	  }
//
//	  status = matPutVariableAsGlobal(pmat, "GlobalDouble", pa2);
//	  if (status != 0) {
//	      printf("Error using matPutVariableAsGlobal\n");
//	      return(EXIT_FAILURE);
//	  }
//
//	  status = matPutVariable(pmat, "LocalString", pa3);
//	  if (status != 0) {
//	      printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
//	      return(EXIT_FAILURE);
//	  }
//
//	  /*
//	   * Ooops! we need to copy data before writing the array.  (Well,
//	   * ok, this was really intentional.) This demonstrates that
//	   * matPutVariable will overwrite an existing array in a MAT-file.
//	   */
//	  memcpy((void *)(mxGetPr(pa1)), (void *)data, sizeof(data));
//	  status = matPutVariable(pmat, "LocalDouble", pa1);
//	  status = matPutVariable(pmat, "MyMatrix2", pa1);
//	  if (status != 0) {
//	      printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
//	      return(EXIT_FAILURE);
//	  }
//
//	  /* clean up */
//	  mxDestroyArray(pa1);
//	  mxDestroyArray(pa2);
//	  mxDestroyArray(pa3);
//
//	  if (matClose(pmat) != 0) {
//	    printf("Error closing file %s\n",file);
//	    return(EXIT_FAILURE);
//	  }
//
//	  /*
//	   * Re-open file and verify its contents with matGetVariable
//	   */
//	  pmat = matOpen(file, "r");
//	  if (pmat == NULL) {
//	    printf("Error reopening file %s\n", file);
//	    return(EXIT_FAILURE);
//	  }
//
//	  /*
//	   * Read in each array we just wrote
//	   */
//	  pa1 = matGetVariable(pmat, "LocalDouble");
//	  if (pa1 == NULL) {
//	    printf("Error reading existing matrix LocalDouble\n");
//	    return(EXIT_FAILURE);
//	  }
//	  if (mxGetNumberOfDimensions(pa1) != 2) {
//	    printf("Error saving matrix: result does not have two dimensions\n");
//	    return(EXIT_FAILURE);
//	  }
//
//	  pa2 = matGetVariable(pmat, "GlobalDouble");
//	  if (pa2 == NULL) {
//	    printf("Error reading existing matrix GlobalDouble\n");
//	    return(EXIT_FAILURE);
//	  }
//	  if (!(mxIsFromGlobalWS(pa2))) {
//	    printf("Error saving global matrix: result is not global\n");
//	    return(EXIT_FAILURE);
//	  }
//
//	  pa3 = matGetVariable(pmat, "LocalString");
//	  if (pa3 == NULL) {
//	    printf("Error reading existing matrix LocalString\n");
//	    return(EXIT_FAILURE);
//	  }
//
//	  status = mxGetString(pa3, str, sizeof(str));
//	  if(status != 0) {
//	      printf("Not enough space. String is truncated.");
//	      return(EXIT_FAILURE);
//	  }
//	  if (strcmp(str, "MATLAB: the language of technical computing")) {
//	    printf("Error saving string: result has incorrect contents\n");
//	    return(EXIT_FAILURE);
//	  }
//
//	  /* clean up before exit */
//	  mxDestroyArray(pa1);
//	  mxDestroyArray(pa2);
//	  mxDestroyArray(pa3);
//
//	  if (matClose(pmat) != 0) {
//	    printf("Error closing file %s\n",file);
//	    return(EXIT_FAILURE);
//	  }
//	  printf("Done\n");
//	  return(EXIT_SUCCESS);
//}
