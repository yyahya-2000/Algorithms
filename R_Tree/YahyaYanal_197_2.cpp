// R_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
* И.Ф.Г: Яхя Янал БПИ197
* Уровень: 2
*/

#include <iostream>
#include "gdal.h"
#include <fstream>
#include <vector>
#include "ogrsf_frmts.h"
#include <string>
#include <boost/geometry.hpp>


using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
typedef bg::model::box<point_t> box_t;
typedef std::pair<box_t, int> pair_t;
typedef bg::index::rtree<pair_t, bg::index::quadratic<8, 4>> rtree;

// class gets polygon or multipolygon in constructor and creats MBR for it
class MBR {
private:
	double minx = 1000;
	double maxx = -1000;
	double miny = 1000;
	double maxy = -1000;

	// method initializes class fildes with setFildesFromPolygon's help and input param multiPolygon
	void setFildesFromMultiPolygonn(OGRMultiPolygon* multiPolygon) {
		for (auto&& poligon : multiPolygon) {
			setFildesFromPolygon(poligon);
		}
	}

	// method find min(X/Y) and max(X/Y) in one polygon
	void setFildesFromPolygon(OGRPolygon* polygon) {
		auto* exteriorRing = polygon->getExteriorRing();
		for (auto&& point : exteriorRing) {
			if (point.getX() < minx)
				minx = point.getX();
			if (point.getX() > maxx)
				maxx = point.getX();
			if (point.getY() < miny)
				miny = point.getY();
			if (point.getY() > maxy)
				maxy = point.getY();
		}
	}
public:
	// constructor gets one polygon to initialize fildes
	MBR(OGRPolygon* polygon) {
		setFildesFromPolygon(polygon);
	}

	// constructor gets  multipolygon to initialize fildes
	MBR(OGRMultiPolygon* mPolygon) {
		setFildesFromMultiPolygonn(mPolygon);
	}

	// method creates MBR and return it
	box_t* generateBox() {
		return new box_t(point_t(minx, miny), point_t(maxx, maxy));
	}
};


// function help in split the test lines
void split_line(string& line, double* subline) {
	if (line[line.length() - 1] == ' ') {
		line = line.substr(0, line.length() - 1);
	}
	size_t current, previous = 0;
	current = line.find(' ');

	size_t index = 0;
	while (current != string::npos) {
		*(subline + index) = stod(line.substr(previous, current - previous));
		previous = current + 1;
		current = line.find(' ', previous);
		index++;
	}
	*(subline + index) = stod(line.substr(previous, current - previous));
}

// method reads input from test file, and create a box using it
box_t* generateRectangle(string testPath) {
	ifstream myTest;
	myTest.open(testPath);
	if (!myTest) {
		cout << "Unable to open file";
		exit(1);
	}
	string line;
	getline(myTest, line);
	double xYCoordinate[4];
	split_line(line, xYCoordinate);
	return new box_t(point_t(xYCoordinate[0], xYCoordinate[1]),
		point_t(xYCoordinate[2], xYCoordinate[3]));
}

// method reads data of buildings in Moscow and return GDALDataset of it
GDALDataset* GetDataSet(char* arg1) {

	string fileNmae = "\\building-polygon.shp";
	fileNmae = arg1 + fileNmae;
	const char* path = fileNmae.c_str();
	return static_cast<GDALDataset*>(GDALOpenEx(path, GDAL_OF_VECTOR,
		nullptr, nullptr, nullptr));
}

// Driver function to sort the vector elements 
// by second element of pairs 
bool sortbysec(const pair_t a, const pair_t b)
{
	return (a.second < b.second);
}

// insert MBR for all polygons and multipolygons and the ID of the buldings into R-Tree
void insertDataIntoTree(char* arg1, rtree& rTree) {
	MBR* mbr = NULL;
	GDALDataset* dataset = GetDataSet(arg1);
	for (auto&& layer : dataset->GetLayers()) {
		for (auto&& feature : layer) {
			auto* geometry = feature->GetGeometryRef();

			switch (auto geometryType = geometry->getGeometryType()) {

			case wkbPolygon: {

				mbr = new MBR(geometry->toPolygon());

				break;
			}
			case wkbMultiPolygon: {
				mbr = new MBR(geometry->toMultiPolygon());
				break;
			}
			}
			rTree.insert(make_pair(*(mbr->generateBox()), feature->GetFieldAsInteger(0)));
		}
	}
	delete mbr;
	delete[] dataset;
}

// print the result out to the answer file, after sorting the vector,
// which contain the result of intersecting
void printOutput(vector<pair_t>& result_s, char* arg3) {
	sort(result_s.begin(), result_s.end(), sortbysec);
	ofstream out;
	out.open(arg3);
	for (const auto& item : result_s) {
		out << item.second << endl;
	}
}

int main(int argc, char** args)
{
	try {

		GDALAllRegister();
		//box from input test
		box_t* query_box = generateRectangle(args[2]);

		rtree rTree;
		insertDataIntoTree(args[1], rTree);

		vector<pair_t> result_s;
		rTree.query(bgi::intersects(query_box), back_inserter(result_s));//the intersecting process

		printOutput(result_s, args[3]);// print the result out to answer file

		delete query_box;
	}
	catch (exception ex) {
		cout << ex.what() << endl;
	}
	return 0;
}
