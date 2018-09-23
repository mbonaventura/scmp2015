#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <common/utils.h>


#include <qss/qss_model.h>

double __L;
double __a;
double __d;
double __dx;
double __r;

void MOD_definition(int i, double *x, double *d, double t, double *dx)
{
	int j = 0;
	j = i;
	if(j >=1 && j <= 998)
	{
		dx[1] = __d*(x[(j+1) * 4]-2.0*x[(j) * 4]+x[(j-1) * 4])/(pow(__dx,2.0))+__r*(pow(x[(j) * 4],2.0))*(1.0-x[(j) * 4])-__a*(x[(j) * 4]-x[(j-1) * 4])/__dx;
		dx[2] = ((pow(__dx,-2.0))*__d*(x[(j-1) * 4 + 1]-2.0*x[(j) * 4 + 1]+x[(j+1) * 4 + 1])-2.0*x[(j) * 4]*x[(j) * 4 + 1]*(-1.0+x[(j) * 4])*__r+(1.0/(__dx))*__a*(x[(j-1) * 4 + 1]-x[(j) * 4 + 1])-(pow(x[(j) * 4],2.0))*x[(j) * 4 + 1]*__r)/2;
		dx[3] = (-2.0*x[(j) * 4 + 2]*2*(-1.0+x[(j) * 4])*x[(j) * 4]*__r-__d*(pow(__dx,-2.0))*(2.0*x[(j) * 4 + 2]*2-x[(j+1) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)-__a*(x[(j) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)*(1.0/(__dx))-4.0*x[(j) * 4]*(pow(x[(j) * 4 + 1],2.0))*__r-x[(j) * 4 + 2]*2*(pow(x[(j) * 4],2.0))*__r-2.0*(-1.0+x[(j) * 4])*(pow(x[(j) * 4 + 1],2.0))*__r)/6;
	}
}

void MOD_dependencies(int i, double *x, double *d, double t, double *der)
{
	int j = 0;
	j = i+1;
	if(j >=1 && j <= 998)
	{
		der[(j) * 4 + 1] = __d*(x[(j+1) * 4]-2.0*x[(j) * 4]+x[(j-1) * 4])/(pow(__dx,2.0))+__r*(pow(x[(j) * 4],2.0))*(1.0-x[(j) * 4])-__a*(x[(j) * 4]-x[(j-1) * 4])/__dx;
		der[(j) * 4 + 2] = ((pow(__dx,-2.0))*__d*(x[(j-1) * 4 + 1]-2.0*x[(j) * 4 + 1]+x[(j+1) * 4 + 1])-2.0*x[(j) * 4]*x[(j) * 4 + 1]*(-1.0+x[(j) * 4])*__r+(1.0/(__dx))*__a*(x[(j-1) * 4 + 1]-x[(j) * 4 + 1])-(pow(x[(j) * 4],2.0))*x[(j) * 4 + 1]*__r)/2;
		der[(j) * 4 + 3] = (-2.0*x[(j) * 4 + 2]*2*(-1.0+x[(j) * 4])*x[(j) * 4]*__r-__d*(pow(__dx,-2.0))*(2.0*x[(j) * 4 + 2]*2-x[(j+1) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)-__a*(x[(j) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)*(1.0/(__dx))-4.0*x[(j) * 4]*(pow(x[(j) * 4 + 1],2.0))*__r-x[(j) * 4 + 2]*2*(pow(x[(j) * 4],2.0))*__r-2.0*(-1.0+x[(j) * 4])*(pow(x[(j) * 4 + 1],2.0))*__r)/6;
	}
	j = i;
	if(j >=1 && j <= 998)
	{
		der[(j) * 4 + 1] = __d*(x[(j+1) * 4]-2.0*x[(j) * 4]+x[(j-1) * 4])/(pow(__dx,2.0))+__r*(pow(x[(j) * 4],2.0))*(1.0-x[(j) * 4])-__a*(x[(j) * 4]-x[(j-1) * 4])/__dx;
		der[(j) * 4 + 2] = ((pow(__dx,-2.0))*__d*(x[(j-1) * 4 + 1]-2.0*x[(j) * 4 + 1]+x[(j+1) * 4 + 1])-2.0*x[(j) * 4]*x[(j) * 4 + 1]*(-1.0+x[(j) * 4])*__r+(1.0/(__dx))*__a*(x[(j-1) * 4 + 1]-x[(j) * 4 + 1])-(pow(x[(j) * 4],2.0))*x[(j) * 4 + 1]*__r)/2;
		der[(j) * 4 + 3] = (-2.0*x[(j) * 4 + 2]*2*(-1.0+x[(j) * 4])*x[(j) * 4]*__r-__d*(pow(__dx,-2.0))*(2.0*x[(j) * 4 + 2]*2-x[(j+1) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)-__a*(x[(j) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)*(1.0/(__dx))-4.0*x[(j) * 4]*(pow(x[(j) * 4 + 1],2.0))*__r-x[(j) * 4 + 2]*2*(pow(x[(j) * 4],2.0))*__r-2.0*(-1.0+x[(j) * 4])*(pow(x[(j) * 4 + 1],2.0))*__r)/6;
	}
	j = i-1;
	if(j >=1 && j <= 998)
	{
		der[(j) * 4 + 1] = __d*(x[(j+1) * 4]-2.0*x[(j) * 4]+x[(j-1) * 4])/(pow(__dx,2.0))+__r*(pow(x[(j) * 4],2.0))*(1.0-x[(j) * 4])-__a*(x[(j) * 4]-x[(j-1) * 4])/__dx;
		der[(j) * 4 + 2] = ((pow(__dx,-2.0))*__d*(x[(j-1) * 4 + 1]-2.0*x[(j) * 4 + 1]+x[(j+1) * 4 + 1])-2.0*x[(j) * 4]*x[(j) * 4 + 1]*(-1.0+x[(j) * 4])*__r+(1.0/(__dx))*__a*(x[(j-1) * 4 + 1]-x[(j) * 4 + 1])-(pow(x[(j) * 4],2.0))*x[(j) * 4 + 1]*__r)/2;
		der[(j) * 4 + 3] = (-2.0*x[(j) * 4 + 2]*2*(-1.0+x[(j) * 4])*x[(j) * 4]*__r-__d*(pow(__dx,-2.0))*(2.0*x[(j) * 4 + 2]*2-x[(j+1) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)-__a*(x[(j) * 4 + 2]*2-x[(j-1) * 4 + 2]*2)*(1.0/(__dx))-4.0*x[(j) * 4]*(pow(x[(j) * 4 + 1],2.0))*__r-x[(j) * 4 + 2]*2*(pow(x[(j) * 4],2.0))*__r-2.0*(-1.0+x[(j) * 4])*(pow(x[(j) * 4 + 1],2.0))*__r)/6;
	}
}

void MOD_output(int i, double *x, double *d, double t, double *out)
{
	switch(i)
	{
		case 0:
			out[0] = x[396];
			return;
		case 1:
			out[0] = x[1196];
			return;
		case 2:
			out[0] = x[1996];
			return;
		case 3:
			out[0] = x[2796];
			return;
		case 4:
			out[0] = x[3596];
			return;
		case 5:
			out[0] = x[3996];
			return;
	}
}

void QSS_initializeDataStructs(QSS_simulator simulator)
{
	int *outputs = (int*)malloc(6*sizeof(int));
	int *states = (int*)malloc(1000*sizeof(int));
	int i0;
	int i1;
	int i;
	int j = 0;
	simulator->data = QSS_Data(1000,0,0,0,"adr");
QSS_data modelData = simulator->data;

	// Allocate main data structures.
	__L = 10.0;
	__a = 1.0;
	__d = 1.00000e-04;
	__dx = __L/1000;
	__r = 10.0;
	// Initialize model code.
	for(i0 = 0; i0 <= 999; i0++)
	{
		modelData->x[(i0) * 4] = 0.0;
	}
		modelData->x[0] = 1.0;
		modelData->x[3996] = 0.0;
	for(i1 = 0; i1 <= -1; i1++)
	{
		modelData->x[(i1) * 4] = 1.0;
	}
		simulator->settings = SD_SimulationSettings(0);
	for(i = 1; i <= 998; i++)
	{
		modelData->nDS[i] = 3;
	}
	for(i = 1; i <= 998; i++)
	{
		modelData->nSD[i-1]++;
		modelData->nSD[i]++;
		modelData->nSD[i+1]++;
	}
	QSS_allocDataMatrix(modelData);
	// Initialize model data.
	// Initialize model time.
		cleanVector(states,0,1000);

	for(i = 1; i <= 998; i++)
	{
		modelData->DS[i][states[i]++] = i-1;
		modelData->DS[i][states[i]++] = i;
		modelData->DS[i][states[i]++] = i+1;
	}
		cleanVector(states,0,1000);

	for(i = 1; i <= 998; i++)
	{
		modelData->SD[i-1][states[i-1]++] = i;
		modelData->SD[i][states[i]++] = i;
		modelData->SD[i+1][states[i+1]++] = i;
	}
	simulator->time = QSS_Time(1000,0,0,0,ST_Binary,NULL);

	simulator->output = SD_Output("adr",6,0,1000,NULL,0,0,CI_Step,SD_Memory,MOD_output);
SD_output modelOutput = simulator->output;

		modelOutput->nOS[0] = 1;
		modelOutput->nSO[99]++;
		modelOutput->nOS[1] = 1;
		modelOutput->nSO[299]++;
		modelOutput->nOS[2] = 1;
		modelOutput->nSO[499]++;
		modelOutput->nOS[3] = 1;
		modelOutput->nSO[699]++;
		modelOutput->nOS[4] = 1;
		modelOutput->nSO[899]++;
		modelOutput->nOS[5] = 1;
		modelOutput->nSO[999]++;
	SD_allocOutputMatrix(modelOutput,1000,0);
		cleanVector(states,0,1000);

		cleanVector(outputs,0,6);

		sprintf(modelOutput->variable[0].name,"u[100]");
		sprintf(modelOutput->variable[1].name,"u[300]");
		sprintf(modelOutput->variable[2].name,"u[500]");
		sprintf(modelOutput->variable[3].name,"u[700]");
		sprintf(modelOutput->variable[4].name,"u[900]");
		sprintf(modelOutput->variable[5].name,"u[1000]");
		cleanVector(outputs,0,6);

		modelOutput->SO[99][states[99]++] = 0;
		modelOutput->OS[0][outputs[0]++] = 99;
		modelOutput->SO[299][states[299]++] = 1;
		modelOutput->OS[1][outputs[1]++] = 299;
		modelOutput->SO[499][states[499]++] = 2;
		modelOutput->OS[2][outputs[2]++] = 499;
		modelOutput->SO[699][states[699]++] = 3;
		modelOutput->OS[3][outputs[3]++] = 699;
		modelOutput->SO[899][states[899]++] = 4;
		modelOutput->OS[4][outputs[4]++] = 899;
		modelOutput->SO[999][states[999]++] = 5;
		modelOutput->OS[5][outputs[5]++] = 999;
	simulator->model = QSS_Model(MOD_definition,MOD_dependencies,NULL,NULL,NULL);
	free(outputs);
	free(states);
}
