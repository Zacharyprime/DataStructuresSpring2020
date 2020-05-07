#include <iostream>
using namespace std;


//GLRow Class Definition Start
template<class DT>
class GLRow; //Class prototype

template<class DT>
ostream& operator<<(ostream& s, GLRow<DT>& oneGLRow);

template<class DT>
class GLRow {
	//Adding <> after operator<< tells the compiler that we've defined the template above.
	friend ostream& operator<<<>(ostream& s, GLRow<DT>& oneGLRow);
	
	protected:
		DT* _Info;
		int _Next;
		int _Down;
	public:
		GLRow(); //Default Constructor
		GLRow(const DT& newInfo); //Basic Constructor
		GLRow(GLRow<DT>& anotherOne); //Copy Constructor

		//Make sure this is a deep copy
		void operator = (GLRow<DT>& anotherOne); //Overloaded = operator
		int getNext(); //Return address of next node
		int getDown(); //Return address of lower node (row)
		DT& getInfo(); //Return data inside current node
		void setNext(const int n); //Set the next node address
		void setDown(const int d); //Set the down node address
		void setInfo(DT x); //Set the data that is stored in the node
		~GLRow(); //Destructor
};

template<class DT>
GLRow<DT>::GLRow(){
	_Info = new DT(999);
	_Next = -1;
	_Down = -1;
}

template<class DT>
GLRow<DT>::GLRow(const DT& newInfo){
	_Info = new DT(newInfo);
	_Next = -1;
	_Down = -1;
}

template<class DT>
GLRow<DT>::GLRow(GLRow<DT>& anotherOne){
	_Info = anotherOne.getInfo();
	_Next = anotherOne.getNext();
	_Down = anotherOne.getDown();
}

template<class DT>
ostream& operator<<(ostream& s, GLRow<DT>& oneGLRow){
	return s << oneGLRow.getInfo() << " | " << oneGLRow.getNext() << " | " << oneGLRow.getDown();
}

//Remember this is a DEEP COPY
template<class DT>
void GLRow<DT>::operator=(GLRow<DT>& anotherOne){
	if(_Info != NULL) delete _Info;
	_Info = new DT(anotherOne.getInfo());
	_Next = anotherOne.getNext(); 
	_Down = anotherOne.getDown();
}

template<class DT>
int GLRow<DT>::getNext(){
	return _Next;
}

template<class DT>
int GLRow<DT>::getDown(){
	return _Down;
}

template<class DT>
DT& GLRow<DT>::getInfo(){
	return *_Info;
}

template<class DT>
void GLRow<DT>::setNext(const int n){
	_Next = n;
}

template<class DT>
void GLRow<DT>::setDown(const int d){
	_Down = d;
}

template<class DT>
void GLRow<DT>::setInfo(DT x){
	*_Info = x;
}

template<class DT>
GLRow<DT>::~GLRow(){
	delete _Info;
}

//GLRow Class Definition End


//ArrayGLL Class Definition Start
template<class DT>
class ArrayGLL; //Class prototype

template<class DT>
ostream& operator<<(ostream& s, ArrayGLL<DT>& OneGLL);

template<class DT>
class ArrayGLL {
	//Adding <> after operator<< tells the compiler that we've defined the template above.
	friend ostream& operator<<<>(ostream& s, ArrayGLL<DT>& OneGLL);
	protected:
		GLRow<DT>* myGLL;
		int maxSize;
		int firstElement = 2;
		int firstFree = 8;
	public:
		ArrayGLL();
		ArrayGLL(int size);
		ArrayGLL(ArrayGLL<DT>& anotherOne);
		ArrayGLL<DT>& operator=(ArrayGLL<DT>& anotherOne);

		//10% BONUS
		void display(int pos);
		void display(); //Display in parenthesis format 10% bonus
		
		int find(const DT& key); //return index position where you find element "key", return -1 if not found. Recursive searches only.
		int find(int pos, const DT& key); //+helper that allows recursion

		int findDisplayPath(int pos,const DT& key);
		int findDisplayPath(const DT& key); //as you travel through the tree print the values of nodes encountered. If the element is there you will print all of the values.
		
