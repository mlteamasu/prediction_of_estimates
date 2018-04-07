#include"dataset.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include <cstring>
#include "H5Cpp.h"
#include <cstdlib>
using namespace H5;
using namespace std;

void read(ifstream &file, char **idname, char **idsubj)
{
	int count=0,i=0,j=0,n=200;
	char mass[200];
	char str[200];
	int gate = 0;
	while (idsubj[i][0] != 0)
		i++;
	while (idname[j][0] != 0)
		j++;
	while(!file.eof())
	{
		file.getline(mass, 200, ',');
		count++;
		if(!((mass[0]=='"')&&(mass[1]=='"')))
		{	
			if(!(((mass[1]=='С')&&(mass[2]=='Н'))||((mass[1]=='О')&&(mass[2]=='О'))||((mass[1]=='Ц')&&(mass[2]=='Н'))))
			strcpy(str,mass);

			if((mass[1]=='Ф')&&(mass[2]=='И')&&(mass[3]=='О'))
			{
				 do{

					file.getline(mass, 200, ',');
					count++;

					if(!(((mass[0]=='"')&&(mass[1]=='"'))||((mass[1]=='Д')&&(mass[2]=='о')&&(mass[3]=='л')&&(mass[4]=='г')&&(mass[5]=='о')&&(mass[6]=='в'))))
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
				 }while(!((mass[1]=='Д')&&(mass[2]=='о')&&(mass[3]=='л')&&(mass[4]=='г')&&(mass[5]=='о')&&(mass[6]=='в')));
			}

			if(((mass[1]=='С')&&(mass[2]=='Н'))||((mass[1]=='О')&&(mass[2]=='О'))||((mass[1]=='Ц')&&(mass[2]=='Н')))
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

void readint(ifstream &file, int **data, char **idname, char **idsubj)
{
	char buff[200];
	int gate = 0, gate1 = 0, gate2 = 0, gate3 = 0;;
	int i = 0, j = 1;
	int i1=0, j1 = 0;
	data[i][j] = -1;
	while (!file.eof())
	{
		file.getline(buff, 200, ',');
		if (!((buff[0] == '"') && (buff[1] == '"')))
		{
			if (gate2)
			{
				gate2--;
				continue;
			}
			if (!(strcmp(buff, "\"ФИО\"")))
			{
				gate = 1;
				continue;
			}
			if (!(strcmp(buff, "\"Долгов\"")))
			{
				gate = 0;
				i++;
				j = 0;
				continue;
			}
			if (!(strcmp(buff, "\"Зачет\"")))
			{
				gate1 = 1;
				continue;
			}
			if(gate)
			{
				while (idsubj[i1][0] != 0)
				{
					if(!(strcmp(buff, idsubj[i1])))
						break;
					i1++;
				}
				data[i][j]=i1;
				i1 = 0;
				j++;
			}
			if (gate1)
			{

				j1 = 0;
				while (idname[j1][0] != 0)
				{
					if (!(strcmp(buff, idname[j1])))
						break;
					j1++;
				}
				if (idname[j1][0] == 0)
					continue;
				data[i][j] = j1;
				j++;
				gate2 = 2;
				gate1 = 0;
				gate3 = 1;
				continue;
			}
			if(gate3)
			{
				/*
				Отл- 5
				Хор- 4
				Удв- 3
				Неуд- 2
				Н/я- -1
				Зач- 1
				Н/з- 0
				*/
				if (!(strcmp(buff, "\"Неуд\"")))
				{
					data[i][j] = 2;
					j++;
					continue;
				}
				if (!(strcmp(buff, "\"Отл\"")))
				{
					data[i][j] = 4;
					j++;
					continue;
				}
				if (!(strcmp(buff, "\"Хор\"")))
				{
					data[i][j] = 3;
					j++;
					continue;
				}
				if (!(strcmp(buff, "\"Н/я\"")))
				{
					data[i][j] = 0;
					j++;
					continue;
				}
				if (!(strcmp(buff, "\"Удв\"")))
				{
					data[i][j] = 2;
					j++;
					continue;
				}
				if (!(strcmp(buff, "\"Зач\"")))
				{
					data[i][j] = 4;
					j++;
					continue;
				}
				if (!(strcmp(buff, "\"Н/з\"")))
				{
					data[i][j] = 1;
					j++;
					continue;
				}
				/*if ((!(strcmp(buff, "\"Неусп\"")))|| (!(strcmp(buff, "\"Успев\""))))
				{*/
					gate3 = 0;
					gate1 = 1;
					i++;
					j = 0;
					continue;
				/*}*/
			}
		}
	}

}
void convert(int ***data, char **idname, char **idsubj, int **dataset)
{
	int n=0, m =0, l=0; 
	/*while (idsubj[n][0] != 0)
		n++;
	while (idname[m][0] != 0)
		m++;*/
	while (data[l][0][1] != -2)
		l++;
	for(int i=0; i<l; i++){
		n = 2;
		m = 2;
		while (data[i][0][n] != -2)
			n++;
		while (data[i][m][0] != -2)
			m++;
		for(int j=1; j<m; j++){
			for(int k=1; k<n; k++){
				//printf("[%d][%d] = %d\n", data[i][0][k], data[i][j][0], data[i][j][k]);
				dataset[data[i][0][k]][data[i][j][0]]=data[i][j][k];
			}
		}
	}
	n = 0;
	m = 0;
	while (idsubj[n][0] != 0)
		n++;
	while (idname[m][0] != 0)
		m++;
	/*for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			printf("%d\t", dataset[j][i]);
		}
		printf("\n");
	}*/
}

void write(int **dataset,int n,int m)
{
	printf("\n mass %d x %d\n", m, n);
	float *data = (float*)malloc(sizeof(float)*m*n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			data[j*m + i] = (dataset[j][i])/4.0;
			printf("%f\t", data[j*m + i]);
		}
		printf("\n");
	}
	const H5std_string DATASET_NAME1("data");
	const H5std_string FILE_NAME1("DATASET.h5");
	H5File file1(FILE_NAME1, H5F_ACC_TRUNC);
	hsize_t dimsf1[2] = {n,m };
	DataSpace dataspace1(2, dimsf1);
	DataSet dataset1 = file1.createDataSet(DATASET_NAME1, PredType::NATIVE_FLOAT, dataspace1);
	dataset1.write(data, PredType::NATIVE_FLOAT);
	file1.close();
}