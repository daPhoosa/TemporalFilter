/*
  TemporalFilter.h 
  Author: Phillip Schmidt

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
			//float getStDev();
			//float getMin();
			//float getMax();
		
		
		private:
			void slopeInterceptCompute();
			void avgDataCompute();

			bool dataAvgNew, slopeIntNew;

			float dataAverage, timeAverage;
			float slope, intercept;
			
			byte filterWindowSize; // number of samples window	
			byte newDataPoint;	   // newest data point in array index	
			
			float * dataList;			// array for data	
			float * timeList;			// array for coefficients	

	};

#endif
