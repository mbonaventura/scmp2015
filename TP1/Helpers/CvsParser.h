/*
 * CvsParser.h
 *
 *  Created on: Oct 20, 2015
 *      Author: matiasb
 */

#ifndef CVSPARSER_H_
#define CVSPARSER_H_

#include <fstream>
#include <sstream>
#include <string>
#include "boost/multi_array.hpp"

typedef boost::multi_array<double, 3> Matrix3D;

class CvsParser {
public:
	CvsParser();
	virtual ~CvsParser();

	static Matrix3D parseCvs3DCerebro(std::string fileName, uint sizeX, uint sizeY, uint sizeZ);
private:
	static bool parseCvsLine(std::istream& str, uint* line);
};

#endif /* CVSPARSER_H_ */
