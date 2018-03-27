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
	int gate = 0;
	while (idsubj[i][0] != 0)
		i++;
	while (idname[j][0] != 0)
		j++;
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
						int i1 = 0;
						while (idsubj[i1][0] != 0)
						{
							if (strcmp(idsubj[i1], mass) == 0)
							{
								gate = 1;
								break;
							}
							i1++;
						}
						if (!gate)
						{
							strcpy(idsubj[i], mass);
							//printf("id:%d", i);
							i++;
							//puts(mass);
						}
						gate = 0;
					}
				 }while(!((mass[1]=='Ä')&&(mass[2]=='î')&&(mass[3]=='ë')&&(mass[4]=='ã')&&(mass[5]=='î')&&(mass[6]=='â')));
			}

			if(((mass[1]=='Ñ')&&(mass[2]=='Í'))||((mass[1]=='Î')&&(mass[2]=='Î'))||((mass[1]=='Ö')&&(mass[2]=='Í')))
			{

				int i1 = 0;
				while (idname[i1][0] != 0)
				{
					if (strcmp(idname[i1], str) == 0)
					{
						gate = 1;
						break;
					}
					i1++;
				}
				if (!gate)
				{
					strcpy(idname[j],str);
					//printf("id:%d", j);
					j++;
					//puts(str);
				}
				gate = 0;
			}

			/*puts(mass);
			if(!(count%50))
				system("pause");*/
		}

	}
	i=0;
	j=0;
	//printf("\n  %d   \n",count);
}
