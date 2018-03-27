#include"dataset.h"
#include<iostream>
#include<fstream>
#include<stdio.h>

using namespace std;

void read(ifstream *file, int **data, char **idname, char **idsubj)
{
	char str[200];
	int count=0;
	char mass[200];
	while(!file->eof())
	{
		file->getline(mass, 200, ',');
		count++;
		if(!((mass[0]=='"')&&(mass[1]=='"')))
		{
			puts(mass);
			/*if(!(count%50))
				system("pause");*/
		}

	}
	printf("\n  %d   \n",count);
}
