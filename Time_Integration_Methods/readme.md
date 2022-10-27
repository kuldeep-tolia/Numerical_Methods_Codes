Problem Description:  

-> This is a program to solve for an initial value problem using different numerical time integration methods and compare the errors associated with different time step sizes.  
-> Consider the following initial value problem:  
$$\frac{dy}{dt} = -\lambda \left( y - e^{-t} \right) - e^{-t}, \lambda>0$$  
-> The initial condition is $y(t=0)=y_0=10$, $\lamda=10$.  
-> The time step sizes chosen are $\Delta t=0.1, 0.05, 0.025, 0.0125, 0.00625$ and integrated from $t=0$ to $t=0.8$.  
-> The exact analytical solution to this problem is:  
$$y = e^{-t} + \left( y_0 -1 \right) e^{-\lambda t}$$
-> Error between the numerical and the exact solution is compared.
