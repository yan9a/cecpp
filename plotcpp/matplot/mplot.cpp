// File: mplot.cpp
// Description: using matplotlib with C++
// WebSite: http://cool-emerald.blogspot.com
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye

// References
// https://github.com/lava/matplotlib-cpp

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() 
{
    int n = 100;
    std::vector<double> x(n), y(n), z(n);
    for(int i=0; i<n; ++i) {
        x.at(i) = i;
        y.at(i) = 50.0 + 25.0 * sin(2*M_PI*i/50.0);
        z.at(i) = i + i * sin(2*M_PI*i/50.0);
    }
    plt::plot(x, y);
    plt::named_plot("z", x, z);
    plt::title("Test matplot");
    plt::show();
    // save figure
    // const char* filename = "./mplot.png";
    // plt::save(filename);
}
