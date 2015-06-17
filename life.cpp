#include <iostream>
#include "Life.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h> 
#include <stdio.h>
#include <sstream>
#include <cmath>
#include <ctime>
using namespace std;

Life::Life(){
	current_population[0][0];
	future_population[0][0];
	check_stabilization[0][0];
	fileOrRand = 0;
	modeType = 0;
	userFile = "";
	userFileOut = "";
	runTimeOptions = 0;
	numOfRow=0;
	numOfCol=0;
	density = 0;
	height = 0;
	width = 0;
	numOfGen = 0;
	boarderWidth=0;
	boarderHeight=0;
	dead=false;

}
Life::~Life(){
	cout<<"object destroyed"<<endl;
}
void Life::collectInfo(){
	cout<<"collectInfo"<<endl;
	ifstream readme(userFile.c_str());
	string line;

	while(getline(readme, line)){
		width = line.length();
		height++;

	}
	int** baseConstruction = new int*[width];
	for(int i = 0; i < width; ++i){
    	baseConstruction[i] = new int[height];
	}
	current_population = baseConstruction;
}
void Life::readInFile(){
	cout<<"readInFile"<<endl;
	ifstream readme(userFile.c_str());
	string line;
	int countRow= 0; //this count = the row in the array
	while(getline(readme, line)){
		for(int i = 0; i < line.length();++i){
			if(line[i]=='-'){
				current_population[countRow][i]=0;
			}
			else{
				current_population[countRow][i]=1;
			}
		}
		countRow++;
	}

}
void Life::populate(){
	srand(std::time(0)); 
	boarderWidth=width+2;
	boarderHeight=height+2;
	int** temp = new int*[boarderWidth];
	for(int i = 0; i < boarderHeight; ++i){
    	temp[i] = new int[boarderWidth];
	}
	for(int i = 0; i < (boarderHeight); ++i){
		//cout << endl;
		for(int j = 0; j < (boarderWidth); ++j){
			if(j == 0 || i == 0 || j == (boarderWidth-1) || i == (boarderHeight-1)){   //poulate borders with zero
				temp[i][j] = 0;
			}
			else{
				int randNum = rand()%(100-1 + 1) + 1;
				if(randNum <= (density*100)){
					temp[i][j] = 0;
				}
				else{
					temp[i][j] = 1;
				}
			}
			//cout << v[i][j] << " ";
		}
	}
	current_population=temp;
	check_stabilization=temp;
}


//determine the user's choice for file or random
void Life::fileVsRand(){
	cout<<"fileVsRand"<<endl;
	string user_input="";
	cout<<"would you like to enter a file (y/n)?"<<endl;
	cin>>user_input;
	if (user_input=="y"){
		cout<<"enter the filepath (include .txt)"<<endl;
		cin>>userFile;
		if(checkIfExists(userFile)!=true){
			cout<<"invalid file"<<endl;
			Life::fileVsRand();
		}
		else{
			fileOrRand = 1;
			Life::collectInfo();
			Life::readInFile();
			Life::buildBoarder();
		}
	}
	else if(user_input=="n"){
		fileOrRand = 0;
		Life::dimensionPrompt();
		Life::getDensity();
		//Life::buildBoarder();
		
		Life::populate();
		Life::printArray(current_population,height+2,width+2);
	}

	else
	{
		cout<<"invalid input"<<endl;
		Life::fileVsRand();
	}
	//cout<<"fileOrRand: "<<fileOrRand<<endl;
}

//check if the file exists
bool Life::checkIfExists(string file_path){
	cout<<"checkIfExists"<<endl;
	bool real_file=0;
	ifstream mystream(file_path.c_str());
	string line;
	try{
		while(getline(mystream, line)){
			cout<<"valid file"<<endl;
			real_file=1;
		}
	}
	catch(int e){
		cout<<"no file"<<endl;
	}
	mystream.close();
	return real_file;

}

