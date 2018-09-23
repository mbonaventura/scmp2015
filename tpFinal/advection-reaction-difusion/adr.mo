model adv_dif_reac
	constant Integer N=1000;
	parameter Real a=1;
	parameter Real d=1e-4;
	parameter Real r=10;
	parameter Real L=10;
	parameter Real dx=L/N;
	Real u[N];
initial algorithm
	for i in 1:0.2*N loop
		u[i]:=1;
		end for;
		equation
		der(u[1])=-a*(u[1]-1)/dx+d*(u[2]-2*u[1]+1)/(dx^2)+r*(u[1]^2)*(1-u[1]);
		der(u[N])=-a*(u[N]-u[N-1])/dx+d*(u[N-1]-2*u[N]+u[N-1])/(dx^2)+r*(u[N]^2)*(1-u[N]
		);
		for i in 2:N-1 loop
		der(u[i])=-a*(u[i]-u[i-1])/dx+ d*(u[i+1]-2*u[i]+u[i-1])/(dx^2)+
		r*(u[i]^2)*(1-u[i]);
	end for;
	annotation(

	experiment(
		MMO_Description="",
		MMO_Solver=QSS3,
		MMO_Output={u[100], u[300], u[500],u[700], u[900], u[1000]},
		StartTime=0.0,
		StopTime=5.0,
		Tolerance={1e-3},
		AbsTolerance={1e-3}
	));
end adv_dif_reac;
