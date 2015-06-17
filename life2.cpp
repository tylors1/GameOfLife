#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <stdio.h>
using namespace std;

//g++ -std=c++11

void print(int** array1, int mWidth, int mHeight){
	for(int i = 1; i < (mWidth - 1); i++){
		cout << endl;
		for(int j = 1; j < (mHeight -1); j++){
			cout << array1[i][j] << " ";
		}
	}
	cout << endl;

}

void printWhole(int** array1, int mWidth, int mHeight){
	for(int i = 0; i < (mWidth); i++){
		cout << endl;
		for(int j = 0; j < (mHeight); j++){
			cout << array1[i][j] << " ";
		}
	}
	cout << endl;

}

void populate(int** array1, int mWidth, int mHeight){
	for(int i = 0; i < (mWidth); i++){
		//cout << endl;
		for(int j = 0; j < (mHeight); j++){
			if(j == 0 || i == 0 || j == (mHeight-1) || i == (mWidth-1)){   //poulate borders with zero
				array1[i][j] = 0;
			}
			else{
				int randNum = rand()%(100-1 + 1) + 1;
				if(randNum <= 37){
					array1[i][j] = 0;
				}
				else{
					array1[i][j] = 1;
				}
			}
			//cout << v[i][j] << " ";
		}
	}
}
//populate temp array
void copy(int** array1, int** array2, int mWidth, int mHeight){
	for(int i = 1; i < (mWidth); i++){
		for(int j = 1; j < (mHeight); j++){
			array2[i][j] = array1[i][j];
		}
	}
}

//populate temp doughnut array (wrap around)
void copyD(int** array1, int** array2, int mWidth, int mHeight){
	
	//set top outside row equal to bottom inside row
	for(int i = 0; i < (mWidth-1); i++){
		array2[0][i] = array1[mHeight-1][i];
	}
	//set bottom outside row equal to top inside row
	for(int i = 0; i < (mWidth-1); i++){
		array2[mHeight-1][i] = array1[1][i];
	}
	//set left outside column equal to right inside column
	for(int i = 0; i < (mHeight-1); i++){
		array2[i][0] = array1[i][mWidth-1];
	}
	//set right outside column equal to left inside column
	for(int i = 0; i < (mHeight-1); i++){
		array2[i][mWidth-1] = array1[i][1];
	}
	//top left = bottom right
	array2[0][0] = array1[mWidth-1][mHeight-1];
	//bottom left = top right
	array2[mWidth-1][0] = array1[1][mWidth-1];
	//bottom right = top left
	array2[mWidth-1][mHeight-1] = array1[1][1];
	//top right = bottom left
	array2[0][mWidth-1] = array1[mHeight-1][1];

	//rest of inside of board
	for(int i = 1; i < (mWidth-1); i++){
		for(int j = 1; j < (mHeight-1); j++){
			array2[i][j] = array1[i][j];
		}
	}
}


void calcClassicGeneration(int** array1, int mWidth, int mHeight){

	int** temp = new int*[mWidth];
	for(int i = 0; i < mWidth; ++i){
    	temp[i] = new int[mHeight];
	}
	cout << "...copying..." << endl;
	//copy main array to temp
	copy(array1, temp, mHeight, mWidth);
	cout << "...generating..." << endl;
	for(int i = 1; i < (mWidth-1); i++){
		for(int j = 1; j < (mHeight-1); j++){
			//classic mode
				int count = 0;
				//iterate through 8 spaces around cell, count populated cells
				count = array1[i][j+1] + array1[i+1][j+1] + array1[i+1][j] + array1[i+1][j-1] + array1[i][j-1] + 
				array1[i-1][j-1] + array1[i-1][j] + array1[i-1][j+1];
				//kill cell 
				//cout << "count at " << v[i][j] << " is: " << count << endl;
				if(count < 2 || count > 3)
					temp[i][j] = 0;
				//cell kept alive
				if(count == 2)
					temp[i][j] = array1[i][j];
				//cell is born, or kept alive
				if(count == 3)
					temp[i][j] = 1;
		}
	}
	//sets completed generation back to main array
	copy(temp, array1, mHeight, mWidth);
}
void calcDoughnutGeneration(int** array1, int mWidth, int mHeight){

	int** temp = new int*[mWidth];
	for(int i = 0; i < mWidth; ++i){
    	temp[i] = new int[mHeight];
	}
	cout << "...copying..." << endl;
	//copy main array to temp
	cout << "...print before generating..." << endl;;
	printWhole(array1, mWidth, mHeight);
	copyD(array1, temp, mHeight, mWidth);
	cout << "...generating..." << endl;
	for(int i = 1; i < (mWidth-1); i++){
		for(int j = 1; j < (mHeight-1); j++){
			//classic mode
				int count = 0;
				//iterate through 8 spaces around cell, count populated cells
				count = array1[i][j+1] + array1[i+1][j+1] + array1[i+1][j] + array1[i+1][j-1] + array1[i][j-1] + 
				array1[i-1][j-1] + array1[i-1][j] + array1[i-1][j+1];
				//kill cell 
				//cout << "count at " << v[i][j] << " is: " << count << endl;
				if(count < 2 || count > 3)
					temp[i][j] = 0;
				//cell kept alive
				if(count == 2)
					temp[i][j] = array1[i][j];
				//cell is born, or kept alive
				if(count == 3)
					temp[i][j] = 1;
		}
	}
	//sets completed generation back to main array
	//copyD(temp, array1, mHeight, mWidth);
	array1 = temp;
	
}


int main ()
{

	int height = (6+2);
	int width = (6+2);

	int** array1 = new int*[width];
	for(int i = 0; i < width; ++i){
    	array1[i] = new int[height];
	}

	//random populate for array
	populate(array1, width, height);

	//print vector
	cout << "...printing...";
	print(array1, width, height);

	//classic
	//cout << "...classic..." << endl;
	//calcClassicGeneration(array1, width, height);
	cout << "...Doughnut..." << endl;
	calcDoughnutGeneration(array1, width, height);
	print(array1, width, height);

	cout << "...print whole...";
	printWhole(array1, width, height);

	return 0;
}

/*void calcDoughnutGeneration(int array1[5][5]){
	int temp[5][5];
	copy(array1, temp);
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			//classic mode
			int count = 0;
			int pointX = 0;
			int pointY = 0;
			//up and right
			if()
		}
	}
	//sets completed generation back to main array
	copy(temp, array1);
}

