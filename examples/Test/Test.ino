/*
	TemporalFilter - Test.ino
	Author: Phillip Schmidt
	
	MIT License

	This is a unit test that processes known inputs and compares to expected outputs.

*/

#include <TemporalFilter.h>

TemporalFilter myFilter(10);

void setup()
{
  Serial.begin(57600);
  while(!Serial);
  delay(1000);
  Serial.println("");Serial.println("");

  //	TEST #1 - feed in 10 samples and test the output
  // (time, data)
  Serial.println("Start Test #1");
  myFilter.dataIn(1.12, 1.91);
  myFilter.dataIn(1.85, 2.63);
  myFilter.dataIn(2.58, 2.85);
  myFilter.dataIn(3.31, 2.81);
  myFilter.dataIn(4.04, 2.85);
  myFilter.dataIn(4.77, 3.29);
  myFilter.dataIn(5.50, 4.24);
  myFilter.dataIn(6.23, 5.55);
  myFilter.dataIn(6.96, 6.89);
  myFilter.dataIn(7.69, 7.91);

  Serial.print("Test #1 Slope:     ");
  floatEquals( myFilter.getSlope(), 0.84723952);
  Serial.print("Test #1 Intercept: ");
  floatEquals( myFilter.getIntercept(), 0.36090992);
  Serial.print("Test #1 Filter:    ");
  floatEquals( myFilter.filterResult(), 6.87618182);
  Serial.print("Test #1 Filter+1:  ");
  floatEquals( myFilter.filterResult(8.69), 7.72342134);

	//	TEST #2 - feed in 5 more samples
  Serial.println("Start Test #2");
  myFilter.dataIn(8.62,9.49);
  myFilter.dataIn(9.55,8.74);
  myFilter.dataIn(10.48,8.09);
  myFilter.dataIn(11.41,8.14);
  myFilter.dataIn(12.34,8.92);

  Serial.print("Test #2 Slope:     ");
  floatEquals( myFilter.getSlope(), 0.67641003);
  Serial.print("Test #2 Intercept: ");
  floatEquals( myFilter.getIntercept(), 1.47459417);
  Serial.print("Test #2 Filter:    ");
  floatEquals( myFilter.filterResult(), 9.82149398);
  Serial.print("Test #2 Filter+1:  ");
  floatEquals( myFilter.filterResult(13.34), 10.49790402);

}

void loop()
{

}

void floatEquals(float a, float b)
{
  if( abs(a-b) < 0.000001 )
  {
      Serial.println(" PASS");
  }
  else
  {
    Serial.print(" FAIL  ");
    Serial.print(a, 5);Serial.print(" != ");Serial.println(b, 5);
  }
}

