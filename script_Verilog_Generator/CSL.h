#pragma once
#ifndef CSL_H
#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void verilog_template_CSL(string module_name, vector<string> ports, int input_ports_num, ofstream& f2, vector<int> input_ports_size);
void function_csl(vector<string> ports, vector<int> input_ports_size, int input_ports_num, ofstream& f2);
void CSL_V();
#endif // !CSL_H

