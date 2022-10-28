Problem Description:  

-> The heat equation with a source term is  
$$\frac{\partial T}{\partial t} = \alpha \frac{\partial^2 T}{\partial x^2} + S(x), 0 \leq x \leq L$$  
-> The initial and boundary conditions are $T(x,0) = 0$, $T(0,t) = 0$, and $T(L,t)=T_{steady}(L)$. Taking $\alpha = 1$, $L=15$ and $S(x) = -(x^2-4x +2) e^{-x}$. The exact steady solution is  
$$T_{steady}(x) = x^2 e^{-x}$$  
-> Solve the equation to steady state on a uniform grid with a grid spacing of $\Delta x = 1,0.1$ and employing a time step of $\Delta t =  0.005$. For time advancement, Explicit Euler, Implict Euler and Crank-Nicolson methods are used along with second-order central difference scheme for spatial derivative.  
-> The exact and numerical solutions are compared along with the variation of error in 1-norm.  

-> The discrete equation for Explicit Euler time advancement with $2^{nd}$ order Central Difference scheme for spatial derivative is  
$$T_i^{n+1} = F T_{i-1}^n + (1-2F)T_i^n + FT_{i+1}^n + S(x_i)\Delta t, F = \frac{\alpha \Delta t}{\Delta x^2}$$
-> The discrete equation for Implicit Euler time advancement with $2^{nd}$ order Central Difference scheme for spatial derivative is  
$$-FT_{i-1}^{n+1} + (1+2F)T_i^{n+1} - FT_{i+1}^{n+1} = T_i^n + S(x_i)\Delta t, F = \frac{\alpha \Delta t}{\Delta x^2}$$
-> The discrete equation for Crank-Nicolson time advancement with $2^{nd}$ order Central Difference scheme for spatial derivative is  
$$-FT_{i-1}^{n+1} + (1+2F)T_i^{n+1} - FT_{i+1}^{n+1} = F T_{i-1}^n + (1-2F)T_i^n + FT_{i+1}^n + S(x_i)\Delta t, F = \frac{\alpha \Delta t}{2 \Delta x^2}$$
-> The discrete equations obtained for implicit schemes involves solving for a system of linear algebraic equations. Thus, thomas algorithm is used to solve for a tri-diagonal matrix system.  
