#include "backprop.h"


//	initializes and allocates memory on heap

CBackProp::CBackProp(int NumLayers, int *sz, double b, double a, bool dropout_enabled)
{

	Init(NumLayers, sz, b, a, dropout_enabled);
}

void CBackProp::Init(int NumLayers, int *sz, double b, double a, bool dropout_enabled)
{
	dropoutmode = dropout_enabled;
	beta = b;
	alpha = a;
	//	set no of layers and their sizes
	numl = NumLayers;
	lsize = new int[numl];
	int i;

	input_buffer = new double[sz[0]];

	// NN Layergröße auf vielfaches von 16 erweitern
	for (i = 0; i<numl; i++)
	{
		if (i<numl - 1)
		{
			if (sz[i] % 16 != 0)
			{
				sz[i] += (16 - sz[i] % 16);

			}
		}
		lsize[i] = sz[i];
	}

	//	allocate memory for output of each neuron
	out = new double*[numl];

	for (i = 0; i<numl; i++)
	{
		out[i] = (double*)_aligned_malloc(sizeof(double)*lsize[i], 64);
	}

	//	allocate memory for delta
	delta = new double*[numl];

	for (i = 0; i<numl; i++)
	{
		delta[i] = (double*)_aligned_malloc(sizeof(double)*lsize[i], 64);
	}

	//	allocate memory for dropoutlist
	if (dropoutmode)
	{
		dropoutlist = new int*[numl];

		for (i = 1; i<numl - 1; i++)
		{
			dropoutlist[i] = new int[lsize[i]];
		}
	}

	//	allocate memory for weights
	weight = new double**[numl];

	for (i = 1; i<numl; i++) {
		weight[i] = new double*[lsize[i]];
	}
	for (i = 1; i<numl; i++) {
		for (int j = 0; j<lsize[i]; j++) {
			weight[i][j] = (double*)_aligned_malloc(sizeof(double)*lsize[i - 1] + 1, 64); //new double[lsize[i-1]+1];
		}
	}

	//	allocate memory for previous weights
	prevDwt = new double**[numl];

	for (i = 1; i<numl; i++) {
		prevDwt[i] = new double*[lsize[i]];

	}
	for (i = 1; i<numl; i++) {
		for (int j = 0; j<lsize[i]; j++) {
			prevDwt[i][j] = (double*)_aligned_malloc(sizeof(double)*lsize[i - 1] + 1, 64);
		}
	}

	//	seed and assign random weights
	//srand((unsigned)(time(NULL)));
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1.0);

	for (i = 1; i<numl; i++)
		for (int j = 0; j<lsize[i]; j++)
			for (int k = 0; k < lsize[i - 1] + 1; k++)
			{
				if (k<lsize[i - 1]) // weights init
				{
					float rand_nr = (double)distribution(generator);
					float factor = (double)sqrt(2.0 / ((double)lsize[i - 1] * 0.5)); // ReLU init
					weight[i][j][k] = rand_nr *factor;
				}
				else	// bias init
				{
					weight[i][j][k] = 0.0;
				}
			}

	//	initialize previous weights to 0 for first iteration
	for (i = 1; i<numl; i++)
		for (int j = 0; j<lsize[i]; j++)
			for (int k = 0; k<lsize[i - 1] + 1; k++)
				prevDwt[i][j][k] = (double)0.0;

	// Note that the following variables are unused,
	//
	// delta[0]
	// weight[0]
	// prevDwt[0]
	// dropoutlist[0]
	// dropoutlist[numl-1]

	//  I did this intentionaly to maintains consistancy in numbering the layers.
	//  Since for a net having n layers, input layer is refered to as 0th layer,
	//  first hidden layer as 1st layer and the nth layer as output layer. And 
	//  first (0th) layer just stores the inputs hence there is no delta or weigth
	//  values corresponding to it.
}



CBackProp::~CBackProp()
{
	Reset();
}

