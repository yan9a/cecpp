// File: oplot.cpp
// Description: plotting with octave
// WebSite: http://cool-emerald.blogspot.com
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye

#include <iostream>
using namespace std;
int main() {
    cout<<"Octave plot simple example"<<endl;
    system("octave -qf ofunc.m");
    return 0;
}
