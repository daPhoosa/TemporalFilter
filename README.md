Temporal Data Filter
====================

Temporal filter for the Arduino ecosystem

 
Filtering is performed by creating a least-squares linear regression through the data.  The resulting value can be either the point on the linear regression at the time of the most recent sample, or a different time passed as an argument.
   
Object Creation:
```
TemporalFilter myFilter( filter_Size );
```

`filter_Size:` Number of samples in the filter window.  Larger sizes improve filter smoothness but increase computational time and response lag.

Add data to the filter:
```
myFilter.dataIn( new_data, new_time );
```
Get filter result:
```
filtered_value = myFilter.filterResult();
extrapolated_value = myFilter.filterResult( some_future_time );
```
Additionally the average of all time or data in the filter can be accessed:
```
average_data = myFilter.getAvgData();
average_time = myFilter.getAvgTime();
```
