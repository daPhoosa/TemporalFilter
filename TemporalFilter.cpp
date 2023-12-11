/*
  TemporalFilter.cpp
  Author: Phillip Schmidt
  
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
	
	dataAvgNew  = true;
	slopeIntNew = true;
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
	if( slopeIntNew )
	{
		float topSum = 0;
		float botSum = 0;
		slope = 0;

		avgDataCompute();

		// Generate Slope and Intercept by Least-Squares regression
		for(int i=0; i<filterWindowSize; i++)
		{
			float xDif = timeList[i] - timeAverage;
			float yDif = dataList[i] - dataAverage;

			topSum += xDif * yDif;
			botSum += xDif * xDif;
		}

		if( botSum > 0.000001 ) // avoid divide by zero if all samples have the same time
		{
			slope = topSum / botSum;
		}

		intercept = dataAverage - (slope * timeAverage);

		slopeIntNew = false;
	}
}


void TemporalFilter::avgDataCompute()
{
	if( dataAvgNew )
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

		dataAvgNew = false;

		//Serial.print("Avg Time: ");Serial.println(timeAverage, 3);
		//Serial.print("Avg Data: ");Serial.println(dataAverage, 3);
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
