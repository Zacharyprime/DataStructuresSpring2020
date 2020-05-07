//Standard C Libraries
#include <iostream>
using namespace std;

/*
Assignment:Project 1
Course: CS 2813: Datastructures
Section: 001
Author:Zachary Sasser (113447344)

Notes:
I originally had this project split up into 4 header files with the necessary include guards but then I combined it at the end.
Please keep this in mind as you grade it.

I hope we are doing headers in the next project.
*/

//zmath.h
//Makes the number positive. AKA returns the absolute value.
double absolute(double val){
	if(val<0){
		//If it's negative, make it positive
		val *= -1;
	}
	return val;
}

//returns the *base* raised to the *exponent* power
double power(double base, double exponent){
	double final = 1;
	for(int i = 0; i<exponent; i++){//Multiply base exponent times
		final *= base;
	}
	return final;
}

//Returns "an approximation" of the square root. 
//I think this is called the "babylonian method"? but I may be thinking of something else.
double squareroot(double n){

  //Start with a guess (mid) and a range (high,low)
  double low = 0;
  double high = n;
  double mid = (high + low)/2;

  for (int i = 0; i<2500; i++){ //2500 seems to get close enough in my testing
  	//Calculate our guess
  	mid = (high+low)/2;

  	if(mid*mid > n){
  		//if the guess is too big, make it smaller by making it the new high
  		high=mid;
  	}
  	else if(mid*mid < n){
  		//If our guess was too low, make it bigger by making it the new low
  		low = mid;
  	}
  	else{
  		//If we got the correct answer, return it.
  		return mid;
  	}
  }
  //I just added this in case something breaks so that we will still get an approximation.
  return mid;
}


//Returns the number that is bigger
double maxima(double a, double b){
	if(a>=b){
		//a is bigger so a is max
		return a;
	}
	else{
		//a wasn't bigger so b is max
		return b;
	}
}

//Returns the smaller number
double minima(double a, double b){
	if(a<=b){
		//a was smaller so a is the min
		return a;
	}
	else{
		//a wasn't smaller so b is the min
		return b;
	}
}

double round(double a){
	/*
	Truncate by converting the double to an int.
	Convert back to double to preserve datatype.
	This works better than a modulus based round for the way the output test seems to be formatted.
	*/
	return (double)((int)a);
}
//zmath.h end

//Point.hpp

template<class DT>
class Point {
	protected:
		DT x;
		DT y;

	public:
		Point (); //Default Constructor
		Point (DT xVal, DT yVal); //Optional Contructor

		void setLocation (DT xVal, DT yVal); //Change the point's coordinates
		void operator= (Point<DT> P2); //Override the = operator to work for point objects
		DT getXValue(); //Returns the x coordinate
		DT getYValue(); //Returns the y coordinate
		void display(); //Displays the point in the form  (x, y)
};

