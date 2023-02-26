// File: gsyscall.cpp
// Description: gnuplot system call
// WebSite: http://cool-emerald.blogspot.com
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye

#include <iostream>
using namespace std;
int main() {
    cout<<"Using gnuplot"<<endl;
    system("gnuplot -p -e \"set datafile separator ',';plot 'test.csv'\"");
    return 0;
}