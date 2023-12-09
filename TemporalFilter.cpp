/*
  TemporalFilter.cpp
  Author: Phillip Schmidt
  
  MIT License

*/

#include "TemporalFilter.h"


TemporalFilter::TemporalFilter(byte filterSize) // initialize filter
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


void TemporalFilter::dataIn(float newData, float newTime) // data input function
{  
	newDataPoint++;	// increment and wrap pointer
	if(newDataPoint >= filterWindowSize)  newDataPoint = 0;
	
	dataList[newDataPoint] = newData; // replace oldest data in array
	timeList[newDataPoint] = newTime; // replace oldest time in array
	
	dataAvgDone  = false;
	slopeIntDone = false;
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
	if( !slopeIntDone ) // Only re-compute if new data has been added
	{
		float topSum = 0;
		float botSum = 0;
		slope = 0;

		avgDataCompute();

		// Generate Slope 
		for(int i=0; i<filterWindowSize; i++)
		{
			float xDif = dataList[i] - dataAverage;
			float yDif = timeList[i] - timeAverage;

			topSum += xDif * yDif;
			botSum += xDif * xDif;
		}

		if( botSum > 0.000001 ) // avoid divide by zero if all sample have the same time
		{
			slope = topSum / botSum;
		}

		// Generate intercept
		intercept = dataAverage - slope * timeAverage;

		slopeIntDone = true;
	}
}


void TemporalFilter::avgDataCompute()
{
	if( !dataAvgDone ) // Only re-compute if new data has been added
	{
		float timeAccumulator = 0;
		float dataAccumulator = 0;
		
		for(int i=0; i<filterWindowSize; i++)
		{
			dataAccumulator += dataList[i]; // sum all values
			timeAccumulator += timeList[i]; // sum all values
		}

		timeAverage = timeAccumulator / filterWindowSize;
		dataAverage = dataAccumulator / filterWindowSize;

		dataAvgDone = true;
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
