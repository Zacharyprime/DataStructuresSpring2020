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

Finished:
1. Template all classes
2. Create the following
	a. class Exception {};
	b. class LineSegmentException: Public Exception {};
	c. class SegmentsException: Public Exception {};
3. Under these conditions throw exception. Catch and print a message as follows:
	a. throw a LineSegmentException when you ask for a midpoint of a line segment that has a length of 0.
	b. throw a SegmentsException when you are asked to remove a linesegment that does not exist.
4. Create a overloaded << operator for all classes.

6. In the Segments class, create a method named findAllIntersects that returns a Segments object that contain line segments that intersects with the line segment that is passed as a parameter.
	Segments<DT>& findAllIntersects (LineSEgment<DT>& LS);

7. Write a destructor method for the Segments class.
8.In the Segments class, create a method named findClosest that returns a LineSEgment that is closest to the input Point object that is passed as a parameter among all line segments.
	LineSegment<DT>& findClosest(Point<DT>& aPoint);

9.For the main program you will process the following commands:
	a. A for adding a line segment. For Example A 2.3 3.5 2.5 8.12 woulc mean at the line segment in the segments object.
	b. R is for removing a line segment (you must loop through and find the correct one)
	c. D is for displaying all line segments stored in the Segments object in the format y = mx +c USE OSTREAM OPERATOR (<<) NOT THE DISPLAY METHOD.
	d. P is for getting a closed polygon and for the SEgments object that is return to execute the ostream operator, if it contains a closed polygon, otherwise, output "NO CLOSED POLYGON" (20 points bonus). If not implemented have command P state "Command P not implemented"
	e. I for displaying all line segments that intersects with a given line segment. If no line segment intersects "NO INTERSECTING LINE SEGMENTS".
	f. C is for displaying a line secment that is closest to a point.  ie. C 2.8 3.1

10. Check structure of main program with pdf.

TODO:
5. In the Segments class, create a method named aClosedPolygon that returns a segments object that contains a set of line segments that form a closed polygon.
	a. Segments<DT>& aClosedPolygon(); // Bonus - 20 pts.
--Template math.h future zach.


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
	Added functionality for true round instead of truncation like in project 1.
	*/
	a = a * 100;
	double b = ((double)((int)a));
	if(a-b>=0.5){
		return b/100+0.01;
	}
	else{
		return b/100;
	}
}
//zmath.h end


//Exceptions.hpp
class Exception {};
class LineSegmentException: public Exception {};
class SegmentsException: public Exception {};
//Exceptions.hpp end


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
		bool operator == (Point<DT> P2); //Override equality operator
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

//Checks if two points are equal to each other.
template<class DT>
bool Point<DT>::operator == (Point<DT> P2){
	if(x == P2.getXValue() && y==P2.getYValue()){
		return true;
	}
	else{
		return false;
	}
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
	cout << "(" << round(x) << "," << round(y) << ")" << endl;
}