		int noFree(); //return number of free locations, you need to follow _Next and get the free locations.
		int size(); //Return total number of elements stored
		
		int size(int pos); //+Helper function for recursion

		bool isSibling(int pos,const DT& key);

		//10% BONUS
		int parentPos(int pos, int index, const DT& key);
		int parentPos(const DT& key); //Provide the location of the parent of the element Key in the array

		GLRow<DT>& operator[](int pos);//Returns the GLRow in that position
		int getFirstFree();
		int getFirstElement();
		int getMaxSize();
		void setFirstFree(int pos);
		void setFirstElement(int pos);
		~ArrayGLL(); //Destructor

		//Added Project 4
		void insertAChild (const DT& parent,const DT& child);
		void removeANode (const DT& node);

		void clean(); //Sets the entire array to an empty array;
};

template<class DT>
ArrayGLL<DT>::ArrayGLL(){
	myGLL = NULL;
	maxSize = 0;
}

template<class DT>
ArrayGLL<DT>::ArrayGLL(int size){
	myGLL = new GLRow<DT>[size];
	maxSize = size;
}

template<class DT>
ArrayGLL<DT>::ArrayGLL(ArrayGLL<DT>& anotherOne){
	//Set all variables
	firstFree = anotherOne.getFirstFree();
	firstElement = anotherOne.getFirstElement();
	maxSize = anotherOne.getMaxSize();

	//Delete old array (using delete [] causes a crash?)
	if(myGLL != NULL) delete myGLL;

	//Create new Array
	myGLL = new GLRow<DT>[maxSize];

	//Copy all the data over
	for(int i = 0; i<maxSize; i++){
		myGLL[i] = anotherOne[i];
	}
}

template<class DT>
ArrayGLL<DT>& ArrayGLL<DT>::operator=(ArrayGLL<DT>& anotherOne){
	firstFree = anotherOne.getFirstFree();
	firstElement = anotherOne.getFirstElement();
	maxSize = anotherOne.getMaxSize();
	if(myGLL != NULL) delete myGLL;
	myGLL = new GLRow<DT>(maxSize);
	for(int i = 0; i<maxSize; i++){
		myGLL[i] = anotherOne[i];
	}
}

template<class DT>
ostream& operator<<(ostream& s, ArrayGLL<DT>& OneGLL){
	s << "Info | Next | Down" << endl;
	for (int i = 0; i<OneGLL.getMaxSize(); i++){
		s << OneGLL[i] << endl;
	}
	return s;
}

template<class DT>
void ArrayGLL<DT>::display(int pos){
	//Make sure the position isn't an end
	if(pos != -1){

		//Print out the node we just visited
		cout << myGLL[pos].getInfo() << " ";

		//Go visit the kids
		if(myGLL[pos].getDown() != -1){
			cout << "(";
			display(myGLL[pos].getDown());
			cout << ") ";
		}

		//Go visit your siblings
		if(myGLL[pos].getNext() != -1){
			display(myGLL[pos].getNext());
		}
	}
}

template<class DT>
void ArrayGLL<DT>::display(){
	display(firstElement);
	cout << endl;
}

template<class DT>
int ArrayGLL<DT>::findDisplayPath(int pos,const DT& key){
	//Make sure we aren't trying to search a "Null" (pos = -1) route
	if(pos == -1){
		return pos;
	}
	else{
		cout <<  myGLL[pos].getInfo() << " "; //Display the path we took
	}

	//Check if this is the correct information
	if(myGLL[pos].getInfo() == key){ 
		return pos;
	}

	//check is used as a holder to determine if we should check the next node or not.
	if(myGLL[pos].getDown() != -1){
		cout << "(";
	}

	//check if the children have the key
	int check = findDisplayPath(myGLL[pos].getDown(),key);
	if(myGLL[pos].getDown() != -1){
		cout << ")";
	}

	//If our children couldn't find it, check siblings
	if(check == -1){
		return findDisplayPath(myGLL[pos].getNext(),key);
	}

	//If we already found it, then we shouldn't bother checking the next node.
	else{
		return check;
	}
	
}

