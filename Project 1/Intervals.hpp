/*
Intervals.hpp
by: Zachary Sasser
----------------------------------------------------------------
Description:
An interval is essentally a collection of line segments
----------------------------------------------------------------
Current Bugs/Issues:
	-BUG FREE (as far as we know) :)
----------------------------------------------------------------
*/
#ifndef INTERVALS_H
#define INTERVALS_H

#include "LineSegment.hpp"

template<class DT>
class Intervals {
	protected:
		LineSegment<DT>* segments;
		int count;
		int maxSize;
	public:
		Intervals();
		~Intervals();
		Intervals(int size);
		DT getSize();
		LineSegment<DT> getSegment(int index);
		void addLineSegment(LineSegment<DT>& L);
		void display();
};

template<class DT>
Intervals<DT>::Intervals(){
	segments = NULL;
	count = 0;
	maxSize = 0;
}

template<class DT>
Intervals<DT>::~Intervals(){
	//C++ garantees that deleting a NULL pointer will do nothing. So don't worry about the default constructor.
	delete [] segments;
}

template<class DT>
Intervals<DT>::Intervals(int size){
	segments = new LineSegment<DT> [size]; //Create an array to store the object pointers
	count = 0; //Keep track of the number of objects
	maxSize = size; //Keep track of the size of our interval
}

template<class DT>
void Intervals<DT>::addLineSegment(LineSegment<DT>& L){
	//Resize the array (double it)
	if(count>=maxSize){
		LineSegment<DT>* temp = new LineSegment<DT>[maxSize*2];
		for(int i = 0; i<maxSize; i++){
			temp[i] = *(segments+i);
		}
		delete [] segments;
		segments = temp;
	}

	//Add the line segment
	segments[count] = L;
	count++;
}

template<class DT>
DT Intervals<DT>::getSize(){
	return count;
}

template<class DT>
LineSegment<DT> Intervals<DT>::getSegment(int index){
	return segments[index];
}

template<class DT>
void Intervals<DT>::display(){
	//run display function for all line segments
	for(int i = 0; i<count; i++){
		segments[i].displayEquation();
	}
}

#endif