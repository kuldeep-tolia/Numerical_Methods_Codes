Problem Description:  

-> Consider an equation $u(x) = 7 - xtan(x)$ that governs heat conduction in a plane wall for $x=[-1,1]$.  
-> The analytical expression for the first derivative of the given equation is  
$$\frac{du}{dx} = -tan(x) - x sec^2x$$  
-> This is a program to compute the first derivative using first, second and fourth-order accurate forward-difference formulae.  
-> The grid size is varied as $\Delta x = 0.1, 0.01, 0.001$ and a comparison is made for the truncation error with the grid size.  
-> The following are the forward-difference formulae to compute the first derivative, along with their corresponding truncation errors:  

- $1^{st}$ order accurate:  
$$\left. \frac{du}{dx} \right|_0 = \frac{ u_1 - u_0}{\Delta x}, TE \sim O(\Delta x)$$ 

- $2^{nd}$ order accurate:    
$$\left. \frac{du}{dx} \right|_0 = \frac{ 4u_1 - 3u_0 - u_2}{ 2 \Delta x}, TE \sim (\Delta x^2)$$

- $4^{th}$ order accurate:    
$$\left. \frac{du}{dx} \right|_0 = \frac{ 48u_1 - 25u_0 - 36u_2 + 16u_3 - 3u_4}{ 12 \Delta x}, TE \sim (\Delta x^4)$$

where $TE$ denotes the truncation error.

NOTE: The corresponding backward-difference formulae is used of the same order of accuracy, to compute the first derivative near the boundary location.  
