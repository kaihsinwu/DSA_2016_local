usage:
	1. make
		*build the program
	2. make run --silent < "input file path" > "output file path"
		*The result will be using stdin (cin) to input and stdout (cout) to output. 
	3. make rebuild
		*rebuild the program entirely. 

Algorithm:
	The row operations of gaussian elimination can be think as multiply the Operator Matrixs E_i to A for step i=0 ,i++ to let A becomes row echlon form and then keep doing row operations  until A becomes Identity I:
	
	{ E_n * ... * E_(a+2) * E_(a+1) }*{ E_a * ... * E_1 * E_0 } * A = I

	= invA * A = I

	Infact, the A can be seen as  L * U by combine the row operator Matrixes 	where L has non zero terms on left down triangular ; U has non zero terms on right upper triangular. So called LU decomposition of A

	A = L * U
	A * invA = L * U * invA = I
	
	invA can be derive simply by : 
	1. L * D = I , solve D
	2. U * invA = D , solve invA 
	
	

 

	  
	
