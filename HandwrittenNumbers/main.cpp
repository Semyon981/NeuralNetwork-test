#include <iostream>
#include "NeuralNetwork.hpp"
using namespace std;

void normalize(vec& a)
{
	for (int i = 0; i < a.size; i++)
	{
		if (a[i] > 1)
		{
			a[i] = 1;
		}
	}
}

int main()
{
	srand(time(NULL));

	vec* in = new vec[16];
	for (int i = 0; i < 16; i++)
	{
		in[i].setSize(9);
		in[i].clear();
	}
	in[0][0] = 1;
	in[0][1] = 1;
	in[0][2] = 1;

	in[1][3] = 1;
	in[1][4] = 1;
	in[1][5] = 1;

	in[2][6] = 1;
	in[2][7] = 1;
	in[2][8] = 1;


	in[3][0] = 1;
	in[3][3] = 1;
	in[3][6] = 1;

	in[4][1] = 1;
	in[4][4] = 1;
	in[4][7] = 1;

	in[5][2] = 1;
	in[5][5] = 1;
	in[5][8] = 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 3; j < 6; j++)
		{
			in[(i * 3) + j + 3] = in[i] + in[j];
			normalize(in[(i * 3) + j + 3]);
		}
	}

	vec* outright = new vec[16];
	for (int i = 0; i < 16; i++)
	{
		outright[i].setSize(2);
		outright[i][0] = 0.2;
		outright[i][1] = 0.2;
	}
	outright[0][0] = 0.8;
	outright[1][0] = 0.8;
	outright[2][0] = 0.8;

	outright[3][1] = 0.8;
	outright[4][1] = 0.8;
	outright[5][1] = 0.8;

	for (int i = 6; i < 15; i++)
	{
		outright[i][0] = 0.8;
		outright[i][1] = 0.8;
	}




	for (int i = 0; i < 16; i++)
	{
		cout << i << " " << outright[i][0] << " " << outright[i][1] << endl << endl;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << in[i][j * 3 + k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}




	Network nn;
	nn.setArch(3, 9, 4, 2);
	nn.setRandWeights(-1, 1, 3);
	//nn.loadFromFile("Network1.nn");

	for (int i = 0; i < 100000; i++)
	{
		int bb = rand()%16;
		nn.setInputLayer(in[bb]);

		nn.work();
		nn.setError(outright[bb]);
		nn.updateWeights(0.3);
		

		
	}

	nn.saveToFile("Network1.nn");


	while (true)
	{
		int bb;
		cout << "num: ";
		cin >> bb;
		nn.setInputLayer(in[bb]);
		nn.work();
		vec out = nn.getOutputLayer();
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << in[bb][j * 3 + k] << " ";
			}
			cout << endl;
		}
		cout << "-------------------------" << endl;
		cout << out[0] << "\t" << out[1] << endl << endl;
	}

	

	
	









	return 0;
}