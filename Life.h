#include <iostream>
#include <fstream>

using namespace std;
#ifndef GAMEOFLIFE
#define GAMEOFLIFE

class Life{
private:
	string userFile;
	string userFileOut;
	int** current_population;
	int** check_stabilization;
	//int** temp_population;
	int** future_population;
	bool fileOrRand;//0 = no file, 1 = user will use file
	int modeType; //0 = classic, 1 = donut, 2 = mirror
	int runTimeOptions; //1 = pause method, 2 = enter method, 3 = outputfile
	int numOfRow;
	int numOfCol;
	double density;
	int height;
	int width;
	int numOfGen;
	int boarderHeight;
	int boarderWidth;
	bool dead;
public:
	Life();
	~Life();

	//the 5 summary steps
	void fileVsRand();
	void selectMode();
	void runTime();//pause, enter or outputfile
	void calculateFuture();//check for mode type
	
	void printArray(int**,int,int);//called depending on outcome of runTime
	bool stableCheck();//see if population is stable or not

	//other functions
	void dimensionPrompt();
	void getDensity();//if random selected
	void createRandomLife();//uses getDensity
	void pauseProgress();//if user wants there to be a pause
	void enterProgress();//if user wants to use enter
	void outputProgress();//if user wants info written to output file, not sure if function needed
	
	void checkIfDead();
	void populate();//generates array based on user input
	bool checkIfExists(string);//checks if file exists
	void getUserOutFile();
	void readInFile();//read in file and set equal to current_population
	void collectInfo();
	void buildBoarder();
	void mirror(int**,int**,int,int);//mirror mode build the boarder
	void classic(int**,int**,int,int);
	void donut(int**,int**,int,int);
	int** createTempBoarder();
	void calcGeneration(int**,int**,int,int);
	void printInside(int**,int,int);
	void howToProceed();//determines how to move onto next generation
	void buildCheckStable(int**);//build array to compare to current generation


	int** getCurrent_Population();
	int** getFuture_Population();
	int getHeight();
	int getWidth();

	int toInteger(string);//convert string to integer
	double toDouble(string);

};

#endif

// cd desktop\update2Proj2
// g++ *.cpp -o runme.exe
