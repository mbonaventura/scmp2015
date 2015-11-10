/*
 * Jacobi.h
 *
 *  Created on: 01/09/2015
 *      Author: mbonaventura
 */

#ifndef MATLAB_HELPERS__H
#define MATLAB_HELPERS__H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h> /* For strcmp() */
#include <stdlib.h> /* For EXIT_FAILURE, EXIT_SUCCESS, system */
#include <vector> /* For STL */
//#include "mat.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "CvsParser.h" // Matrix3D

#define BASE_PATH "/home/matiasb"
//#define BASE_PATH ""

class MatlabHelper {
	#define BUFSIZE 256
	#define MATLAB_FILENAME "variables_scmp.mat"
public:
	//static void WriteVectorToMatLab(const std::vector<double>& vec, std::string vectorName);
	//static void WriteMatrixToMatLab(const std::vector<std::vector<double> >& vec, std::string vectorName);
	static void WriteMatrixToVtk(const std::vector<std::vector<double> >& vec, std::string fileName);
	static void PrintVector(std::vector<double>& vec, double t);
	static void PrintMatrix(std::vector<std::vector<double> >& matrix, double t);
	static void WriteToVtk(const Matrix3D& matrix, std::string fileName);

};

#endif /* MATLAB_HELPERS__H */
