/*
 * CvsParser.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#include "CvsParser.h"

CvsParser::CvsParser() {
	// TODO Auto-generated constructor stub

}

CvsParser::~CvsParser() {
	// TODO Auto-generated destructor stub
}

Matrix3D CvsParser::parseCvs3DCerebro(std::string fileName, uint sizeX, uint sizeY, uint sizeZ){
	std::ifstream infile(fileName.data());

	// Check existence
	if(!infile.good()){
		printf("File %s does not exist. Aborting\n",  fileName.data());
		throw new std::runtime_error("File does not exist");
	}

	// skip first line
	std::string firstLine;
	std::getline(infile, firstLine);

	// create empty matrix with corresponding size
	Matrix3D matrix(boost::extents[sizeX][sizeY][sizeZ]);

	// parse the rest of the file
	uint line[4]; // it is a matrix so we know it has exactly 4 values per line
	int x, y, z;
	double value;
	while(CvsParser::parseCvsLine(infile, line)){
		x = line[0]-1; // cvs is 1-based. c++ is 0-based
		y = line[1]-1; // cvs is 1-based. c++ is 0-based
		z = line[2]-1; // cvs is 1-based. c++ is 0-based

		/** Set value according to the TP:
		 * el valor de cada celda debe ser transformado de la siguiente forma para obtener el valor del coeficiente de difusion en ese punto:
		 * Entre 110 y 225: sustancia blanca. D=0.255 mm 2 /d ́ıa
		 *	Entre 75 y 110: sustancia gris. D=0.051 mm 2 /d ́ıa
		 *	Otro caso: D=0
		 */
		value = line[3]; // original value
		if(value >= 110 && value <= 225){ // sustancia blanca
			//printf("Sustancia blanca\n");
			value = 0.255; //mm^2 / dıa
		} else if (value >= 75 && value < 110) {
			//printf("Sustancia gris\n");
			value = 0.051; //mm^2 / dıa
		} else {
			value = 0;
		}

		// set the value for the matrix
		matrix[x][y][z] = value;
	}

	return matrix;
}

bool CvsParser::parseCvsLine(std::istream& str, uint* line)
{
	std::vector<std::string>   result;
	std::string                strLine;
	std::getline(str,strLine);

	std::stringstream          lineStream(strLine);
	std::string                cell;

	bool ret = false;
	int index = 0;
	while(std::getline(lineStream, cell,','))
	{
		line[index] = std::stoi(cell);
		index++;
		ret = true;
	}

	return ret;
}