void Life::selectMode(){
	cout<<"selectMode"<<endl;

	string user_input;
	cout<<endl<<"select mode: "<<endl<<"a) classical"<<endl<<"b) donut"<<endl<<"c) mirror"<<endl;
	cin>>user_input;
	if(user_input=="a"){
		modeType = 0;
	}
	else if(user_input=="b"){
		modeType = 1;
	}
	else if (user_input == "c"){
		modeType = 2;
	}
	else{
		cout<<"invalid entry (enter 'a' or 'b' or 'c')"<<endl;//how do i remove from stack so that it doesn't print the number of time user messed up
		Life::selectMode();
	}
	cout<<"modeType: "<<modeType<<endl;
	
}
void Life::runTime()
{
	cout<<"runTime"<<endl;
	string user_input;
	cout<<"select method of data output"<<endl<<"a) have the program pause for a certain amount of time between generations"<<endl;
	cout<<"b) press 'enter' to continue"<<endl<<"c) write out to a file"<<endl;
	cin>>user_input;
	if (user_input=="a")
	{
		runTimeOptions = 1;
	}
	else if (user_input == "b")
	{
		runTimeOptions = 2;
	}
	else if (user_input == "c")
	{
		runTimeOptions = 3;
		Life::getUserOutFile();
		Life::outputProgress();
	}
	else
	{
		cout<<"invalid entry (enter 'a' or 'b' or 'c')"<<endl;
		Life::runTime();
	}
	cout<<"user run time option"<<runTimeOptions<<endl;
}

void Life::calculateFuture()
{
	int n=0;
	while(n!=1){


		if(modeType == 0){
			Life::classic(getCurrent_Population(),createTempBoarder(),getWidth()+2,getHeight()+2);
		}
		else if (modeType == 1){
			Life::donut(getCurrent_Population(),createTempBoarder(),getWidth()+2,getHeight()+2);
		}
		else{
			Life::mirror(getCurrent_Population(),createTempBoarder(),getWidth()+2,getHeight()+2);
		}
		
		Life::calcGeneration(getCurrent_Population(),createTempBoarder(),getWidth()+2,getHeight()+2);
		Life::howToProceed();
		Life::checkIfDead();
		if(stableCheck()==true){
			n = 1;
		}
	}
	cout<<"closing"<<endl;

}

void Life::dimensionPrompt(){
	
	cout<<"dimensionPrompt"<<endl;
	string x="";
	cout<<"please enter the number of columns"<<endl;
	cin>>x;
	width=Life::toInteger(x);
	x="";
	cout<<"please enter the number of rows"<<endl;
	cin>>x;
	height=Life::toInteger(x);
	cout<<width<<endl;
	cout<<height<<endl;

	

	
}
int Life::toInteger(string x){
	int myint=0;
	int temp = 0;
	bool decimal=false;
	for(int i = 0; i <x.length();++i){
			temp = x[i]-'0';
			cout<<"temp"<<temp<<endl;
			myint+=temp*(pow(10,i));
		
	}

	return myint;
}
double Life::toDouble(string x){
	double mydouble=0;
	int temp;
	for(int i= 0; i < x.length();++i){
		if(i==0){
			continue;
		}
		else{
			temp = x[i]-'0';
			mydouble+=temp*(pow(10,i-1));
		}
		temp = 0;
	}
	mydouble=mydouble/pow(10,x.length()-1);
	cout<<"mydouble"<<mydouble<<endl;
	return mydouble;
}
void Life::getDensity()
{
	string x;
	cout<<"getDensity"<<endl;
	cout<<"enter a decimal value x such that, 0<x<=1"<<endl;
	cin>>x;
	if((Life::toDouble(x)<=0)||(Life::toDouble(x)>1)){
		cout<<"you must satisy these conditions"<<endl;
		Life::getDensity();
	}
	else{
		density=Life::toDouble(x);
	}
	cout<<density<<endl;
}