void CBackProp::Reset()
{
	int i;

	// free input buffer
	delete[] input_buffer;

	//	free out
	for (i = 0; i<numl; i++)
		_aligned_free(out[i]);
	delete[] out;

	//	free delta
	for (i = 0; i<numl; i++)
		_aligned_free(delta[i]);
	delete[] delta;

	//	free dropoutlist
	for (i = 1; i<numl - 1; i++)
		delete[] dropoutlist[i];
	delete[] dropoutlist;

	//	free weight
	for (i = 1; i<numl; i++)
		for (int j = 0; j<lsize[i]; j++)
			_aligned_free(weight[i][j]);
	for (i = 1; i<numl; i++)
		delete[] weight[i];
	delete[] weight;

	//	free prevDwt
	for (i = 1; i<numl; i++)
		for (int j = 0; j<lsize[i]; j++)
			_aligned_free(prevDwt[i][j]);
	for (i = 1; i<numl; i++)
		delete[] prevDwt[i];
	delete[] prevDwt;

	//	free layer info
	delete[] lsize;
}

//	sigmoid function
double CBackProp::Sigmoid(double in)
{
	return (double)(1 / (1 + exp(-in)));
}

inline void CBackProp::Softmax(double *in, int size)
{
	// determine max output sum
	double max = 0.0;
	for (int i = 0; i < size; i++)
		if (in[i] > max) max = in[i];

	// determine scaling factor -- sum of exp(each val - max)
	double scale = 0.0;
	for (int i = 0; i < size; ++i)
		scale += exp(in[i] - max);

	for (int i = 0; i < size; ++i)
		in[i] = exp(in[i] - max) / scale;

}

inline double CBackProp::SigmoidDerivative(double in)
{
	return (in * (1 - in));
}

// ReLU activation
inline double CBackProp::ReLU(double in)
{
	if (in < 0) return in*0.01f;
	return in;
}

inline double CBackProp::ReLUDerivative(double in)
{
	if (in < 0) return (double)0.01;
	else return (double)1.0;
}
//	mean square error
double CBackProp::mse(double *tgt) const
{
	double mse = 0;

	for (int i = 0; i<lsize[numl - 1]; i++)
	{
		double tmp = tgt[i] - out[numl - 1][i];
		mse += tmp*tmp;
	}
	return mse / 2;
}

#ifdef FTYPE_NODOUBLE
bool CBackProp::isCorrectGuess(double *tgt)
{
	double *tmptarget = importArray(tgt, lsize[numl - 1]);
	bool retval = isCorrectGuess(tmptarget);
	delete[] tmptarget;
	return retval;
}
#endif

bool CBackProp::isCorrectGuess(double *tgt)
{
	double largestoutput = 0.0;
	int samelargestoutputs = 0;
	int index_of_largestoutput = 0;
	int target = 0;

	for (int i = 0; i<lsize[numl - 1]; i++)
	{
		if (tgt[i] == 1.0) target = i;

		if (out[numl - 1][i] > largestoutput)
		{
			samelargestoutputs = 0;
			largestoutput = out[numl - 1][i];
			index_of_largestoutput = i;
		}
		else if (out[numl - 1][i] == largestoutput)
		{
			samelargestoutputs++;

		}
	}

	if (target == index_of_largestoutput && largestoutput > 0.01 && samelargestoutputs == 0)
		return true;
	return false;
}

//	returns i'th output of the net
double CBackProp::Out(int i) const
{
	return out[numl - 1][i];
}

void CBackProp::ffwd(double *in)
{
	ffwd(in, false);
}

void CBackProp::ffwd(double *in, bool dropout)
{
	SetInputs(in);
	ffwd(dropout);
}

