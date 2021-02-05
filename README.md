# GOMIL: Global Optimization of Multiplier by Integer Linear Programming
This project proposes GOMIL, a novel global optimization technique for designing better multipliers. The main idea of GOMIL is to establish an ILP formulation to jointly optimize the compressor tree and the prefix structure in a multiplier [1].

## Reference paper(s):
- [1]: GOMIL: Global Optimization of Multiplier by Integer Linear Programming (Weihua Xiao, Weikang Qian, Weiqiang Liu, DATE 2021)

## Requirements
- OS: 64-bit Windows/Linux
- Gurobi (version >= 9.0)
- visual studio (version >= 2017)
- gcc
- g++

Note that this project uses C++ interface of Gurobi optimizer 9.0, a mixed ILP solver, to solve the ILP problems (link: https://www.gurobi.com).

## Getting Started
### Configuration in VS Studio
- Install Gurobi at a self-defined path `Gurobi_Path`
- Set up a C++ project in Visio Studio;
- Add the source files and header files in the folder `src/`;
- Configure the library path of Gurobi for this project:

  Project->Property->
  - VC++ directory->Include directory->Edit->New line: `Gurobi_Path\win64\include`;
  - VC++ directory->Library directory->Edit->New line: `Gurobi_Path\win64\lib`;
  - Linker->Input->Additional dependencies->Edit->New line： `gurobi_c++mdd2017.lib`;
  - Linker->Input->Additional dependencies->Edit->New line： `gurobi90.lib`.
  
### Configuration in Code
- `PARAMETER_W` : parameter to control the weight between adder tree's delay and area, e.g., area+ `PARAMETER_W` * delay;
- `PARAMETER_L` : speedup technique that control the optimized bits of adder tree;
- `MULT_SIZE` : size of optimized multiplier;
- `stages_num` : number of compressor tree's stages, which us consistent with wallace tree's.
-  `Time_Bound_s` : runtime upper bound of optimization;

### Example
Optimize a 10 * 10  multiplier, set: 
- MULT_SIZE = 10;
- stages_num = 5;
- PARAMETER_W = 10;
- PARAMETER_L = 8;

In this case, the results of this GOMIL multiplier are saved into `Tune_WL/gurobi_10_10.sol` (compression tree) and `Tune_WL/gurobi_glo_adder_10.sol` (adder tree part).


