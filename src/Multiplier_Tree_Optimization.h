#pragma once
#ifndef MULTIPLIER_TREE
#define MULTIPLIER_TREE
#include <iostream>
#include <vector>
#include <sstream>
#include "gurobi_c++.h"
using namespace std;
extern int MULT_SIZE;
extern int stages_num;
extern vector<int> input_patterns;
void generate_input_patterns();
void generate_variables_of_multiplier(vector<vector<GRBVar>>& variables_fa, vector<vector<GRBVar>>& variables_ha, vector<vector<GRBVar>>& variables_V, GRBModel& model);
void Initial_constraints_of_V(vector<vector<GRBVar>> variables_V, GRBModel& model);
void generate_constraints_of_h_f_V(vector<vector<GRBVar>> variables_fa, vector<vector<GRBVar>> variables_ha, vector<vector<GRBVar>> variables_V, GRBModel& model);
void generate_constraints_of_last_stage(vector<vector<GRBVar>> variables_V, GRBModel& model);
void generate_cost_of_adders(vector<vector<GRBVar>> variables_fa, vector<vector<GRBVar>> variables_ha, GRBVar& fa_num, GRBVar& ha_num, GRBModel& model);

#endif // !MULTIPLIER_TREE
