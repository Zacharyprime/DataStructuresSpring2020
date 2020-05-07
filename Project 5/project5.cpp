using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>


/*
Things to do:
	//read the name of the file ./a.out < filename.txt
	//get each token and store themin theunordered_map (or map)
	//increment its frequencies. You MAY be able to do myTokens[aToken]++.
	//close the file (filename.txt)
	//sort the myTokens in the decreasing order of VALUE which is frequencies
	//print the KEYS in myTokens (which has been sorted)separatedby a space.
	//after you printed the KEYS Do this  cout<<endl;  cout << “********”<< endl;
	//Now open the filename.text file again for reading
	//Read token by token as you have done this before
	//each time you get a token, find its position in the myTokens (sorted data structure and print the position followed by spacecout) << endl;



*/

int arrayFind(string KEY,string* A,int size){
	for(int i = 0; i<size; i++){
		if(*(A+i) == KEY){
			return i;
		}
	}
	return -1;
}

	//Returns the iterator for where the current max of the map is.
	unordered_map<string,int>::iterator getMax(unordered_map<string,int>& map){
	unordered_map<string,int>::iterator itr = map.begin();
	unordered_map<string,int>::iterator currentMax = map.end(); //Placed at end to avoid caller from getting errors in edge cases.

	while(itr != map.end()){
		//If the current node has a higher frequency than our current max, adjust.
		if(currentMax->second < itr->second){
			cout << "New Max: " << itr->second << endl;
			currentMax = ++itr;
		}
	}
	cout << "Got Map" << endl; //DEBUG STATEMENT PLEASE REMOVE-------------------------------------------------------------------------
	return currentMax;
}

//Compresses text files into a frequency based compression.
void compress(string file){
	cout << "Compressing" << endl; //DEBUG STATEMENT PLEASE REMOVE-------------------------------------------------------------------------
	//Store the key we are inserting.
	string currentKey;

	//Setup map and map iterator
	unordered_map<string,int> myMap = {};
	unordered_map<string,int>::iterator itr = myMap.begin();

	//Setup I/O structure
	ifstream myFile;
	ofstream myOutFile;
	myFile.open(file);


	
	//INSERT THE NEXT TOKEN TO THE MAP
	while(!myFile.eof()){

		//Grab the next "token"
		myFile >> currentKey;

		//Try and find the token in our map
		itr = myMap.find(currentKey);

		//If it's already in our map, increment the count
		if(itr != myMap.end()){
			(itr->second)++;
		}
		//If we haven't seen that token before, add it to the map
		else{
			myMap.insert(pair<string,int>(currentKey,1));
		}
	}

	myFile.close();
	//MAP INSERTION COMPLETE

	
	//SORT THE DATA BY FREQUENCY

	//Create an array to hold our (to be sorted) values.
	int size = myMap.size(); //Store the size as it changes as we sort
	string tokens[size];

	cout << "Sorting Data" << endl; //DEBUG STATEMENT PLEASE REMOVE-------------------------------------------------------------------------

	//Sort Map while putting the strings into an array
	for(int i = 0; i<size; i++){
		itr = getMax(myMap); //Find the most frequent token

		cout << "The max is: " << itr->first << endl;

		tokens[i] = itr->first; //Put it in it's place in the array
		myMap.erase(itr); //Erase the token from the map so we don't re-add it to the array.
	}

	//DATA SORT COMPLETE

	cout << "Data Sorted" << endl; //DEBUG STATEMENT PLEASE REMOVE-------------------------------------------------------------------------

	//PRINT KEYS
	for(int i = 0; i<size; i++){
		cout << tokens[i] << endl;
	}

	//End the file as described in project description
	cout << endl;
	cout << "********" << endl;
	//KEY PRINT COMPLETE


	//COMPRESS FILE

	//Put all the tokens into a map so that we can put the text file back together compressed.
	map<int,int> textMap; //Order in the text file, Array Index
	map<int,int>::iterator itr2; //New iterator for the new map

	myFile.open(file); 
	int i, arrayIndex = -1;
	while(!myFile.eof()){
		myFile >> currentKey; //Get the key

		arrayIndex = arrayFind(currentKey, tokens, size); //Find the token in our array

		textMap.insert(pair<int,int>(i++,arrayIndex)); //Store it's position in the text file and increment i
	}

	myFile.close();

	cout << "Opening FIle" << endl; //DEBUG STATEMENT PLEASE REMOVE-------------------------------------------------------------------------
	//Take our map and put it back into the text file compressed.
	myOutFile.open(file);
		for(int i = 0; i<textMap.size(); i++){

			itr2 = textMap.find(i);
			myOutFile << itr2->second << " ";
		}
		myOutFile << endl;
	myOutFile.close();
	//COMPRESSION COMPLETE

}


int main(){
	
	unordered_map<string, int> myMap;
	compress(_argv[1]);
	return 0;
}