//Creates a default point at the origin
template<class DT>
Point<DT>::Point(){
	x = 0; //Defaults zero, this constructor is ideally unused for non-number datatypes.
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

//Sets the point on the LHS to the values of the point on the RHS of the = operator
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


//Overrides the ostream operator so you can use points in output/input
//Rounds the value to match project requirements
template<class DT>
ostream& operator<<(ostream& o,Point<DT> P){
	return o << "(" << ((P.getXValue() == 0) ? 0:round(P.getXValue()*100)/100) << ", " //Conditional operator is used to prevent -0 in output.
					<< ((P.getYValue() == 0) ? 0:round(P.getYValue()*100)/100) << ")";
}
//Point.hpp end


//LineSegment.hpp

template<class DT>
class LineSegment {
	protected:
		Point<DT> P1;
		Point<DT> P2;

	public:
		LineSegment(); //Default Constructor
		LineSegment(Point<DT> one, Point<DT> two); //Optional Contructor

		DT length(); //Computes the length of the line segment
		Point<DT> midpoint(); //Computes the midpoint of the line segment (unrounded)
		Point<DT> xIntercept(); //Computes the x intersept of the extended line
		Point<DT> yIntercept(); //Computes the y intersept of the extended line
		Point<DT> getP1(); //returns arbitary Point 1
		Point<DT> getP2(); //returns arbitary Point 2
		DT slope(); //Returns the slope of the extended line
		bool onLine(Point<DT> P); //Returns true if the point input is on the line segment
		bool itIntersects(LineSegment<DT> L); //Returns true if the Line input intersects the line segment (factors in domain/range)
		Point<DT> intersectionPoint (LineSegment<DT> L); //Finds where the lines intersect (if they do intersect)
		bool isParallel (LineSegment<DT> L); //Returns true if lines are parallel
		void displayEquation();	 //Displays the equation of the extended line in y=m*x+b form
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
	DT deltaX = absolute(P1.getXValue() - P2.getXValue()); //Stores the change in X/Y in order to make more visually appealing.
	DT deltaY = absolute(P1.getYValue() - P2.getYValue()); //In practice you could combine these into the return but I think most compilers will do that automatically.
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
	Point<DT> intersept = Point<DT>(x0,0); //Put the xIntercept into a point object to match project requirements
	return intersept;
}

//Returns the point where the line intersects the y axis
template<class DT>
Point<DT> LineSegment<DT>::yIntercept(){
	DT y0 = P1.getYValue() - slope()*P1.getXValue(); // y=mx+b -> b = y-mx
	Point<DT> intersept = Point<DT>(0,y0); //Put the yIntercept into a point object to match project requirements
	return intersept;
}

//Returns Point 1
template<class DT>
Point<DT> LineSegment<DT>::getP1(){
	return P1;
}

//Returns Point 2
template<class DT>
Point<DT> LineSegment<DT>::getP2(){
	return P2;
}

//Returns the slope of the line segment
template<class DT>
DT LineSegment<DT>::slope(){
	return (P1.getYValue()-P2.getYValue())/(P1.getXValue()-P2.getXValue()); // slope = (y1-y2)/(x1-x2) = deltaY/deltaX
}

//Returns if the line segment is Parallel to the input.
template<class DT>
bool LineSegment<DT>::isParallel(LineSegment<DT> L){
	if(slope() == L.slope()){
		//The lines are parallel
		return true;
	}
	else{
		//The lines are non-parallel
		return false;
	}
}

//Returns a point object of the intersection
template<class DT>
Point<DT> LineSegment<DT>::intersectionPoint(LineSegment<DT> L){
	//We can't solve for a intersection if the lines are Parallel
	if(isParallel(L)){
		cout << "Lines are Parallel" << endl;
	}


	DT xIntersection = (L.yIntercept().getYValue()-yIntercept().getYValue())/(slope()-L.slope()); // x = (b2-b1)/(m1-m2)
	DT yIntersection = slope() * xIntersection + yIntercept().getYValue(); // mx + b
	Point<DT> intersection = Point<DT>(xIntersection,yIntersection); //Put the values into a point.

	//Make sure that the point is on BOTH of the line segments, not just the extended lines
	if((!onLine(intersection) || !L.onLine(intersection)) && !isParallel(L)){
		cout << "Not Parallel and not Intersecting" << endl;
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

	if(isParallel(L)){ //Make sure the lines aren't parallel
		return false;
	}

	else if(onLine(intersection) && L.onLine(intersection) ){ //Make sure it is a part of both line segments
		//The lines intersect and at a point in the range
		return true;
	}

	else{
		//The lines intersect but not within the range
		return false;
	}
}

//Prints out an equation of the line segment
template<class DT>
void LineSegment<DT>::displayEquation(){
	//y=m*x+b (rounded to match project requirements)
	cout << "y=" << round(slope()*100)/100 << "*x+" << round(yIntercept().getYValue()*100)/100 << endl; 
}
//LineSegment.hpp end

//Intervals.hpp
template<class DT>
class Intervals {
	protected:
		LineSegment<DT>* segments;
		int count; //Keep track of where to put the next element
		int maxSize; //Keep track of the current capacity so we can dynamically resize
	public:
		Intervals(); //Default Constructor
		~Intervals(); //Destructor to clean up dynamic array
		Intervals(int size); //Non-default contructor
		DT getSize(); //Returns count, the current number of segments in the array (because we start at 0).
		LineSegment<DT> getSegment(int index); //Returns a particular segment in the interval
		void addLineSegment(LineSegment<DT>& L); //Add a line segment to the interval. Adjust dynamic array accordingly
		void display(); //Display all the equations of each segment in y=m*x+b form
};


//Default Contructor
template<class DT>
Intervals<DT>::Intervals(){
	segments = NULL;
	count = 0;
	maxSize = 0;
}

//Destructor
template<class DT>
Intervals<DT>::~Intervals(){
	//C++ garantees that deleting a NULL pointer will do nothing. So don't worry about the default constructor.
	delete [] segments;
}


//Creates an interval of a given size (preallocates an array of that size)
template<class DT>
Intervals<DT>::Intervals(int size){
	segments = new LineSegment<DT> [size]; //Create an array to store the object pointers
	count = 0; //Keep track of the number of objects
	maxSize = size; //Keep track of the size of our interval
}


//Adds a line segment to the interval
template<class DT>
void Intervals<DT>::addLineSegment(LineSegment<DT>& L){
	//Resize the array (double it)
	if(count>=maxSize){
		LineSegment<DT>* temp = new LineSegment<DT>[maxSize*2]; //Create a new BIGGER array
		for(int i = 0; i<maxSize; i++){
			temp[i] = *(segments+i); //Copy the data over to the new array
		}
		delete [] segments; //Remove the old array from the heap
		segments = temp; //Point segments to the new array
	}

	//Add the line segment
	segments[count] = L; //Put the line segment pointer into our array
	count++; //Keep track of the number of segments we've entered
}

/*
Because count is the next index we will insert,
 and we start counting at zero,
 count is always the amount of segments in the interval.
*/
template<class DT>
DT Intervals<DT>::getSize(){
	return count;
}

//Return the line segment at a given index
template<class DT>
LineSegment<DT> Intervals<DT>::getSegment(int index){
	return segments[index];
}

//Display the equations of all the line segments in the interval
template<class DT>
void Intervals<DT>::display(){
	//run display function for all line segments
	for(int i = 0; i<count; i++){
		segments[i].displayEquation();
	}
}
//Intervals.hpp end



//main.cpp start
int main(){

	//Initialize our static variable
	double x1,y1,x2,y2;
	Point<double> P1,P2;
	LineSegment<double> L1;
	int numOfSeg = 0; 

	//Retrieve the number of segments the user is going to input
	cin >> numOfSeg; 

	//Create the corrosponding interval to store those segments. 
	//This avoids wasting resources dynamically resizing.
	Intervals<double> segments = Intervals<double>(numOfSeg); 

	//Collect the datapoints from the user for each segment.
	for(int i = 0; i<numOfSeg; i++){
		//Collect Data
		cin >> x1 >> y1 >> x2 >> y2;

		//Put into points
		P1 = Point<double>(x1,y1);
		P2 = Point<double>(x2,y2);

		//Put points into a segment
		L1 = LineSegment<double>(P1,P2);

		//Add the segment to our interval
		segments.addLineSegment(L1);
	}

	//Print out the information given in the output case test.
	for(int i = 0; i<segments.getSize(); i++){
		cout << "Line Segment " << i+1 << ":" << endl; //Line Segment #:
		cout << segments.getSegment(i).getP1() << "," << segments.getSegment(i).getP2() << endl; // (#, #),(#, #)
		cout << "Slope:" << round(segments.getSegment(i).slope()*100)/100 << endl; //Slope:#
		cout << "Midpoint:" << segments.getSegment(i).midpoint() << endl; //Midpoint:(#, #)
		cout << "X Intercept:" << round(segments.getSegment(i).xIntercept().getXValue()*100)/100 << endl; //X Intercept:#
		cout << "Y Intercept:" << round(segments.getSegment(i).yIntercept().getYValue()*100)/100 << endl; //Y Intercept:#
		cout << "Length:" << round(segments.getSegment(i).length()*100)/100 << endl; //Length:#
		segments.getSegment(i).displayEquation(); //Displays the equation for the segment
	}
	

	//Loop through all possible intersections and see if they intersect or not, then return the intersection point.
	for(int i = 0; i<segments.getSize(); i++){
		//Grab the line segment i before the for loop to save computation time
		L1 = segments.getSegment(i);

		for(int b = i; b<segments.getSize(); b++){ //b starts at i because everything >= i has already been checked.
			LineSegment<double> L2 = segments.getSegment(b);

			if(i != b){//Removes the case where we are pulling two of the same segments
				cout << "The line segments compared are segments[" << i << "] and segments[" << b << "]: ";

				if(L1.itIntersects(L2)){
					//Check if they intersect (the itIntersects() function will handle the string outputs)
					cout << "Intersection Point :" << L1.intersectionPoint(L2) << endl;
				}
			}
		}
	}


	
}
//main.cpp end

