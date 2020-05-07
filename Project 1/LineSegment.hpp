/*
LineSegment.hpp
by: Zachary Sasser
----------------------------------------------------------------
Description:
This is a class that allows you to make a line segment object.
A line segment is a object that contains two points.
A line segment is not a line, a line segment has endpoints.
----------------------------------------------------------------
Current Bugs/Issues:
	-BUG FREE (as far as we know) :)
----------------------------------------------------------------
*/
#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "Point.hpp"

template<class DT>
class LineSegment {
	protected:
		Point<DT> P1;
		Point<DT> P2;
	public:
		LineSegment();
		LineSegment(Point<DT> one, Point<DT> two);

		DT length();
		Point<DT> midpoint();
		Point<DT> xIntercept();
		Point<DT> yIntercept();
		Point<DT> getP1();
		Point<DT> getP2();
		DT slope();
		bool onLine(Point<DT> P);
		bool itIntersects(LineSegment<DT> L);
		Point<DT> intersectionPoint (LineSegment<DT> L);
		bool isParallel (LineSegment<DT> L);
		void displayEquation();	
};

//Default Constructor
template<class DT>
LineSegment<DT>::LineSegment(){
	P1 = Point<DT>(0,0);
	P2 = Point<DT>(0,0);
}

//Contructor
template <class DT>
LineSegment<DT>::LineSegment(Point<DT> one, Point<DT> two){
	P1 = one;
	P2 = two;

}

//Finds length of line segment
template<class DT>
DT LineSegment<DT>::length(){
	DT deltaX = absolute(P1.getXValue() - P2.getXValue()); 
	DT deltaY = absolute(P1.getYValue() - P2.getYValue());
	return round(squareroot(power(deltaX,2)+power(deltaY,2))*100)/100;
}

//Finds the midpoint of the line segment and returns a point object
template<class DT>
Point<DT> LineSegment<DT>::midpoint(){
	Point<DT> mid = Point<DT>((P1.getXValue()+P2.getXValue())/2,  //Calculate midpoint x coordinate
							(P1.getYValue()+P2.getYValue())/2); //Calculate midpoint y coordinate
	return mid;
}

//Returns the point where the line intersects the x axis
template<class DT>
Point<DT> LineSegment<DT>::xIntercept(){
	DT x0 = -1*yIntercept().getYValue()/slope(); // y = mx + b -> 0 = mx + b -> b=-mx -b/m = x
	Point<DT> intersept = Point<DT>(x0,0);
	return intersept;
}

//Returns the point where the line intersects the y axis
template<class DT>
Point<DT> LineSegment<DT>::yIntercept(){
	DT y0 = P1.getYValue() - slope()*P1.getXValue(); // y=mx+b -> b = y-mx
	Point<DT> intersept = Point<DT>(0,y0);
	return intersept;
}

//Returns Point 1
template<class DT>
Point<DT> LineSegment<DT>::getP1(){
	return P1;
}

//Returns Point 
template<class DT>
Point<DT> LineSegment<DT>::getP2(){
	return P2;
}

//Returns the slope of the line segment
template<class DT>
DT LineSegment<DT>::slope(){
	return (P1.getYValue()-P2.getYValue())/(P1.getXValue()-P2.getXValue()); // slope = (y1-y2)/(x1-x2)
}

//Returns if the line segment is parralel to the input.
template<class DT>
bool LineSegment<DT>::isParallel(LineSegment<DT> L){
	if(slope() == L.slope()){
		return true;
	}
	else{
		return false;
	}
}

//Returns a point object of the intersection
template<class DT>
Point<DT> LineSegment<DT>::intersectionPoint(LineSegment<DT> L){
	//We can't solve for a intersection if the lines are parralel
	if(isParallel(L)){
		cout << "Lines are Parralel" << endl;
	}

	DT xIntersection = (L.yIntercept().getYValue()-yIntercept().getYValue())/(slope()-L.slope()); // x = (b2-b1)/(m1-m2)
	DT yIntersection = slope() * xIntersection + yIntercept().getYValue(); // mx + b
	Point<DT> intersection = Point<DT>(xIntersection,yIntersection); //Put the values into a point.

	//Make sure that the point is on BOTH of the line segments
	if((!onLine(intersection) || !L.onLine(intersection)) && !isParallel(L)){
		cout << "Lines are not Parralel and not Intersecting" << endl;
	}
	return intersection;
}

//Checks if the point is on the line segment
template<class DT>
bool LineSegment<DT>::onLine(Point<DT> P){
	if(P.getYValue() == slope()*P.getXValue() + yIntercept().getYValue()){ // y1 = m*x1 + b
		//The point is on the extended line.
		if(P.getXValue()>=minima(P1.getXValue(),P2.getXValue()) && P.getXValue()<=maxima(P1.getXValue(),P2.getXValue()) ){
			//The point is in the correct range to be on the SEGMENT not just the line.
			return true;
		} 
		else{
			//The point is on the extended Line but not in the correct range.
			return false;
		}
	}
	else{
		//The point is not even on the extended line.
		return false;
	}
}

//Returns if the line segment intersects with the input line segment object
template<class DT>
bool LineSegment<DT>::itIntersects(LineSegment<DT> L){
	Point<DT> intersection = intersectionPoint(L); //Save computation time by storing this variable;

	if(isParallel(L)){
		return false;
	}

	else if(onLine(intersection) && L.onLine(intersection) ){ //Make sure it is a part of both line segments
		return true;
	}

	else{
		return false;
	}
}

//Prints out an equation of the line segment
template<class DT>
void LineSegment<DT>::displayEquation(){
	cout << "y=" << round(slope()*100)/100 << "*x+" << round(yIntercept().getYValue()*100)/100 << endl; 
}
#endif