// feed forward
void CBackProp::ffwd(bool dropout)
{
	int i, lsize_hlp;
	double sum,
		*out_hlp,
		*weight_hlp;

	if (dropoutmode) // dropout NN in dropout (for backpropagation) or in non-dropout
	{
		//	assign content to input layer
		for (i = 0; i<lsize[0]; i++)
			out[0][i] = input_buffer[i];

		//	assign output(activation) value 
		//	to each neuron using sigmoid func
		for (i = 1; i<numl; i++)
		{				// For each layer

			lsize_hlp = lsize[i - 1];

			for (int j = 0; j<lsize[i]; j++) // For each unit in current layer
			{
				if (dropout) // for dropouts, set output to 0
				{
					if (i < numl - 1)
					{
						if (dropoutlist[i][j] == 1)
						{
							out[i][j] = 0.0;
							continue;
						}
					}
				}

				sum = 0.0;
				weight_hlp = weight[i][j];
				out_hlp = out[i - 1];

				for (int k = 0; k<lsize_hlp; k++)
				{
					sum += *out_hlp * *weight_hlp;	// Apply weight to inputs and add to sum
					out_hlp++;
					weight_hlp++;
				}

				if (i>1 && !dropout)	// for each layer above a dropout layer, halve the incoming sum if no-dropout
				{
					sum = sum * (double)0.5;
				}
				sum += weight[i][j][lsize_hlp];		// Apply bias

													//if (i == numl-1)//softmax for outputlayer if no-dropout
													//	out[i][j]=sum;
													//else
				if (i == numl - 1)//Sigmoid+CrossEntropy for outputlayer http://neuralnetworksanddeeplearning.com/chap3.html#softmax
					out[i][j] = sum; //out[i][j] = Sigmoid(sum);
				else // hidden Layers
					out[i][j] = ActivationFunction(sum);
			}
		}
		Softmax(out[numl-1], lsize[numl - 1]); // Softmax for outputlayer
	}
	else // no dropout NN
	{
		//	assign content to input layer
		for (i = 0; i<lsize[0]; i++)
			out[0][i] = input_buffer[i];

		//	assign output(activation) value 
		//	to each neuron usng sigmoid func
		for (i = 1; i<numl; i++)
		{				// For each layer

			lsize_hlp = lsize[i - 1];

			for (int j = 0; j<lsize[i]; j++)
			{		// For each neuron in current layer
				sum = 0.0;
				weight_hlp = weight[i][j];

				for (int k = 0; k<lsize_hlp; k++)
				{		// For input from each neuron in preceeding layer
					sum += out[i - 1][k] * weight_hlp[k];	// Apply weight to inputs and add to sum
				}

				sum += weight_hlp[lsize_hlp];		// Apply bias
				if (i == numl - 1)//Sigmoid+CrossEntropy for outputlayer http://neuralnetworksanddeeplearning.com/chap3.html#softmax
					out[i][j] = sum; //out[i][j] = Sigmoid(sum);
				else
					out[i][j] = ActivationFunction(sum);
			}
		}
		Softmax(out[numl - 1], lsize[numl - 1]); // Softmax for outputlayer
	}
}


