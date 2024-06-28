// Online C++ compiler to run C++ program online
#include <iostream>
#include <cmath>
//#include <iomanip>
   
using namespace std;
void f(double &a, double &b, double &result, int &iteration){
    int k=1;
    while(k<iteration){
        result=pow(a,pow(2,k))/(pow(a,pow(2,k))+pow(b,pow(2,k)));
        //cout<<result<<endl;
        k+=1;
    }
}

int main() {
    // Write C++ code here
    
double a=3005,b=1000,result=0;
//a=3005,b=4000;
//a=3005,b=3005;
int iteration=4;

f(a,b,result,iteration);
// Set precision to 2 decimal places and fixed format
//cout<<result<<endl;
if ((std::floor(abs(result-1)*100)/100)==0) cout <<a <<" > "<<b;
else if (std::floor(abs(result-.5)*100)/100==0) cout <<a <<" = "<<b;
else cout <<a <<" < "<<b;
//cout<<result;
return 0;
}
