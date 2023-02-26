// File: gplot.cpp
// Description: using gnuplot with C++
// WebSite: http://cool-emerald.blogspot.com
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye

// References
// https://code.google.com/archive/p/gnuplot-cpp/
// http://www.gnuplot.info/links.html

#include <iostream>
#include "gnuplot_i.hpp"
using namespace std;
int main() {
    cout<<"Gnu plot simple example"<<endl;
    try
    {
        Gnuplot g1;
        vector<double> x, y;
        for(int i=0;i<100;i++){
            x.push_back((double)i);             // x[i] = i
            y.push_back((double)i * (double)i); // y[i] = i^2
        }

        g1.set_grid();
        g1.set_style("lines").plot_xy(x,y,"2d plot");
        g1.savetopng("test");
        g1.replot();

        cout<<"Press enter to exit"<<endl;
        cin.get();
    }
    catch (GnuplotException ge)
    {
        cout << ge.what() << endl;
    }
    return 0;
}
