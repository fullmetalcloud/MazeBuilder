// MazeGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int size = 1000;
	Maze m(size, size);
	Graph<int> maze = m.GenerateMaze();
	cout << "DONE" << endl;
	ofstream wfile;
	wfile.open("output.txt", ofstream::trunc);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			wfile << maze(i, j) << " ";
		}
		wfile << endl;
	}
	cin.ignore();
	return 0;
}

