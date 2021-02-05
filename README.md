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
- Install Gurobi at a self-defined path `Gurobi_Path`
- Set up a C++ project in Visio Studio;
- Add the source files and header files in the folder `src/`;
- Configure the library path of Gurobi for this project:
  Project->Property->
  - VC++ directory->Include directory->Edit->New line: `Gurobi_Path\win64\include`;
  - VC++ directory->Library directory->Edit->New line: `Gurobi_Path\win64\lib`;
  - Liner->Input->Additional dependencies->Edit->New line： `gurobi_c++mdd2017.lib`;
  - Liner->Input->Additional dependencies->Edit->New line： `gurobi90.lib`.




- 


