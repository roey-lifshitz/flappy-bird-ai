#include "NeuralNetwork.h"
#include <math.h>


NeuralNetwork::NeuralNetwork()
{
	this->inputLayer = vector<double>(INPUT_LAYER_SIZE);
	//Initiallize a 2d vector
	this->hiddenLayers = vector<vector<double>>(HIDDEN_LAYER_NUM, vector<double>(HIDDEN_LAYER_SIZE));
	this->outputLayer = vector<double>(OUTPUT_LAYER_SIZE);

	// initiallize weightMap
	int fromInputToHidden = this->inputLayer.size() * this->hiddenLayers[0].size();
	int fromHiddenToHidden = pow(this->hiddenLayers[0].size(), 2);
	int fromHiddenToOutput = this->hiddenLayers[0].size() * this->outputLayer.size();
	int size = fromInputToHidden + fromHiddenToHidden * (HIDDEN_LAYER_NUM - 1) + fromHiddenToOutput;
	this->weightMapSize = size;
	this->weightMap = vector<double>(size);
}

void NeuralNetwork::init()
{
	// assign random values to weight map
	for (int i = 0; i < this->weightMapSize; i++)
	{
		// gen random num between 1- 0
		this->weightMap[i] = ((double)rand() / (RAND_MAX));
	}
}

vector<double> NeuralNetwork::getWeight() 
{ 
	return this->weightMap; 
}

void NeuralNetwork::setWeight(vector<double> weightMap)
{
	this->weightMap = weightMap;
}

int NeuralNetwork::calculate(double data[])
{
	// Reset all Neuron values
	int numberOfHiddenLayers = this->hiddenLayers.size();
	int outputLayerSize = this->outputLayer.size();
	int inputLayerSize = this->inputLayer.size();

	// Since in this project, all hidden layers have the same size
	int hiddenLayerSize = this->hiddenLayers[0].size();

	for (int i = 0; i < numberOfHiddenLayers;i++)
	{
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			this->hiddenLayers[i][j] = 0;
		}
	}
	for (int i = 0; i < outputLayerSize; i++) 
		this->outputLayer[i] = 0;


	// insert new data into input Layer
	for (int i = 0; i < inputLayerSize; i++)
	{
		this->inputLayer[i] = data[i];
	}

	// calculate the neuralNetwork with new data
	int counter = 0;

	// start calculation from inputLayer to first hiddenLayers
	for (int i = 0; i < hiddenLayerSize; i++)
	{
		for (int j = 0; j < inputLayerSize; j++)
		{
			this->hiddenLayers[0][i] += this->inputLayer[j] * this->weightMap[counter++];
		}
		this->hiddenLayers[0][i] = this->relu(this->hiddenLayers[0][i]);
	}

	// calculate from hiddenLayer to hiddenLayer
	for (int layer = 1; layer < numberOfHiddenLayers; layer++)
	{
		for (int i = 0; i < hiddenLayerSize; i++)
		{
			for (int j = 0; j < hiddenLayerSize; j++)
			{
				this->hiddenLayers[layer][i] +=
					this->hiddenLayers[layer - 1][j] * this->weightMap[counter++];
			}
			this->hiddenLayers[layer][i] = this->relu(this->hiddenLayers[layer][i]);
		}
	}

	// calculate from last hiddenLayer to outputLayer
	for (int i = 0; i < outputLayerSize; i++)
	{
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			this->outputLayer[i] += this->hiddenLayers[numberOfHiddenLayers - 1][i] * this->weightMap[counter++];
		}
		this->outputLayer[i] = this->relu(this->outputLayer[i]);
	}

	// if output[1] > output[0] then jump
	return this->outputLayer[1] > this->outputLayer[0];
}

void NeuralNetwork::mutate(vector<double> weightMap, int percent)
{
	// default mutation percent
	if (percent == 0) percent = MUTATION_PERCENT;
	percent = 2 * percent;
	this->weightMap = weightMap;
	int size = this->weightMap.size();
	for (int i = 0; i < size; i++)
	{
		// if mutation percent is 20, then it will mutate between 80% to 120%
		float ran = rand() % percent + (100 - percent / 2);
		this->weightMap[i] = this->weightMap[i] * (ran / 100);
	}
}

double NeuralNetwork::relu(double z)
{
	return max(0.0, z);
}


