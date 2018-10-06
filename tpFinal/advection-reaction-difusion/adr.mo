model adr
	constant Integer N=5000; 
	constant Integer LEN=10; 
	constant Real INIT_CONC_L=(N/2)-(N/(LEN*2)); 
	constant Real INIT_CONC_H=(N/2)+(N/(LEN*2)); 
	parameter Real a=1;
	parameter Real d=0.5;
	parameter Real r=0.1;
	parameter Real dx=10/N;
	Real u[N]; 
initial algorithm
	// start the grid in 0
	for i in 1:N loop
		u[i]:=0;
	end for;

	// boundary 
      u[1] := 0;
      u[N] :=0;

	// initial concentration u=1 for t=0, x<2
	for i in INIT_CONC_L:INIT_CONC_H loop
		u[i]:=1;
	end for;

equation
      // boundaries do not change
	der(u[1])=0;
	der(u[N])=0;

	for i in 2:N-1 loop
		der(u[i]) = d*(u[i+1]-2*u[i]+u[i-1])/(dx^2) + r*(u[i]^2)*(1-u[i]) - a*(u[i]-u[i-1])/dx ;
	end for;
	annotation(
	experiment(

		MMO_Description="",
		MMO_Solver=LIQSS,
		StartTime=0.0,
		StopTime=10.0,
		Tolerance={1e-3},
		AbsTolerance={1e-3}
	));
end adr;
