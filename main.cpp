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
	printf("sdfsdf");
	setlocale(LC_ALL, "Russian");
	int ***data=0, n=500;
	int count_f = 0;
	int i = 0,j=0;
	char **idname=0;
	char **idsubj=0;
	string namef();
	int **dataset=0;
	ifstream file; // ������� ������ ������ ifstream
	WIN32_FIND_DATA FindFileData_csv;
	HANDLE csv;
	csv = FindFirstFile(L"*.csv", &FindFileData_csv);
	idsubj = (char**)malloc(n*sizeof(char*));
	idname = (char**)malloc(n*sizeof(char*));
	for (int i = 0; i<n; i++) 
	{
		idsubj[i] = (char*)malloc(n*sizeof(char));
		idsubj[i][0] = 0;
		idname[i] = (char*)malloc(n*sizeof(char));
		idname[i][0] = 0;
	}
	data = (int***)malloc(100*sizeof(int**));
	for (int i = 0; i < 100; i++)
	{
		data[i] = (int**)malloc(500 * sizeof(int*));
		for (int j = 0; j < 500; j++)
		{
			data[i][j] = (int*)malloc(500 * sizeof(int));
			for (int k = 0; k < 500; k++)
				data[i][j][k] = -2;
		}
	}
	dataset = (int**)malloc(1000 * sizeof(int*));
	for (int k = 0; k < 1000; k++)
	{	
		dataset[k] = (int*)malloc(1000 * sizeof(int));
		for(int i=0; i<1000; i++)
			dataset[k][i]=-5;
	}
	do
	{
		_putws(FindFileData_csv.cFileName);
		file.open(FindFileData_csv.cFileName);
		read(file,  idname, idsubj);
		/*file.close();
		file.open(FindFileData_csv.cFileName);*/
		file.seekg(0, ios_base::beg);
		readint(file, data[count_f], idname, idsubj);
		file.close();
		count_f++;
	} while (FindNextFile(csv, &FindFileData_csv) != 0);


	printf("\n\n__________Subject :\n");
	j = 0;
	while (idsubj[j][0] != 0)
	{
		printf("id:%d", j);
		puts(idsubj[j]);
		j++;
	}
	i = 0;
	printf("\n\n__________Students :\n");
	while (idname[i][0] != 0)
	{
		printf("id:%d", i);
		puts(idname[i]);
		i++;
	}
	printf("\n\n\nst\\sub  ");
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if((data[0][i][j]!=-2))
				printf("%d \t", data[0][i][j]);
		}
		printf("\n");
	}
	convert(data, idname, idsubj, dataset);
	write(dataset, j, i);
	system("pause");
}