
//////////////////////////////////////////////
//	Fully connected multilayered feed		//
//	forward	artificial neural network using	//
//	Backpropogation	algorithm for training.	//
//////////////////////////////////////////////


#ifndef backprop_h
#define backprop_h

#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <immintrin.h>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <random>

using namespace std;

class CBackProp{

// Input Buffer
	double *input_buffer;

//	output of each neuron
	double **out;

//	delta error value for each neuron
	double **delta;

//  dropout list
	int **dropoutlist;

// Is in dropout mode? 1=yes
	int dropoutmode;

//	vector of weights for each neuron
	double ***weight;

//	no of layers in net
//	including input layer
	int numl;

//	vector of numl elements for size 
//	of each layer
	int *lsize;

//	storage for weight-change made
//	in previous epoch
	double ***prevDwt;

//	squashing functions
#define ActivationFunction ReLU
#define ActivationDerivativeFunction ReLUDerivative
	inline double Sigmoid(double in);
	inline void Softmax(double * in, int size);
	inline double SigmoidDerivative(double in);
	inline double ReLU(double in);
	inline double ReLUDerivative(double in);

//	learning rate
	double beta;

//	momentum parameter
	double alpha;



//	initializes and allocates memory
public:
	CBackProp(int NumLayers,int *sz, double b, double a, bool dropout_enabled);
	~CBackProp();

//	backpropogates error for one set of input
	bool bpgt(double *tgt);
	bool bpgt(double *in, double *tgt);

//	feed forwards activations for one set of inputs
	void ffwd(double *in, bool dropout);
	void ffwd(bool dropout);
	void ffwd(double *in);

//	returns mean square error of the net
	double mse(double *tgt) const;
	bool isCorrectGuess(double *tgt);
//	returns i'th output of the net
	double Out(int i) const;
	void MakeDropoutList();
	void SaveNet(char *filename);
	bool LoadNet(char *filename);
	void Reset();
	void Init(int NumLayers,int *sz, double b, double a, bool dropout_enabled);
	void Log(char *file, int i, int time, double err_train, double err_test);
	void PrintSymbol(double *in, int tgt);
	void PrintConfig();
	void SetHyperParameters(double Alpha, double Beta, int BatchSize);
private:
	void SetInputs(double *in);
	double *importArray(double *in, int size);
};

#endif