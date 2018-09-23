model adr
	constant Integer N=1000;
	parameter Real a=1;
	parameter Real d=1e-4;
	parameter Real r=10;
	parameter Real L=10;
	parameter Real dx=L/N;
	Real u[N]; 
initial algorithm
	// start the grid in 0
	for i in 1:N loop
		u[i]:=0;
	end for;

	// boundary 
      u[1] := 1;
      u[N] :=0;

	// initial concentration u=1 for t=0, x<2
	for i in 1:0.2*N loop
		u[i]:=1;
	end for;

equation
	for i in 2:N-1 loop
		der(u[i]) = d*(u[i+1]-2*u[i]+u[i-1])/(dx^2) + r*(u[i]^2)*(1-u[i]) - a*(u[i]-u[i-1])/dx ;
	end for;
	annotation(

	experiment(
		MMO_Description="",
		MMO_Solver=QSS3,
		MMO_Output={u[:]},
		StartTime=0.0,
		StopTime=10.0,
		Tolerance={1e-3},
		AbsTolerance={1e-3}
	));
end adr;
