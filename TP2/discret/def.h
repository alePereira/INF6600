#ifndef DEF_H
#define DEF_H

# include "cosim.h" 
// definitions des  varaibles d'environnement ajoutees pour la cosimulation
#define MIXED_SIGNAL sc_get_curr_simcontext()->MIXED_SIGNAL

#define MemPtrTime sc_get_curr_simcontext()->MemPtr
#define Speriod_0 sc_get_curr_simcontext()-> Speriod_0
#define Speriod_1 sc_get_curr_simcontext()-> Speriod_1

#define et_mat0 sc_get_curr_simcontext()->et_mat[0]
#define et_mat1 sc_get_curr_simcontext()->et_mat[1]
#define et_mat2 sc_get_curr_simcontext()->et_mat[2]
#define et_mat3 sc_get_curr_simcontext()->et_mat[3]
#define et_mat4 sc_get_curr_simcontext()->et_mat[4]
#define et_mat5 sc_get_curr_simcontext()->et_mat[5]
#define et_mat6 sc_get_curr_simcontext()->et_mat[6]
#define et_mat7 sc_get_curr_simcontext()->et_mat[7]
#define et_mat8 sc_get_curr_simcontext()->et_mat[8]
#define et_mat9 sc_get_curr_simcontext()->et_mat[9]

#define SET_COSIM set_cosim();\
		MemPtrTime = set_simcontext();\
		sc_get_curr_simcontext()->_hSemClient = PassSemPtrsClient();\
		sc_get_curr_simcontext()->_hSemCreator = PassSemPtrsCreator();
#define CLOSE_COSIM close_cosim();

#define FS sc_get_curr_simcontext()->FS
#define UE sc_get_curr_simcontext()->UE

#endif