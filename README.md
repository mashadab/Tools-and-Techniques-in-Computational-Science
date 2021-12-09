# Tools and Techniques in Computational Science

## Author
- Mohammad Afzal Shadab (mashadab@utexas.edu)

## Affiliation
Oden Institute for Computational Engineering and Sciences / Jackson School of Geosciences / University of Texas Institute for Geophysics
The University of Texas at Austin

## 2-line Summary
This repository has codes from Tools and Techniques in Computational Science course. These codes have been validated against the reference.

# Skills required
1. C++ 
2. Linux / Unix
3. Bash scripting
4. Version control (Git)
5. Stampede2 job launching
6. Portable, Extensible Toolkit for Scientific Computation (PETSc) 
7. GRVY (Toolkit library for supporting high-performance, scientific applications)
8. Manufactured Analytical Solution Abstraction (MASA)
9. Bash automated testing system (bats)
10. Travis CI
11. Docker

## Project: Solving the heat equation using high order methods on Stampede2 Supercomputer at Texas Advanced Computing Center ([Report](), [YouTube video](https://www.youtube.com/watch?v=I4WwXOMeBo4&t=1s))
In this project, I performed testing mainly verification, regression, and runtime performance. I have also used these libraries: GRVY for timekeeping and debugging, MASA for method of manufactured solutions, bash automated testing system (bats) for designing regression tests. Finally, I have shown some results and compared them with analytical results. Moreover, I added code coverage using gcov, output file formatting using Hierarchical Data Formatting (HDF5), Portable Extensible Toolkit for Scientific Computation (PETSc) library with GMRES solver integration and finally performed the continuous integration using Travis.


<p align="center">
<img src="./Cover_photos/Cover0.jpeg" height="370">
</p>
Figure : The enclosed Pressure and Saturation contour plots correspond to the simulation of the Nechelik reservoir (80 X 75 cells) with 6 wells (2 horizontal, 4 vertical) for 1000 days with a time step of 0.1 days. After 500 days, water is being injected into two wells on the bottom left for secondary recovery.


### Quick Usage
Refer to the solution PDFs find description of the bash scripts or C++ codes.


## Acknowledgement
I would like to acknowledge Professor Karl Schulz for teaching the course in 2020.
