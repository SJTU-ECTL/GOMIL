#include "gurobi_c++.h"
#include "Adder_Tree_Optimization.h"
#include "Multiplier_Tree_Optimization.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
vector<int> input_patterns;
int PARAMETER_W, PARAMETER_L, MULT_SIZE, stages_num;
//vector<int> para_Ms = { 10,16,20,32,64 };
//vector<int> para_Ws = { 5,8,/*10*/13 };
//vector<int> para_Ls = { 10,9,8,7 };
//vector<int> para_Ss = { 5,6,7,8,10 };

int main()
{
	
		//initial parameter m, stages_num
		MULT_SIZE = 10;
		stages_num = 5;
		//initial parameter W,L
		PARAMETER_W = 10;
		PARAMETER_L = 8;
		//define runtime upper bound
		int Time_Bound_s = 7200;
		//update the file path
		string filename = "..//Tune_WL//gurobi_" + to_string(MULT_SIZE) + "_" + to_string(MULT_SIZE);

		//optimization process
		try {
				/*******Set up environment******/
				GRBEnv env = GRBEnv();
				GRBModel model = GRBModel(env);
				model.set(GRB_StringParam_LogFile, filename + ".log");
				//model.set(GRB_INT_PAR_MIPFOCUS, "1");
				model.set(GRB_INT_PAR_PRESOLVE, "2");
				model.set(GRB_DBL_PAR_TIMELIMIT, to_string(Time_Bound_s));
				//model.set(GRB_DBL_PAR_HEURISTICS, "0.5");
				model.set(GRB_DBL_PAR_MIPGAP, "0.005"); 
				/*******generate input patterns******/
				input_patterns = {};
				generate_input_patterns();
				/*******Create variables******/
				//Compressor tree
				vector<vector<GRBVar>> variables_fa, variables_ha;
				vector<vector<GRBVar>> variables_V;
				GRBVar fa_num, ha_num;
				generate_variables_of_multiplier(variables_fa, variables_ha, variables_V, model);

				//Adder tree	
				vector<vector<GRBVar>> variables_x;
				vector<vector<GRBVar>> variables_b;
				vector<vector<GRBVar>> variables_d;
				vector<vector<GRBVar>> variables_sp;
				vector<vector<GRBVar>> variables_indicator;
				vector<vector<GRBVar>> variables_obj;

				//interface
				vector<GRBVar> final_stage;

				//make simplification(2-27)

				for (int i = variables_V[0].size() - PARAMETER_L; i < variables_V[variables_V.size() - 1].size() - 0; i++)
				{
					final_stage.push_back(variables_V[variables_V.size() - 1][i]);
				}

				//vector<GRBVar> final_stage = variables_V[variables_V.size() - 1];
				generate_variables(variables_x, variables_b, final_stage, model);
				generate_variables_of_delay(variables_d, final_stage, model);
				generate_variables_of_sp(variables_sp, final_stage, model);
				generate_variables_obj(variables_obj, final_stage, model);

				/*Add general constraints*/
				//Compressor Tree
				Initial_constraints_of_V(variables_V, model);
				generate_constraints_of_h_f_V(variables_fa, variables_ha, variables_V, model);
				generate_constraints_of_last_stage(variables_V, model);
				//Adder Tree
				Initial_constraints_b_x_d_sp_id_0(variables_x, variables_b, variables_d, variables_sp, variables_indicator, final_stage, model);
				generate_constraints_b(variables_b, model);
				generate_constraints_obj(variables_obj, variables_x, variables_d, model);
				generate_constraints_x_d_sp_id(variables_x, variables_b, variables_d, variables_sp, model, PARAMETER_L);

				// Set objective
				GRBLinExpr obj = 0;
				obj = variables_obj[PARAMETER_L - 1][variables_obj[PARAMETER_L - 1].size() - 1];
				generate_cost_of_adders(variables_fa, variables_ha, fa_num, ha_num, model);
				obj += (4 * fa_num + 2 * ha_num);

				model.setObjective(obj, GRB_MINIMIZE);

				// Save problem
				model.write(filename + ".lp");
			
				// Optimize model
				model.update();

				model.optimize();

				//Save solution

				model.write(filename + ".sol");

				cout << fa_num.get(GRB_StringAttr_VarName) << " "
					<< fa_num.get(GRB_DoubleAttr_X) << endl;
				cout << ha_num.get(GRB_StringAttr_VarName) << " "
					<< ha_num.get(GRB_DoubleAttr_X) << endl;
				cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;

				/*repeatly*/
				vector<int> last_stage;
				for (int i = 0; i < variables_V[variables_V.size() - 1].size(); i++)
				{
					cout << variables_V[variables_V.size() - 1][i].get(GRB_DoubleAttr_X) << ", ";
				}

				for (int i = variables_V.size() - 1; i < variables_V[variables_V.size() - 1].size(); i++)
				{
					last_stage.push_back(variables_V[variables_V.size() - 1][i].get(GRB_DoubleAttr_X));
				}

				cout << endl << endl;

				/*global optimization of adder tree*/
				int glo_adder_cost = glo_opt_adder_tree(last_stage, 0, env);
				cout << "The total cost of multiplier is :" << fa_num.get(GRB_DoubleAttr_X) * 3 + ha_num.get(GRB_DoubleAttr_X) * 2 + glo_adder_cost << endl;
					
		}
		catch (GRBException e) {
					cout << "Error code = " << e.getErrorCode() << endl;
					cout << e.getMessage() << endl;
		}
		catch (...) {
					cout << "Exception during optimization" << endl;
		}

		system("pause");
		return 0;
}
