#pragma once
#include "Globals.h"
using namespace std;

class NeuralNetwork
{
public:
	NeuralNetwork();

	//-----------------------------------------------------------------------------
	// init()
	// ---------
	//
	// General : Initializes random weight between 0-1 for weights vector
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void init();

	//-----------------------------------------------------------------------------
	// getWight()
	// ---------
	//
	// General : Gets the weights of this neuralNetwork
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : vecotr<double> weightMap
	//
	//-----------------------------------------------------------------------------
	vector<double> getWeight();

	//-----------------------------------------------------------------------------
	// setWight()
	// ---------
	//
	// General : Sets the weight of this NeuralNetwork
	//
	// 
	// Parameters :
	// vector<double> weightMap(in)
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void setWeight(vector<double> weightMap);

	//-----------------------------------------------------------------------------
	// calculate()
	// ---------
	//
	// General : This function starts by reseting all hidden and output Layer values
	// then it re-calculates the hidden and output Layer values by the weightMap and 
	// the data passed as a argument
	//
	// 
	// Parameters :
	// double data[](in) - array with the size of inputLayer that contains the inputLayer data
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	int calculate(double data[]);

	//-----------------------------------------------------------------------------
	// calculate()
	// ---------
	//
	// General : This function mutates the weights of this neuralNetowrk by a give percent
	// the percent
	//
	// 
	// Parameters :
	// vector<double> weightMap(in) - what weights to mutate
	// int percent(in) - the mutation percent (for example: if equal to 20, mutation percent will be 0.2 == 20%)
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void mutate(vector<double> weightMap, int percent);

	//-----------------------------------------------------------------------------
	// relu()
	// ---------
	//
	// General : Calculates a value passed in a relu activation function
	//
	// 
	// Parameters :
	// double z(in)- what value to pass in relu function
	//
	// Return Value : double - the value of passed z in relu function
	//
	//-----------------------------------------------------------------------------
	double relu(double z);

private:
	vector<double> inputLayer;
	vector<vector<double>> hiddenLayers;
	vector<double> outputLayer;
	vector<double> weightMap;

	int weightMapSize;
};