bool CBackProp::bpgt(double * in, double * tgt)
{
	SetInputs(in);
	double *tmptarget = new double[lsize[numl - 1]];
	for (int i = 0; i < lsize[numl - 1]; i++)
	{
		tmptarget[i] = (double)tgt[i];
	}
	bool retval = bpgt(tmptarget);
	delete[] tmptarget;
	return retval;
}
//	backpropagate errors from output
//	layer uptill the first hidden layer
bool CBackProp::bpgt(double *tgt)
{
	double sum,
		*weight_hlp,
		*prevDwt_hlp,
		*out_hlp,
		delta_hlp,
		tmp, tmp2;
	int lsize_hlp, i;

	if (dropoutmode) // dropout NN
	{
		MakeDropoutList();
		ffwd(true);//	update output values for each neuron
		bool retval = isCorrectGuess(tgt);

		for (i = 0; i<lsize[numl - 1]; i++)//	find delta for output layer
		{
			//delta[numl-1][i]=out[numl-1][i] * (1-out[numl-1][i]) * (tgt[i]-out[numl-1][i]) * beta; // Mean Squared Error
			delta[numl - 1][i] = (tgt[i] - out[numl - 1][i]); // Mean Cross Entropy Error
		}

		for (i = numl - 2; i>0; i--)//	find delta for hidden layers	
		{
			for (int j = 0; j<lsize[i]; j++)
			{
				if (dropoutlist[i][j] == 1) continue;
				sum = 0.0;
				for (int k = 0; k<lsize[i + 1]; k++)
				{
					if (i<numl - 2) if (dropoutlist[i + 1][k] == 1) continue;
					sum += delta[i + 1][k] * weight[i + 1][k][j];
				}
				delta[i][j] = ActivationDerivativeFunction(out[i][j])* sum;

			}
		}

		//__m256 valpha = _mm256_set1_ps(alpha);//	apply momentum ( does nothing if alpha=0 )

		for (i = 1; i<numl; i++)		// for each layer
		{						//	adjust weights usng steepest descent
			lsize_hlp = lsize[i - 1];

			for (int j = 0; j<lsize[i]; j++) // for each neuron
			{
				if (i<numl - 1) if (dropoutlist[i][j] == 1) continue;
				out_hlp = out[i - 1];
				weight_hlp = weight[i][j];
				prevDwt_hlp = prevDwt[i][j];
				delta_hlp = delta[i][j] * beta;

				/*__m256 vdelta = _mm256_set1_ps(delta[i][j]);
				for (int k = 0; k < lsize_hlp; k += 8)
				{
				// dropout...

				__m256 vout = _mm256_load_ps(out_hlp);
				__m256 vprevdwt = _mm256_load_ps(prevDwt_hlp);
				__m256 vweight = _mm256_load_ps(weight_hlp);

				__m256 vtmp = _mm256_mul_ps(vout, vdelta);
				__m256 vtmp2 = _mm256_fmadd_ps(valpha, vprevdwt, vtmp);

				vweight = _mm256_add_ps(vweight, vtmp2);
				_mm256_store_ps(prevDwt_hlp, vtmp);

				// Loop pointer increments
				out_hlp += 8;
				prevDwt_hlp += 8;
				weight_hlp += 8;
				}*/

				for (int k = 0; k < lsize_hlp; k++) // for each weight
				{
					if (i <= 1 || i>1 && (dropoutlist[i - 1][k] == 0))
					{ // no dropout on this weight
						tmp = delta_hlp * (*out_hlp);
						tmp2 = alpha * (*prevDwt_hlp) + tmp;
					
						*weight_hlp += tmp2;
						*prevDwt_hlp = tmp;

					}

					// Loop pointer increments
					out_hlp++;
					prevDwt_hlp++;
					weight_hlp++;

				}
				// bias
				weight[i][j][lsize_hlp] += (delta_hlp + alpha*prevDwt[i][j][lsize_hlp]);
				prevDwt[i][j][lsize_hlp] = delta_hlp;
			}
		}
		return retval;
	}
	else // no dropout NN
	{
		ffwd(false);//	update output values for each neuron
		bool retval = isCorrectGuess(tgt);

		for (i = 0; i<lsize[numl - 1]; i++)//	find delta for output layer
		{
			delta[numl - 1][i] = (tgt[i] - out[numl - 1][i]); // Mean Cross Entropy Error for Sigmoid on last layer
		}

		for (i = numl - 2; i>0; i--)//	find delta for hidden layers	
		{
			for (int j = 0; j<lsize[i]; j++)
			{
				sum = 0.0;
				for (int k = 0; k<lsize[i + 1]; k++)
					sum += delta[i + 1][k] * weight[i + 1][k][j];
				delta[i][j] = ActivationDerivativeFunction(out[i][j])*sum;
			}
		}

		for (i = 1; i<numl; i++)		//	apply momentum ( does nothing if alpha=0 )
		{						//	adjust weights usng steepest descent
			lsize_hlp = lsize[i - 1];
			out_hlp = out[i - 1];

			for (int j = 0; j<lsize[i]; j++)
			{
				weight_hlp = weight[i][j];
				prevDwt_hlp = prevDwt[i][j];
				delta_hlp = delta[i][j] * beta;

				for (int k = 0; k < lsize_hlp; k++)
				{
					tmp = delta_hlp * out_hlp[k];
					tmp2 = alpha*prevDwt_hlp[k] + tmp;

					weight_hlp[k] += tmp2;
					prevDwt_hlp[k] = tmp;
				}
				weight_hlp[lsize_hlp] += (delta_hlp + alpha*prevDwt_hlp[lsize_hlp]);
				prevDwt_hlp[lsize_hlp] = delta_hlp;
			}
		}
		return retval;
	}
}


void CBackProp::SaveNet(char *filename)
{
	FILE *fNet;
	fopen_s(&fNet, filename, "wb");
	if (fNet != NULL)
	{
		double beta1 = (double)beta,
			alpha1 = (double)alpha;
		fwrite(&beta1, sizeof(beta1), 1, fNet);
		fwrite(&alpha1, sizeof(alpha1), 1, fNet);
		fwrite(&numl, sizeof(numl), 1, fNet);
		fwrite(&dropoutmode, sizeof(dropoutmode), 1, fNet);
		fwrite(lsize, sizeof(lsize[0]), numl, fNet);

		for (int i = 1; i<numl; i++)
		{
			for (int j = 0; j<lsize[i]; j++)
			{
				for (int k = 0; k < lsize[i - 1] + 1; k++)
				{
					double weighttmp = weight[i][j][k];
					fwrite(&weighttmp, sizeof(weighttmp), 1, fNet);
				}
			}
		}

		fclose(fNet);
	}
}

