/*
Point.hpp
by: Zachary Sasser
----------------------------------------------------------------
Description:
	This is a class that allows you to make a point object.
----------------------------------------------------------------
Current Bugs/Issues:
	-BUG FREE (as far as we know) :)
----------------------------------------------------------------
*/

#ifndef POINT_H
#define POINT_H

#include <iostream> //Standard C Library
#include "zmath.h" //My Library

using namespace std;

template<class DT>
class Point {
	protected:
		DT x;
		DT y;

	public:
		Point (); //Default Constructor
		Point (DT xVal, DT yVal);

		void setLocation (DT xVal, DT yVal);
		void operator= (Point<DT> P2);
		DT getXValue();
		DT getYValue();
		void display();
};

//Creates a default point at the origin
template<class DT>
Point<DT>::Point(){
	x = 0;
	y = 0;
}

//Creates a point at the input coordinate
template<class DT>
Point<DT>::Point(DT xVal, DT yVal){
	x = xVal;
	y = yVal;
}

//Sets a point's coordinate
template<class DT>
void Point<DT>::setLocation(DT xVal, DT yVal){
	x = xVal;
	y = yVal;
}

template<class DT>
void Point<DT>::operator = (Point<DT> P2){
	x = P2.getXValue();
	y = P2.getYValue();
}

//Returns the x coordinate of the point
template<class DT>
DT Point<DT>::getXValue(){
	return x;
}

//Returns the y coordinate of the point
template<class DT>
DT Point<DT>::getYValue(){
	return y;
}

//Displays the point to the console
template<class DT>
void Point<DT>::display(){
	cout << "(" << round(x*100)/100 << "," << round(y*100)/100 << ")" << endl;
}

template<class DT>
ostream& operator<<(ostream& o,Point<DT> P){
	return o << "(" << ((P.getXValue() == 0) ? 0:round(P.getXValue()*100)/100) << ", " //Conditional operator is used to prevent -0 in output.
					<< ((P.getYValue() == 0) ? 0:round(P.getYValue()*100)/100) << ")";
}

#endif 