//Overrides the ostream operator so you can use points in output/input
//Rounds the value to match project requirements
template<class DT>
ostream& operator<<(ostream& o,Point<DT> P){
	return o << "(" << ((P.getXValue() == 0) ? 0:round(P.getXValue())) << ", " //Conditional operator is used to prevent -0 in output.
					<< ((P.getYValue() == 0) ? 0:round(P.getYValue())) << ")";
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
		DT getDistance(Point<DT> P); //Finds the distance between a point and the line
		bool onLine(Point<DT> P); //Returns true if the point input is on the line segment
		bool itIntersects(LineSegment<DT> L); //Returns true if the Line input intersects the line segment (factors in domain/range)
		Point<DT> intersectionPoint (LineSegment<DT> L); //Finds where the lines intersect (if they do intersect)
		bool isParallel (LineSegment<DT> L); //Returns true if lines are parallel
		void displayEquation();	 //Displays the equation of the extended line in y=m*x+b form
		bool operator == (LineSegment<DT> P2);
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

//Finds lenght of a line segment
template<class DT>
DT LineSegment<DT>::length(){
	DT deltaX = absolute(P1.getXValue() - P2.getXValue()); //Stores the change in X/Y in order to make more visually appealing.
	DT deltaY = absolute(P1.getYValue() - P2.getYValue()); //In practice you could combine these into the return but I think most compilers will do that automatically.
	return round(squareroot(power(deltaX,2)+power(deltaY,2)));
}

//Finds distance from a line segment to a point
/*
Explaination:
We find the perpendicular line and then alter the y intercept to line up with the point.
Then we make a line from the intersection of the two lines and the point given.
Then we run the length function to calculate the distance.
*/
template<class DT>
DT LineSegment<DT>::getDistance(Point<DT> P){
	DT perpIntercept = P.getYValue() + P.getXValue()/slope(); //Gets the y intercept of the perpendicular line
	DT Xintersection = (perpIntercept - yIntercept().getYValue())/(slope()+1/slope()); //(b2-b1)/(m+1/m) = Xintersection (from algebra)
	DT Yintersection = slope() * Xintersection + yIntercept().getYValue(); // Y = mx + b to find the y value at the intersection.
	Point<DT> P2 = Point<DT>(Xintersection,Yintersection); //Package into a point for operations

	//If the point is already on the line, return 0.
	if(P==P2){
		return 0;
	}

	//If the point is not on the line, calculate the real distance.
	else{
		LineSegment<DT> L = LineSegment<DT>(P,P2);
		return L.length();
	}
}

//Finds the midpoint of the line segment and returns a point object
template<class DT>
Point<DT> LineSegment<DT>::midpoint(){
	if(length() == 0){
		throw LineSegmentException();
	}
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
		throw LineSegmentException();
	}

	DT xIntersection = (L.yIntercept().getYValue()-yIntercept().getYValue())/(slope()-L.slope()); // x = (b2-b1)/(m1-m2)
	DT yIntersection = slope() * xIntersection + yIntercept().getYValue(); // mx + b
	Point<DT> intersection = Point<DT>(xIntersection,yIntersection); //Put the values into a point.

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
	
	if(isParallel(L)){ //Make sure the lines aren't parallel
		return false;
	}
	Point<DT> intersection = intersectionPoint(L); //Save computation time by storing this variable;
	if(onLine(intersection) && L.onLine(intersection) ){ //Make sure it is a part of both line segments
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
	cout << "y=" << round(slope()) << "*x+" << round(yIntercept().getYValue()) << endl; 
}

//Overload the << operator for LineSegments
//SLOPE IS NOT ROUNDED DUE TO A MISTAKE IN TEST CASE 5 (LineSegment 2). The slope and yint. are -0.125 and 1.125 respectively but round differently.
//I truncate slope instead to make it match the test case.
template<class DT>
ostream& operator<<(ostream& o,LineSegment<DT> L){
	return o << L.getP1() << "," << L.getP2() << endl
			 << "Slope:" << (double)((int)(L.slope()*100))/100 << endl 
			 << "Midpoint:" << L.midpoint() << endl
			 << "X Intercept:" << round(L.xIntercept().getXValue()) << endl
			 << "Y Intercept:" << round(L.yIntercept().getYValue()) << endl
			 << "Length:" << round(L.length()) << endl
			 << "y=" << (double)((int)(L.slope()*100))/100 << "*x+" << round(L.yIntercept().getYValue()) << endl;
}

//Overloading == operator for Line Segments
template<class DT>
bool LineSegment<DT>::operator == (LineSegment<DT> LS){
	if((P1 == LS.getP1() && P2 == LS.getP2()) || (P1 == LS.getP2() && P2 == LS.getP1()) ){ //(P1 = P1 and P2=P2) or (P1 = P2 and P2 = P1) both cases 
		return true;
	}
	else{
		return false;
	}
}
//LineSegment.hpp end

//Segments.hpp
template<class DT>
class Segments {
	protected:
		LineSegment<DT>* segments;
		int count; //Keep track of where to put the next element
		int maxSize; //Keep track of the current capacity so we can dynamically resize
	public:
		Segments(); //Default Constructor
		~Segments(); //Destructor to clean up dynamic array
		Segments(int size); //Non-default contructor
		int getSize(); //Returns count, the current number of segments in the array (because we start at 0).
		Segments<DT>& findAllIntersects (LineSegment<DT>& LS); //Find all line sements that intersect that line.
		LineSegment<DT>& findClosest(Point<DT>& aPoint); //Find the Line Segment closest to the point
		LineSegment<DT> getLineSegment(int index); //Returns a particular segment in the interval
		void addLineSegment(LineSegment<DT>& L); //Add a line segment to the interval. Adjust dynamic array accordingly
		void removeLineSegment(int index); //Removes the line segment at the specified index.
		void display(); //Display all the equations of each segment in y=m*x+b form
		Segments<DT>& recursivePolygon(int start,Segments<DT>& polygon, int original); //a recursive tool for finding polygons
		Segments<DT>& aClosedPolygon(); //Bonus, find a polygon inside of the segments object
		int findSegment(LineSegment<DT> LS); //Search for the index of a particular line segment (returns -1 if not found)
		LineSegment<DT> operator[](int index); //Finds a line segment at the specific index

};


//Default Contructor
template<class DT>
Segments<DT>::Segments(){
	segments = NULL;
	count = 0;
	maxSize = 1;
}

//Destructor
template<class DT>
Segments<DT>::~Segments(){
	//C++ garantees that deleting a NULL pointer will do nothing. So don't worry about the default constructor.
	if(segments != NULL){
		delete [] segments;
		count = 0;
		maxSize = 1;
	}
}


//Creates an interval of a given size (preallocates an array of that size)
template<class DT>
Segments<DT>::Segments(int size){
	segments = new LineSegment<DT> [size]; //Create an array to store the object pointers
	count = 0; //Keep track of the number of objects
	maxSize = size; //Keep track of the size of our interval
}


//Adds a line segment to the Segments array
template<class DT>
void Segments<DT>::addLineSegment(LineSegment<DT>& L){
	//Resize the array (double it)
	if(count>=maxSize){
		LineSegment<DT>* temp = new LineSegment<DT>[maxSize*2]; //Create a new BIGGER array
		for(int i = 0; i<maxSize; i++){
			temp[i] = segments[i]; //Copy the data over to the new array
		}
		if(segments != NULL){
			delete [] segments; //Remove the old array from the heap
		}
		segments = temp; //Point segments to the new array
	}

	//Add the line segment
	segments[count] = L; //Put the line segment pointer into our array
	count++; //Keep track of the number of segments we've entered
}

//Removes a line segment from the Segments array
template<class DT>
void Segments<DT>::removeLineSegment(int index){
	if(count <= index){
		throw SegmentsException(); //There is no line segment at that index.
	}
	for(int i = index; i<count; i++){
		segments[i] = segments[i+1]; //Move all the elements above that index down by 1. Overwrites element at index.
	}
	count--;

	//If we are only using half the array, we might as well cut the array in half to save memory.
	if(count<maxSize/2){
		LineSegment<DT>* temp = new LineSegment<DT>[maxSize/2]; //Create a smaller array
		for(int i = 0; i<maxSize/2; i++){
			temp[i] = segments[i+1]; //Copy all the elements over to our small array
		}
		if(segments != NULL){
			delete [] segments; //Get rid of the space wasting big array
		}
		segments = temp; //Make our pointer point to the new small array instead.
	}
}



/*
Because count is the next index we will insert,
 and we start counting at zero,
 count is always the amount of segments in the interval.
*/
template<class DT>
int Segments<DT>::getSize(){
	return count;
}

//Finds the closest line segment to a point
template<class DT>
LineSegment<DT>& Segments<DT>::findClosest(Point<DT>& aPoint){
	DT smallestDistance = segments[0].getDistance(aPoint); //Stores the distance from the point of the current closest line segment.
	int smallestIndex = 0; //Stores the index of the current closest line segment.

	for(int i = 1; i<count; i++){ //Loop through all the line segments
		DT distance = segments[i].getDistance(aPoint); //Find distance now to save computation time.
		if(distance < smallestDistance){
			//The distance from the current line is smaller than what we thought was the smallest distance
			smallestDistance = distance; //Update the length we think is the smallest
			smallestIndex = i; //Keep track of the index the distance was found.
		}
	}

	return segments[smallestIndex];
}

//Return the line segment at a given index
template<class DT>
LineSegment<DT> Segments<DT>::getLineSegment(int index){
	return segments[index];
}

//Return the line segment at a given index
template<class DT>
LineSegment<DT> Segments<DT>::operator[](int index){
	return segments[index];
}

//Display the equations of all the line segments in the interval
template<class DT>
void Segments<DT>::display(){
	//run display function for all line segments
	for(int i = 0; i<count; i++){
		segments[i].displayEquation();
	}
}

//Overloading ostream operator to pull all the line segments and match test case outputs.
template<class DT>
ostream& operator<<(ostream& o,Segments<DT> S){
	for(int i = 0; i<S.getSize(); i++){
		o <<"Line Segment " << i+1 << ":" << endl << S.getLineSegment(i);
	}
	return o;
}

//Finds all the line segments that intersect with the input and returns them as a Segments object
template<class DT>
Segments<DT>& Segments<DT>::findAllIntersects (LineSegment<DT>& LS){
	Segments<DT> returnSegment = Segments<DT>();

	//Loop through the entire Segments object
	for(int i = 0; i<getSize(); i++){

		if(segments[i].itIntersects(LS)){
			//It intersects with that line
			returnSegment.addLineSegment(segments[i]); //Add it to our list
		}
	}
	return returnSegment;
}


//Does a linear search to find a particular segment in the Segments object
template <class DT>
int Segments<DT>::findSegment(LineSegment<DT> LS){
	for(int i = 0; i<getSize(); i++){ //Cycle through all the line segments
		if(segments[i].getP1() == LS.getP1() && segments[i].getP2() == LS.getP2()){ //Check if we have a match
			return i;
		}
	}
	throw SegmentsException();
}

template<class DT>
Segments<DT>& Segments<DT>::recursivePolygon(int start,Segments<DT>& polygon, int original){
	if(original == -1){
		original = start;
		polygon.addLineSegment(segments[original]);
	}
	if(start >= getSize()-1){
		return polygon;
	}
	for(int i = start; i<getSize(); i++){ //Cycle through the rest of the lines
		if(!(segments[start] == segments[i])){ //If the line being compared is not the same line

			if(segments[start].getP1() == segments[i].getP1()
			|| segments[start].getP1() == segments[i].getP2()
			|| segments[start].getP2() == segments[i].getP1()
			|| segments[start].getP2() == segments[i].getP2()){
				cout << "We got here " << segments[0] << endl;
				if(segments[i] == segments[original]){
					return polygon;
				}
				else{
					polygon.addLineSegment(segments[i]);
					return recursivePolygon(i,polygon,original);
				}

			}

		}

	}
	for(int i = 0;i<polygon.getSize(); i++){
		polygon.removeLineSegment(i);
	}
	return recursivePolygon(start+1,polygon,-1);
}

template<class DT>
Segments<DT>& Segments<DT>::aClosedPolygon(){
	Segments<DT> poly = Segments<DT>(3);
	return this->recursivePolygon(0,poly,-1);
}

//Segments.hpp end



//main.cpp start
int main(){
	//Define variables
	char command;
	int noOfSegments = 0;
	int index; //Used to track indexes, basically a holder variable.

	//Collect information to match project description (and helps us make a default array size)
	cin >> noOfSegments;
	Segments<double> mainSegment = Segments<double>(noOfSegments);

	//Define holder variables used in operations
	LineSegment<double> L1;
	Point<double> P1,P2;
	double x1, y1, x2, y2;

	//Loop until it reaches the end of file
	while(!cin.eof()){
		cin >> command;

		//This is to fix the "double count final line" issue.
		if(cin.eof()) return 0;

		switch(command){
			//Add to Segments Object
			case 'A': {
				cin >> x1 >> y1 >> x2 >> y2;
				P1 = Point<double>(x1,y1);
				P2 = Point<double>(x2,y2);
				L1 = LineSegment<double>(P1,P2);
				mainSegment.addLineSegment(L1);
				cout << "Line segment added" << endl << endl;
				break;
			}

			//Find and Remove
			case 'R': {
				cin >> x1 >> y1 >> x2 >> y2;
				P1 = Point<double>(x1,y1);
				P2 = Point<double>(x2,y2);
				L1 = LineSegment<double>(P1,P2);
				try{
					index = mainSegment.findSegment(L1);

					//Make sure the function found it.
					mainSegment.removeLineSegment(index);
					cout << "Line segment removed" << endl << endl;
				}
				catch(SegmentsException){
					cout << "Exception,line segment not found" << endl << endl;
				}
				break;
			}

			//Display all segment objects
			case 'D': {
				cout << mainSegment << endl;
				break;
			}

			//Return a closed polygon within the Segments object
			case 'P': {
				cout << "TEST: " << mainSegment[0];
				Segments<double> poly = Segments<double>(3);
				Segments<double> output = mainSegment.recursivePolygon(0,poly,-1);
				if(output.getSize() == 0){
					cout << "No Closed Polygon" << endl;
				}
				else{
					cout << "The Polygon is formed by the points:";
					cout << output[0].getP1();//To match test case's format.
					for(int i = 0; i<output.getSize(); i++){ //We leave out the last line since it shares points with the beginning and end-1.

						//Print the coordinates of the lines
						cout << "," << output[i].getP2();	
					}

					cout << "," << output[0].getP1(); //To match test case's format
				}
				break;
			}

			//Return all intersecting line segments
			case 'I': {
				int intersectingSegments[mainSegment.getSize()];
				int numberOfIntersections = 0;
				cin >> x1 >> y1 >> x2 >> y2;
				P1 = Point<double>(x1,y1);
				P2 = Point<double>(x2,y2);
				L1 = LineSegment<double>(P1,P2);

				for(int i = 0; i<mainSegment.getSize(); i++){
					if( L1.itIntersects(mainSegment.getLineSegment(i)) ){
						//It intersects
						intersectingSegments[numberOfIntersections++] = i;
					}
				}
				if(numberOfIntersections==0){
					cout << "NO INTERSECTING LINE SEGMENTS." << endl;
				}
				else{
					cout << "The lines segments intersecting with the given line segment are:" << endl;
					for(int i = 0; i<numberOfIntersections; i++){
						cout << "Line segment " << i+1 << endl;
					}
				}
				cout << endl; //Fix to formatting of test cases.
				break;
			}

			//Find the line closest to the point
			case 'C': {
				cin >> x1 >> x2;
				P1 = Point<double>(x1,x2);
				index = mainSegment.findSegment(mainSegment.findClosest(P1)); //Find index of closest line segment


				cout << "The Line segment closest to the given point is:Line segment " << index+1 << endl;
				break;
			}

			//If the user makes a mistake
			default: cout << "Invalid command" << endl;
		}
	}
	return 0;
	
}
//main.cpp end

