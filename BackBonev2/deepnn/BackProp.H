
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

#include "GlobalDefines.h"

using namespace std;

class CBackProp{

// Input Buffer
	FPTYPE *input_buffer;

//	output of each neuron
	FPTYPE **out;

//	delta error value for each neuron
	FPTYPE **delta;

//  dropout list
	int **dropoutlist;

// Is in dropout mode? 1=yes
	int dropoutmode;

//	vector of weights for each neuron
	FPTYPE ***weight;

//	no of layers in net
//	including input layer
	int numl;

//	vector of numl elements for size 
//	of each layer
	int *lsize;

//	storage for weight-change made
//	in previous epoch
	FPTYPE ***prevDwt;

//	squashing functions
#define ActivationFunction ReLU
#define ActivationDerivativeFunction ReLUDerivative
	inline FPTYPE Sigmoid(FPTYPE in);
	inline void Softmax(FPTYPE * in, int size);
	inline FPTYPE SigmoidDerivative(FPTYPE in);
	inline FPTYPE ReLU(FPTYPE in);
	inline FPTYPE ReLUDerivative(FPTYPE in);

//	learning rate
	FPTYPE beta;

//	momentum parameter
	FPTYPE alpha;



//	initializes and allocates memory
public:
	CBackProp(int NumLayers,int *sz, FPTYPE b, FPTYPE a, bool dropout_enabled);
	bool isCorrectGuess(FPTYPE *tgt);
	~CBackProp();

//	backpropogates error for one set of input
	bool bpgt(FPTYPE *tgt);
	bool bpgt(FPTYPE *in, FPTYPE *tgt);

//	feed forwards activations for one set of inputs
	void ffwd(FPTYPE *in, bool dropout);
	void ffwd(bool dropout);
	void ffwd(FPTYPE *in);

//	returns mean square error of the net
	FPTYPE mse(FPTYPE *tgt) const;
	bool isCorrectGuess(double *tgt);
//	returns i'th output of the net
	FPTYPE Out(int i) const;
	void MakeDropoutList();
	void SaveNet(char *filename);
	bool LoadNet(char *filename);
	void Reset();
	void Init(int NumLayers,int *sz, FPTYPE b, FPTYPE a, bool dropout_enabled);
	void Log(char *file, int i, int time, double err_train, double err_test);
	void PrintSymbol(FPTYPE *in, int tgt);
	void PrintConfig();
	void SetHyperParameters(double Alpha, double Beta, int BatchSize);
private:
	void SetInputs(FPTYPE *in);
	FPTYPE *importArray(double *in, int size);
};

#endif