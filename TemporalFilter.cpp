/*
  TemporalFilter.cpp
  Author: Phillip Schmidt, 12/2023
  
  MIT License

*/

#include "TemporalFilter.h"


TemporalFilter::TemporalFilter(byte filterSize)
{	
	filterWindowSize = filterSize;

	dataList = (float*) calloc (filterSize, sizeof(float));		// create array for data
	timeList = (float*) calloc (filterSize, sizeof(float));		// create array for time
}


TemporalFilter::~TemporalFilter()
{
	free(dataList);
	free(timeList);
}


void TemporalFilter::dataIn(float newTime, float newData)
{  
	newDataPoint++;	// increment and wrap pointer
	if(newDataPoint >= filterWindowSize)  newDataPoint = 0;
	
	dataList[newDataPoint] = newData; // replace oldest data in array
	timeList[newDataPoint] = newTime; // replace oldest time in array
	
	newDataFlag_Average  = true;
	newDataFlag_SlopeInt = true;
}


float TemporalFilter::filterResult()
{
	return filterResult(timeList[newDataPoint]);
}


float TemporalFilter::filterResult(float time)
{
	slopeInterceptCompute();

	return slope * time + intercept;
}


void TemporalFilter::slopeInterceptCompute()
{
	if( newDataFlag_SlopeInt )
	{
		float numerator   = 0;
		float denominator = 0;

		avgDataCompute();

		// Generate Slope and Intercept by Least-Squares regression
		for(int i=0; i<filterWindowSize; i++)
		{
			float xDif = timeList[i] - timeAverage;
			float yDif = dataList[i] - dataAverage;

			numerator   += xDif * yDif;
			denominator += xDif * xDif;
		}

		if( denominator > 0.000001f ) // avoid divide by zero if all samples have the same time
		{
			slope = numerator / denominator;
		}
		else
		{
			slope = 0;
		}

		intercept = dataAverage - (slope * timeAverage);

		newDataFlag_SlopeInt = false;
	}
}


void TemporalFilter::avgDataCompute()
{
	if( newDataFlag_Average )
	{
		float timeAccumulator = 0;
		float dataAccumulator = 0;
		
		for(int i=0; i<filterWindowSize; i++)
		{
			dataAccumulator += dataList[i];
			timeAccumulator += timeList[i];
		}

		timeAverage = timeAccumulator / filterWindowSize;
		dataAverage = dataAccumulator / filterWindowSize;

		newDataFlag_Average = false;
	}
}


float TemporalFilter::getSlope()
{
	slopeInterceptCompute();
	return slope;
}


float TemporalFilter::getIntercept()
{
	slopeInterceptCompute();
	return intercept;
}


float TemporalFilter::getAvgData()
{
	avgDataCompute();
	return dataAverage;
}


float TemporalFilter::getAvgTime()
{
	avgDataCompute();
	return timeAverage;
}
