/*
  TemporalFilter.h 
  Author: Phillip Schmidt, 12/2023

  MIT License

 */

#ifndef TemporalFilter_h

	#define TemporalFilter_h

	#include "Arduino.h"

	class TemporalFilter
	{
	
		public: 
			TemporalFilter(byte filterSize);
			~TemporalFilter();
			
			void  dataIn(float newTime, float newData);
			float filterResult();
			float filterResult(float time);
			
			float getAvgData();
			float getAvgTime();
			float getSlope();
			float getIntercept();
			float getStDev();
			//float getMin();
			//float getMax();
		
		
		private:
			void slopeInterceptCompute();
			void avgDataCompute();

			bool newDataFlag_Average, newDataFlag_SlopeInt; // indicate that re-computation is needed due to new data

			float dataAverage, timeAverage;
			float slope, intercept;
			float StDev;
			
			byte filterWindowSize; // number of samples window	
			byte newDataPoint;	   // index for newest data point in array
			
			float * dataList;		// array for data	
			float * timeList;		// array for time	

	};

#endif
