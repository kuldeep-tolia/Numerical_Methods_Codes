Problem Description:  

-> Consider an equation $u(x) = 7 - xtan(x)$ that governs heat conduction in a plane wall for $x=[-1,1]$.  
-> The analytical expression for the first derivative of the given equation is  
$$\frac{du}{dx} = -tan(x) - x sec^2x$$  
-> This is a program to compute the first derivative using first, second and fourth-order accurate forward-difference formulae.  
-> The grid size is varied as $\Delta x = 0.1, 0.01, 0.001$ and a comparison is made for the truncation error with the grid size.  