template<class DT>
int ArrayGLL<DT>::findDisplayPath(const DT& key){
	//index is necessary so that we can put a endl marker.
	int index = findDisplayPath(firstElement,key); 
	cout << endl;
	return index;
}

template<class DT>
int ArrayGLL<DT>::find(int pos,const DT& key){
	if(pos == -1 || myGLL[pos].getInfo() == key){ //Left side of || will be evaluated first, avoiding error
		return pos;
	}

	//check is used as a holder to determine if we should check the next node or not.
	int check = find(myGLL[pos].getDown(),key);
	if(check < 0){
		return find(myGLL[pos].getNext(),key);
	}
	//If we already found it, then we shouldn't bother checking the next node.
	else{
		return check;
	}
	
}

template<class DT>
int ArrayGLL<DT>::find(const DT& key){
	return find(firstElement,key);
}

template<class DT>
GLRow<DT>& ArrayGLL<DT>::operator[](int pos){
	return myGLL[pos];
}

template<class DT>
int ArrayGLL<DT>::getMaxSize(){
	return maxSize;
}

template<class DT>
int ArrayGLL<DT>::getFirstElement(){
	return firstElement;
}

template<class DT>
int ArrayGLL<DT>::getFirstFree(){
	return firstFree;
}

template<class DT>
void ArrayGLL<DT>::setFirstElement(int pos){
	firstElement = pos;
}

template<class DT>
void ArrayGLL<DT>::setFirstFree(int pos){
	firstFree = pos;
}

//This function exists to calculate the size recursively
template<class DT>
int ArrayGLL<DT>::size(int pos){
	//If there are no children, we check our siblings
	if(myGLL[pos].getDown() == -1){

		//If we don't have siblings, return 1
		if(myGLL[pos].getNext() == -1){
			return 1;
		}
		//If we have a sibling, return it's size
		else{
			return 1 + size(myGLL[pos].getNext());
		}
	}

	//If we don't have a sibling but we do have children
	else if(myGLL[pos].getNext() == -1){
		return 1 + size(myGLL[pos].getDown());
	}

	//If we have both children and siblings, add their sizes to get the total size;
	else{
		return 1 + size(myGLL[pos].getDown()) + size(myGLL[pos].getNext());
	}
}

template<class DT>
int ArrayGLL<DT>::size(){
	return size(firstElement);
}

template<class DT>
int ArrayGLL<DT>::noFree(){
	return size(firstFree);
}

template<class DT>
ArrayGLL<DT>::~ArrayGLL(){
	delete [] myGLL;
}

template<class DT>
bool ArrayGLL<DT>::isSibling(int pos, const DT& key){
	if(myGLL[pos].getInfo() == key){
		return true; //Count self as sibling
	}

	else if(myGLL[pos].getNext() == -1){
		return false;
	}

	else{
		return isSibling(myGLL[pos].getNext(), key);
	}
}

//Finds what index points to the given index
template<class DT>
int ArrayGLL<DT>::parentPos(int pos, int index, const DT& key){
	//Make sure that the key even exists in the tree
	if(index == -1){
		return -1;
	}

	//Check to see if this is the parent node of the search item
	if(isSibling(myGLL[pos].getDown(),key)){
		return pos;
	}

	//Check to see if the child of this node is the parent of the search item (recursion)
	else if(find(myGLL[pos].getDown(),key) != -1){
		return parentPos(myGLL[pos].getDown(),index,key);
	}

	//Check to see if the sibling is the parent.
	else{
		return parentPos(myGLL[pos].getNext(),index,key);
	}
}

template<class DT>
int ArrayGLL<DT>::parentPos(const DT& key){
	return parentPos(firstElement,find(key),key);
}

