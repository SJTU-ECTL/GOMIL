#pragma once
#ifndef ADDER_TREE
#define ADDER_TREE
#include "gurobi_c++.h"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
extern int PARAMETER_W;
extern int PARAMETER_L;
void generate_variables_obj(vector<vector<GRBVar>>& variables_obj, vector<GRBVar> final_stage, GRBModel& model);
void generate_variables(vector<vector<GRBVar>>& variables_x, vector<vector<GRBVar>>& variables_b, vector<GRBVar> final_stage, GRBModel& model);
void generate_variables_of_indicators(vector<vector<GRBVar>>& variables_indicator, vector<GRBVar> final_stage, GRBModel& model);
void generate_variables_of_sp(vector<vector<GRBVar>>& variables_sp, vector<GRBVar> final_stage, GRBModel& model);
void generate_variables_of_delay(vector<vector<GRBVar>>& variables_d, vector<GRBVar> final_stage, GRBModel& model);
void Initial_constraints_b_x_d_sp_id_0(vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_b, vector<vector<GRBVar>> variables_d, vector<vector<GRBVar>> variables_sp, vector<vector<GRBVar>> variables_indicator, vector<GRBVar> final_stage, GRBModel& model);
void generate_constraints_b(vector<vector<GRBVar>> variables_b, GRBModel& model);
void generate_constraints_id(vector<vector<GRBVar>> variables_indicator, GRBModel& model);
void generate_constraints_x(vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_b, GRBModel& model);
void generate_constraints_obj(vector<vector<GRBVar>> variables_obj, vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_d, GRBModel& model);
//void generate_constraints_x_d_sp_id(vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_b, vector<vector<GRBVar>> variables_d, vector<vector<GRBVar>> variables_sp, vector<vector<GRBVar>> variables_indicator, GRBModel& model);
void generate_constraints_x_d_sp_id(vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_b, vector<vector<GRBVar>> variables_d, vector<vector<GRBVar>> variables_sp, GRBModel& model, int level);
int glo_opt_adder_tree(vector<int> last_stage, int last_split_size, GRBEnv env);
void display_split(vector<vector<GRBVar>> variables_sp, int last_split_size);
#endif // !ADDER_TREE

