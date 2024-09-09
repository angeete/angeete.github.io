// stats.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <cassert>
#include <vector>
#include <cmath>
#include <float.h>
#include <iostream>

using namespace std;

vector<pair<double, int> > summarize(vector<double> v) {

  sort(v);
  vector<pair<double, int>> p;
  int frequency = 1;
  double number = v.at(0);

  for(int i = 0; i<(int)(v.size()); i++){

     for(int j = i+1; j<(int)(v.size()); j++){

        if(v.at(i) == v.at(j)){

            frequency++;
            i++;
        }

     }
    
    p.push_back(std::make_pair(number,frequency));
    frequency = 1;

   if(i < (int)(v.size()-1)){
    number = v.at(i+1);
   }

  }
  return(p);
  assert(false);

  
}

//done
int count(vector<double> v) {

  int count = (int)v.size();
  return count;
  assert(false);
  
}

//done
double sum(vector<double> v) {

  double sum;

     for(int i = 0; i<(int)v.size(); i++){
        sum += v.at(i);
     }

  return sum;
  assert(false);
  
}

//done
double mean(vector<double> v) {

  int number;
  number = count(v);

  double total;
  total = sum(v);

  double mean;
  mean = total/number;

  return mean;
  assert(false);
 
}
//done
double median(vector<double> v) {

  sort(v);
  int number;
  double median;
  number = v.size();

  if(number == 1){

    median = v.at(0);

  }else if(number == 2){

    median = (v.at(1) + v.at(0))/2;

  }else if(number%2 == 0){

    int index = (number/2)-1;
    median = (v.at(index) + v.at(index+1))/2;

  }else{

    int index = round(number/2);
    median = v.at(index);

  }

  return median;
  assert(false);

}
double mode(vector<double> v) {

  sort(v);
  int counter = 1;
  int max = 0;
  double index;
  double mode;

  for(int i = 0; i<(int)(v.size()-1); i++){


     for(int j = i+1; j<(int)(v.size()); j++){


          if(v.at(i) == v.at(j)){

             counter++;
             index = v.at(i);

          }
     }

    if(counter>max){

      max = counter;
      mode = index;

    }

    counter = 1;

  }

  if(max == 1){

     mode = v.at(0);

  }

  return mode;
  assert(false);

}
double min(vector<double> v) {

  double min = v.at(0);
  for (int i = 0; i<v.size(); i++){
    

     if(min>v.at(i)){
        min = v.at(i);
     }
     
  }

  return min;
  assert(false);

}
double max(vector<double> v) {

  double max = v.at(0);
  for (int i = 0; i<(int)v.size(); i++){

     if(max<v.at(i)){
        max = v.at(i);
     }
     
  }

  return max;
  assert(false);

}
double stdev(vector<double> v) {

  int number = count(v);
  double average = mean(v);
  double differenceSquared;
  double summation;
  double stdev;

  for (int i = 0; i<v.size(); i++){
     
     differenceSquared = pow((v.at(i)-average),2);
     summation += differenceSquared;
  }

  stdev = sqrt(summation/(number-1));

  
  return stdev;
  assert(false);
  
}

double percentile(vector<double> v, double p) {

  sort(v);
  double d = p*100;
  
  if((int)(v.size())==1){

   double Percentile = v.at(0);
   return Percentile;

  }
  if(p == 1.0){

   int index = v.size()-1;
   double Percentile = v.at(index);
   return Percentile;

  }
  int size = (int)v.size();

  double n = ((d/100)*(size-1)) + 1;

  double decimalVal = 0;
  double intVal = 0;
  decimalVal = modf(n , &intVal);

  double percentile = v.at(intVal-1) + ((decimalVal)*(v.at(intVal)-v.at(intVal-1)));

  return percentile;
  assert(false);

}
