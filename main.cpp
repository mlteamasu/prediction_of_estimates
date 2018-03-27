#include"dataset.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<windows.h>
using namespace std;

// -------------------- example -----------------

int main()
{
	setlocale(LC_ALL, "Russian");
	int **data=0, n=200;
	char **idname=0;
	char **idsubj=0;
	string namef();
	ifstream file; // создаем объект класса ifstream
	WIN32_FIND_DATA FindFileData_csv;
	HANDLE csv;
	csv = FindFirstFile(L"*.csv", &FindFileData_csv);
	idsubj = (char**)malloc(n*sizeof(char*));
	idname = (char**)malloc(n*sizeof(char*));
	for (int i = 0; i<n; i++) {
		idsubj[i] = (char*)malloc(n*sizeof(char));
		idsubj[i][0] = 0;
		idname[i] = (char*)malloc(n*sizeof(char));
		idname[i][0] = 0;
	}
	do
	{
		file.open(FindFileData_csv.cFileName);
		read(&file, data, idname, idsubj);
		file.close();
	} while (FindNextFile(csv, &FindFileData_csv) != 0);
	system("pause");
}