void Life::printArray(int** array, int h, int w){
	cout<<"printArray"<<endl;
	string line;
	
	for(int i = 0; i < h; ++i){
		for(int j = 0; j <w; ++j){

			if(array[i][j]==1){
				line.append("X");
			}
			else if(array[i][j]==0){
				line.append("-");
			}
			else{
				line.append("error");
			}
		}
		cout<<line<<endl;
		line="";
	}
	
}
void Life::printInside(int** array1, int mWidth, int mHeight){
	cout<<"printInside"<<endl;
	string line;
	for(int i = 1; i < (mHeight - 1); i++){
		

		for(int j = 1; j < (mWidth -1); j++){
			if(array1[i][j]==1){
				line.append("X");
			}
			else{
				line.append("-");
			}
		}
		cout <<line<< endl;
		line="";
	}
	

}
void Life::buildBoarder(){
	cout<<"buildBoarder"<<endl;
	boarderHeight = height+2;
	boarderWidth = width+2;
	
	int** temp = new int*[boarderWidth];
	for(int i = 0; i < boarderHeight; ++i){
    	temp[i] = new int[boarderWidth];
	}
	for(int i = 0; i < height;++i){
		for(int j =  0; j < width;++j)

			temp[i+1][j+1]=current_population[i][j];
	}
	for(int i = 0; i <boarderHeight; ++i){
		for(int j = 0;j<boarderWidth;++j){
			if((temp[i][j]!=0)&&(temp[i][j]!=1)){
				temp[i][j]=0;
			}
		}
	}
	current_population=temp;
	


}
void Life::checkIfDead(){
	int count = 0;
	for (int i = 0; i < height+2; ++i)
	{
		for (int j = 0; j < width+2; ++j)
		{
			if(current_population[i][j]==1){
				count+=1;
			}
		}
	}
	if(count==0){
		dead = true;
	}
}
void Life::buildCheckStable(int** array){
	

	int** temp = new int*[boarderWidth];
	for(int i = 0; i < boarderHeight; ++i){
    	temp[i] = new int[boarderWidth];
	}
	for(int i = 1; i < boarderHeight-1;++i){
		for(int j =  1; j < boarderWidth-1;++j)

			temp[i][j]=array[i][j];
	}
	for(int i = 0; i <boarderHeight; ++i){
		for(int j = 0;j<boarderWidth;++j){
			if((temp[i][j]!=0)&&(temp[i][j]!=1)){
				temp[i][j]=0;
			}
		}
	}
	check_stabilization=temp;

}
int** Life::createTempBoarder(){
	cout<<"createTempBoarder"<<endl;
	boarderHeight = height+2;
	boarderWidth = width+2;

	int** temp = new int*[boarderWidth];
	for(int i = 0; i < boarderHeight; ++i){
    	temp[i] = new int[boarderWidth];
	}
	for(int i = 0; i < boarderHeight;++i){
		for(int j = 0 ; j<boarderWidth;++j){
			temp[i][j]=0;
		}
	}
	return temp;
}
void Life::classic(int** array1, int** array2, int mWidth, int mHeight){
	cout<<"classic"<<endl;
	check_stabilization=array1;
	for(int i = 1; i < (mHeight-1); i++){
		for(int j = 1; j < (mWidth-1); j++){
			array2[i][j] = array1[i][j];
		}
	}
	current_population=array2;
}
void Life::donut(int** array1, int** array2, int mWidth, int mHeight){
	cout<<"donut"<<endl;
	check_stabilization = array1;
	//set top outside row equal to bottom inside row
	for(int i = 1; i < (mWidth-1); i++){
		array2[0][i] = array1[mHeight-2][i];
	}
	
	//set bottom outside row equal to top inside row
	for(int i = 1; i < (mWidth-1); i++){
		array2[mHeight-1][i] = array1[1][i];
	}
	//set left outside column equal to right inside column
	for(int i = 1; i < (mHeight-1); i++){
		array2[i][0] = array1[i][mWidth-2];
	}
	//set right outside column equal to left inside column
	for(int i = 1; i < (mHeight-1); i++){
		array2[i][mWidth-1] = array1[i][1];
	}
	
	//top left = bottom right
	array2[0][0] = array1[mHeight-2][mWidth-2];
	//bottom left = top right
	
	array2[mHeight-1][0] = array1[1][mWidth-2];
	//bottom right = top left
	array2[mHeight-1][mWidth-1] = array1[1][1];
	//top right = bottom left
	array2[0][mWidth-1] = array1[mHeight-2][1];
	
	//rest of inside of board
	for(int i = 1; i < (mHeight-1); i++){
		for(int j = 1; j < (mWidth-1); j++){
			array2[i][j] = array1[i][j];
		}
	}
	current_population=array2;
}
void Life::mirror(int** array1, int** array2, int mWidth, int mHeight){
	cout<<"mirror"<<endl;
	check_stabilization = array1;
	//set top outside row equal to top inside row
	for(int i = 1; i < (mWidth-1); ++i){
		array2[0][i] = array1[1][i];
	}
	//set bottom outside row equal to bottom inside row
	for(int i = 1; i < (mWidth-1); ++i){
		array2[mHeight-1][i] = array1[mHeight-2][i];
	}
	//set left outside column equal to left inside column
	for(int i = 1; i < (mHeight-1); ++i){
		array2[i][0] = array1[i][1];
	}
	//set right outside column equal to right inside column
	for(int i = 1; i < (mHeight-1); i++){
		array2[i][mWidth-1] = array1[i][mWidth-2];
	}
	cout<<"made it this far mirror"<<endl;
	//top left = top left inside
	array2[0][0] = array1[1][1];
	//bottom left = bottom left inside
	array2[mHeight-1][0] = array1[mHeight-2][1];
	//bottom right = bottom right inside
	array2[mHeight-1][mWidth-1] = array1[mHeight-2][mWidth-2];
	//top right = top right inside
	array2[0][mWidth-1] = array1[1][mWidth-2];

	//rest of inside of board
	for(int i = 1; i < (mHeight-1); i++){
		for(int j = 1; j < (mWidth-1); j++){
			array2[i][j] = array1[i][j];
		}
	}
	current_population=array2;
}
//right after this function see if check_stabilization == current_population to see if it is stable
void Life::calcGeneration(int** array1, int** temp, int mWidth, int mHeight){

	cout << "...generating..." << endl;
	for(int i = 1; i < (mHeight-1); i++){
		for(int j = 1; j < (mWidth-1); j++){
			//classic mode
				int count = 0;
				//iterate through 8 spaces around cell, count populated cells
				count = array1[i][j+1] + array1[i+1][j+1] + array1[i+1][j] + array1[i+1][j-1] + array1[i][j-1] + array1[i-1][j-1] + array1[i-1][j] + array1[i-1][j+1];
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
	current_population=temp;
	
	
}

void Life::outputProgress(){
	cout<<"outputProgress"<<endl;

	ofstream writeOut(userFileOut.c_str(), std::ios::app);//check if you need .c_str()
	string line;
	writeOut<<"generation: "<<numOfGen<<endl;
	for(int i = 1; i < boarderHeight; ++i){
		for(int j = 1; j< boarderWidth; ++j)
		{
			if(current_population[i][j]==1){
				line.append("X");
			}
			else{
				line.append("-");
			}
		}	
		writeOut<<line<<endl;
		line="";

	}
	writeOut<<endl;
	writeOut.close();
	numOfGen++;
	
}
void Life::howToProceed(){
	cout<<"howToProceed"<<endl;
	if (runTimeOptions==1){
		Life::pauseProgress();
	}
	else if(runTimeOptions==2){
		Life::enterProgress();
	}
	else{
		cout<<"writing to file"<<endl;
		Life::outputProgress();
	}
}
void Life::pauseProgress(){
	Life::printArray(getCurrent_Population(),getHeight()+2,getWidth()+2);
	double n = 0;
	while(n!=100000000){
		n++;
	}
	numOfGen++;
	
}

bool Life::stableCheck(){
	cout<<"stableCheck"<<endl;
	Life::buildCheckStable(check_stabilization);
	//printArray(getCurrent_Population(),getHeight()+2,getWidth()+2);
	//printArray(check_stabilization,getHeight()+2,getWidth()+2);
	int countIfNotEqual=0;
	for(int i = 0; i<boarderHeight; ++i){
		for(int j = 0; j <boarderWidth; ++j){
			if(check_stabilization[i][j]!=current_population[i][j]){
				countIfNotEqual++;
			}
		}
	}
	if(dead==true){
		cout<<"population is dead"<<endl;
		return true;
	}
	if(countIfNotEqual==0){
		cout<<"population is stable after "<<numOfGen<<" generations"<<endl;
		return true;
	}
	else{
		return false;
	}
}
void Life::enterProgress(){
	Life::printArray(getCurrent_Population(),getHeight()+2,getWidth()+2);
	cout<<"enterProgress"<<endl;
	cout<<"press enter to continue"<<endl;

	if(cin.get() != '\n'){
		Life::enterProgress();
	}
	else
	{
		cout<<"proceeding to next generation"<<endl;

	}
	numOfGen++;

}
void Life::getUserOutFile(){
	cout<<"getUserOutFile"<<endl;
	string user_input;
	cout<<"enter the name of the file you wish to write out the data to (use .txt)"<<endl;
	cin>>user_input;
	std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
	if((user_input[user_input.length()-4]=='.')&&(user_input[user_input.length()-3]=='t')&&(user_input[user_input.length()-2]=='x')&&(user_input[user_input.length()-1]=='t')){
		cout<<"file is valid"<<endl;
		userFileOut = user_input;
	}
	else{
		cout<<"invalid file, make sure it ends in .txt"<<endl;
		Life::getUserOutFile();
	}	
}

int** Life::getCurrent_Population(){
	return current_population;
}
int** Life::getFuture_Population(){
	return future_population;
}
int Life::getHeight(){
	return height;
}
int Life::getWidth(){
	return width;
}