template<class DT>
void ArrayGLL<DT>::insertAChild (const DT& parent,const DT& child){

	//Make sure we have space to add it in.
	if(firstFree != -1){
		//Put data into our new node
		myGLL[firstFree].setInfo(child);

		//Keep track of the place we just put stuff into.
		int childLocation = firstFree; 

		//Set the new free element
		firstFree = myGLL[firstFree].getNext();


		//Find the parent we are adding to
		int parentIndex = find(parent);

		//If we are inserting at the root, there won't be children to worry about.
		if(parentIndex != -1){
			//Set the Child to have the previous down as a sibling
			myGLL[childLocation].setNext(myGLL[parentIndex].getDown());

			//Set the Down of the parent to our new child
			myGLL[parentIndex].setDown(childLocation);
		}

		else{
			//Sets this as the new root.
			firstElement = childLocation; 
			myGLL[childLocation].setNext(-1);
			myGLL[childLocation].setDown(-1);

		}


	}

}

template<class DT>
void ArrayGLL<DT>::removeANode (const DT& node){
	//Find what node we are trying to remove
	int removeIndex = find(node);

	//Find the leaf node we are going to put in it's place (Traverse leftward).
	int currentIndex = removeIndex; //Track the parent
	int nextIndex = myGLL[removeIndex].getDown(); //Track the node we are on

	int parentIndex = parentPos(node); //Track the potential leaf


	while(nextIndex != -1){
		parentIndex = currentIndex; //Track the parent
		currentIndex = nextIndex; //Track the node we are on
		nextIndex = myGLL[nextIndex].getDown(); //Track the potential leaf
	}



	//Copy the data inside the leaf node to the place we are removing (effectively removes the node).
	myGLL[removeIndex].setInfo(myGLL[currentIndex].getInfo());

	//Inform the parent that we have deleted their child and they need to readjust their favorites (shift the siblings of the leaf node over)
	myGLL[parentIndex].setDown(myGLL[currentIndex].getNext());

	//Remove the leaf node we moved over to the removed node.
	myGLL[currentIndex].setNext(firstFree); //Set it to point to the "first" free node
	myGLL[currentIndex].setDown(-1); //Free nodes don't have downs
	firstFree = currentIndex; //Set that element to be the new first free node (avoids traversing free node LinkedList)
}
//ArrayGLL Class Definition End



//MAIN Start
int main(){
	//--INITIAL SETUP--
	int noElements;
	cin >> noElements; //Take the number of elements being input
	cout << "The size of the array is " << noElements << endl;

	//Define our container
	ArrayGLL<int> tree(noElements);

	//Make it so that the entire thing is free space.
	tree.setFirstFree(0);
	tree.setFirstElement(-1);

	//Go through the entire array and turn it into all free space (allocate space)
	GLRow<int> oneRow(0); //Note this is static
	for(int i=1; i<noElements; i++){
		oneRow.setInfo(999);
		oneRow.setNext(i);
		oneRow.setDown(-1);
		tree[i-1] = oneRow;
	}

	//Fix the final element to be the end of the free space
	oneRow.setInfo(999);
	oneRow.setNext(-1);
	oneRow.setDown(-1);
	tree[noElements-1] = oneRow; 

	/* TESTING STUFF
	tree.insertAChild(-1,90);
	tree.insertAChild(90,80);
	tree.insertAChild(90,70);
	tree.insertAChild(90,60);
	tree.insertAChild(60,20);
	cout << tree << endl;

	tree.removeANode(60);

	cout << tree << endl;
	*/


	//--ENTRY TERMINAL CODE--
	char command;
	int param1, param2;
	while(!cin.eof()){

		//Take input
		cin >> command;

		//Fixes the duplication of the final line
		if(cin.eof()) return 0; 


		switch(command){
			case 'I': {
				cin >> param1 >> param2;
				tree.insertAChild(param1, param2);
				cout << "Element inserted" << endl;
				break;
			}
			case 'D':{
				tree.display();
				break;
			}
			case 'F':{
				cin >> param1;
				cout << "The element " << param1 << " is found at index: " << tree.find(param1) << endl;
				break;
			}
			case 'P':{
				cin >> param1;
				cout << "The parent of " << param1 << " is: " << tree[tree.parentPos(param1)].getInfo() << endl;
				break;
			}
			case 'R':{
				cin >> param1;
				tree.removeANode(param1);
				cout << "Element removed" << endl;
				break;
			}
		}
	}
	return 0;
}
