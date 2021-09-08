#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream myfile;
	myfile.open("jonatas.txt");
	string Temp;

	int numberofvertices = 15;
	int numberofedges = 20;

	int* generatednumbers;
	generatednumbers = new int[numberofvertices];
	for (int i = 0; i < numberofvertices; i++)
		generatednumbers[i] = -1;
	for (int i = 0; i < numberofedges; i++)
	{
		int k = rand() % numberofvertices;
		int j;
		do {
			j = rand() % numberofvertices;
		} while (j == k);
		generatednumbers[k] = j;
		Temp.append(to_string(k));
		Temp.append(" ");
		Temp.append(to_string(j));
		Temp.append("\n");
	}
	int additionaledges = 0;
	for (int i = 0; i < numberofvertices; i++)
	{
		if (generatednumbers[i] == -1)
		{
			int k = rand() % numberofvertices;
			generatednumbers[i] = k;
			Temp.append(to_string(i));
			Temp.append(" ");
			Temp.append(to_string(k));
			Temp.append("\n");
			additionaledges++;
		}
	}
	numberofedges += additionaledges;
	myfile << numberofvertices << " " << numberofedges << "\n";
	myfile << Temp;

	myfile.close();
	return 0;
}