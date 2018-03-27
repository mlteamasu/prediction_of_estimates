#include"dataset.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;

void read(ifstream *file, int **data, char **idname, char **idsubj)
{
	int count=0,i=0,j=0,n=200;
	char mass[200];
	char str[200];
	idsubj=(char**) malloc(n*sizeof(char*));
	idname=(char**) malloc(n*sizeof(char*));
	for (int i=0; i<n; i++){
		idsubj[i]=(char*) malloc (n*sizeof(char));
		idname[i]=(char*) malloc (n*sizeof(char));
	}

	while(!file->eof())
	{
		file->getline(mass, 200, ',');
		count++;
		if(!((mass[0]=='"')&&(mass[1]=='"')))
		{	
			if(!(((mass[1]=='Ñ')&&(mass[2]=='Í'))||((mass[1]=='Î')&&(mass[2]=='Î'))||((mass[1]=='Ö')&&(mass[2]=='Í'))))
			strcpy(str,mass);

			if((mass[1]=='Ô')&&(mass[2]=='È')&&(mass[3]=='Î'))
			{
				 do{

					file->getline(mass, 200, ',');
					count++;

					if(!(((mass[0]=='"')&&(mass[1]=='"'))||((mass[1]=='Ä')&&(mass[2]=='î')&&(mass[3]=='ë')&&(mass[4]=='ã')&&(mass[5]=='î')&&(mass[6]=='â'))))
					{
						strcpy(idsubj[i],mass);
						i++;
						puts(mass);
					}
				 }
				while(!((mass[1]=='Ä')&&(mass[2]=='î')&&(mass[3]=='ë')&&(mass[4]=='ã')&&(mass[5]=='î')&&(mass[6]=='â')));
			}

			if(((mass[1]=='Ñ')&&(mass[2]=='Í'))||((mass[1]=='Î')&&(mass[2]=='Î'))||((mass[1]=='Ö')&&(mass[2]=='Í')))
			{
				strcpy(idname[j],str);
						j++;
				puts(str);
			}

			/*puts(mass);
			if(!(count%50))
				system("pause");*/
		}

	}
	i=0;
	j=0;
	printf("\n  %d   \n",count);
}