bool CBackProp::LoadNet(char *filename)
{
	FILE *fNet = NULL;
	fopen_s(&fNet, filename, "rb");
	if (fNet != NULL)
	{
		Reset();
		double beta_tmp, alpha_tmp;
		int numl_tmp;
		int dropout_tmp;
		bool dropout_tmp2 = false;
		fread(&beta_tmp, sizeof(beta_tmp), 1, fNet);
		fread(&alpha_tmp, sizeof(alpha_tmp), 1, fNet);
		fread(&numl_tmp, sizeof(numl_tmp), 1, fNet);
		fread(&dropout_tmp, sizeof(dropout_tmp), 1, fNet);
		if (dropout_tmp) dropout_tmp2 = true;
		int *lsize_temp = new int[numl_tmp];

		fread_s(lsize_temp, sizeof(lsize_temp[0])* numl_tmp, sizeof(lsize_temp[0]), numl_tmp, fNet);

		Init(numl_tmp, lsize_temp, (double)beta_tmp, (double)alpha_tmp, dropout_tmp2);

		for (int i = 1; i<numl_tmp; i++)
		{
			for (int j = 0; j<lsize_temp[i]; j++)
			{
				for (int k = 0; k < lsize_temp[i - 1] + 1; k++)
				{
					double weighttmp;
					fread(&weighttmp, sizeof(weighttmp), 1, fNet);
					weight[i][j][k] = (double)weighttmp;
				}
			}
		}
		delete[] lsize_temp;
		fclose(fNet);
		return true;
	}
	else
	{
		printf("couldnt open the file!");
		return false;
	}
}

void CBackProp::Log(char *file, int i, int time, double err_train, double err_test)
{
	FILE *fp;
	errno_t err = fopen_s(&fp, file, "a");
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y.%m.%d %H-%M-%S");
	auto str = oss.str();
	if (!err) fprintf(fp, "%s\t%i\t%f\t%f\t%i\t%.2f\t%.2f\n", str.c_str(), time, alpha, beta, i, err_train, err_test);
	fclose(fp);
}

void CBackProp::PrintSymbol(double *in, int tgt)
{
	for (int i = 0; i<lsize[0]; i++)
	{
		if (in[i] > 0.5)printf("#");
		else printf(" ");
		if (i % 28 == 0) printf("\n");
	}
	printf("\ntarget=%i\n", tgt);
	for (int i = 0; i < lsize[numl - 1]; i++)
	{
		printf("%.2f  ", out[numl - 1][i]);
	}
	printf("\n");
}

void CBackProp::MakeDropoutList()
{
	for (int i = 1; i < numl - 1; i++)
	{
		for (int j = 0; j < lsize[i]; j++)
		{
			dropoutlist[i][j] = 0;
		}
		int numdropouts = 0;

		do
		{
			int rnd = rand() % lsize[i];

			if (!dropoutlist[i][rnd])
			{
				dropoutlist[i][rnd] = 1;
				numdropouts++;
			}
		} while (numdropouts < lsize[i] / 2);
	}
}


void CBackProp::PrintConfig()
{
	printf("A=%.3f B=%.3f L=%i DO=", alpha, beta, numl);
	if (dropoutmode) printf("Y"); else printf("N");
	for (int i = 0; i < numl; i++)
	{
		printf("[L%i=%i]", i, lsize[i]);
	}
	printf("\n");
}

void CBackProp::SetHyperParameters(double Alpha, double Beta, int BatchSize)
{
	alpha = (double)Alpha;
	beta = (double)Beta;
}

void CBackProp::SetInputs(double *in)
{
	for (int i = 0; i < lsize[0]; i++)
	{
		input_buffer[i] = (double)in[i];
	}
}

double *CBackProp::importArray(double *in, int size)
{
	double *retval = new double[size];
	for (int i = 0; i < size; i++)
	{
		retval[i] = (double)in[i];
	}
	return retval;
}