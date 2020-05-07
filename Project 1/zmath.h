#ifndef ZMATH_H
#define ZMATH_H

//Makes the number positive. AKA returns the absolute value.
double absolute(double val){
	if(val<0){
		val *= -1;
	}
	return val;
}

//returns the *base* raised to the *exponent* power
double power(double base, double exponent){
	double final = 1;
	for(int i = 0; i<exponent; i++){
		final *= base;
	}
	return final;
}


//Returns "an approximation" of the square root.
double squareroot(double n){
  double low = 0;
  double high = n;
  double mid = (high + low)/2;

  for (int i = 0; i<2500; i++){ //2500 seems to get close enough in my testing
  	mid = (high+low)/2;
  	if(mid*mid > n){
  		high=mid;
  	}
  	else if(mid*mid < n){
  		low = mid;
  	}
  	else{
  		return mid;
  	}
  }
  return mid;
}


//Returns the number that is bigger
double maxima(double a, double b){
	if(a>=b){
		return a;
	}
	else{
		return b;
	}
}

//Returns the smaller number
double minima(double a, double b){
	if(a<=b){
		return a;
	}
	else{
		return b;
	}
}

double round(double a){
	return (double)((int)a);
}
#endif