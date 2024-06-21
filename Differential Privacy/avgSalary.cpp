#include <iostream>
#include <vector>
#include <cmath>
#include <random>
//#include <iterator>

double laplaceNoise(double scale) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.5, 0.5);
    double u = dis(gen);
    return scale * std::sin(u) * std::log(1 - 2 * std::abs(u));
}

double computePrivateAverage(const std::vector<double>& salaries, double epsilon) {
    double sum = 0.0;
    for (double salary : salaries) {
        sum += salary;
    }
    double avg = sum / salaries.size();
    double max_salary=*std::max(salaries.begin(), salaries.end());
    double min_salary=*std::min(salaries.begin(), salaries.end());
    double sensitivity = (max_salary - min_salary) / salaries.size();
    double noise = laplaceNoise(sensitivity / epsilon);
    return avg + noise;
}

int main() {
    std::vector<double> salaries = {50000, 60000, 55000, 70000, 65000};
    double epsilon = 1.0;
    double privateAverage;
    int count =0;
    int simulation;
    std::cout<<"How many simulation you want to run: ";
    std::cin>>simulation;
    while(count<simulation){
        privateAverage = computePrivateAverage(salaries, epsilon);
    std::cout << "Private Average Salary: " << privateAverage << std::endl;
    count+=1;
    }
    
    return 0;
}
