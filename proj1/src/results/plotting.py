"""
CSE 380 Tools and Techniques Project 1
Plotting for Problem 3
Author: Mohammad Afzal Shadab
Email: mashadab@utexas.edu
Date modified: 10/14/2020
"""

#Importing required libraries
from IPython import get_ipython
get_ipython().magic('reset -sf')#for clearing everything
get_ipython().run_line_magic('matplotlib', 'qt') #for plotting in separate window
# Import curve fitting package from scipy
from scipy.optimize import curve_fit
import pandas as pd

from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np


import numpy as np              #import numpy library
import matplotlib.pyplot as plt #library for plotting
plt.rcParams.update({'font.size': 22})

# Function to calculate the power-law with constants a and b
def power_law(x, a, b):
    return a*np.power(x, b)

################################
# VERIFICATION TESTING
################################

# GAUSS-SEIDEL
    
#1 Dimension
    
Gauss_dim1_order2 = np.loadtxt("output_Gauss-Seidel_dim1_order2.dat",skiprows=1)
Gauss_dim1_order4 = np.loadtxt("output_Gauss-Seidel_dim1_order4.dat",skiprows=1)

Gauss_dim1_order2_fit, cov = curve_fit(f=power_law, xdata=Gauss_dim1_order2[0:8,0], ydata=Gauss_dim1_order2[0:8,1], bounds=(-np.inf, np.inf))
Gauss_dim1_order2_x = np.logspace(np.log10(Gauss_dim1_order2[0,0]), np.log10(Gauss_dim1_order2[6,0]),10000)

Gauss_dim1_order4_fit, cov = curve_fit(f=power_law, xdata=Gauss_dim1_order4[3:8,0], ydata=Gauss_dim1_order4[3:8,1], bounds=(-np.inf, np.inf))
Gauss_dim1_order4_x = np.logspace(np.log10(Gauss_dim1_order4[0,0]), np.log10(Gauss_dim1_order4[6,0]),10000)

#ABSOLUTE ERRORS===========================================================
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Gauss_dim1_order2[:,0],Gauss_dim1_order2[:,1],'ro',label=r'Gauss-Seidel $2^{nd}$')
plot = plt.loglog(Gauss_dim1_order4[:,0],Gauss_dim1_order4[:,1],'bX',label=r'Gauss-Seidel $4^{th}$')
plot = plt.loglog(Gauss_dim1_order2_x,power_law(Gauss_dim1_order2_x, *Gauss_dim1_order2_fit),'r--',label=r'Fit: $O( N^{%5.4f})$' %Gauss_dim1_order2_fit[1] )
plot = plt.loglog(Gauss_dim1_order4_x,power_law(Gauss_dim1_order4_x, *Gauss_dim1_order4_fit),'b--',label=r'Fit: $O( N^{%5.4f})$' %Gauss_dim1_order4_fit[1] )

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'$||T-T_{exact}||_2/||T_{exact}||_2$')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
#plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'convergence_study_GS_1D.png',bbox_inches='tight', dpi = 600)


#2 Dimension
Gauss_dim2_order2 = np.loadtxt("output_Gauss-Seidel_dim2_order2.dat",skiprows=1)
Gauss_dim2_order4 = np.loadtxt("output_Gauss-Seidel_dim2_order4.dat",skiprows=1)

Gauss_dim2_order2_fit, cov = curve_fit(f=power_law, xdata=Gauss_dim2_order2[1:5,0], ydata=Gauss_dim2_order2[1:5,1], bounds=(-np.inf, np.inf))
Gauss_dim2_order2_x = np.logspace(np.log10(Gauss_dim2_order2[0,0]), np.log10(Gauss_dim2_order2[4,0]),10000)

Gauss_dim2_order4_fit, cov = curve_fit(f=power_law, xdata=Gauss_dim2_order4[1:5,0], ydata=Gauss_dim2_order4[1:5,1], bounds=(-np.inf, np.inf))
Gauss_dim2_order4_x = np.logspace(np.log10(Gauss_dim2_order4[0,0]), np.log10(Gauss_dim2_order4[4,0]),10000)

#ABSOLUTE ERRORS===========================================================
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Gauss_dim2_order2[:,0],Gauss_dim2_order2[:,1],'ro',label=r'Gauss-Seidel $2^{nd}$')
plot = plt.loglog(Gauss_dim2_order4[:,0],Gauss_dim2_order4[:,1],'bX',label=r'Gauss-Seidel $4^{th}$')
plot = plt.loglog(Gauss_dim2_order2_x,power_law(Gauss_dim2_order2_x, *Gauss_dim2_order2_fit),'r--',label=r'Fit: $O( N^{%5.4f})$' %Gauss_dim2_order2_fit[1] )
plot = plt.loglog(Gauss_dim2_order4_x,power_law(Gauss_dim2_order4_x, *Gauss_dim2_order4_fit),'b--',label=r'Fit: $O( N^{%5.4f})$' %Gauss_dim2_order4_fit[1] )

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'$||T-T_{exact}||_2/||T_{exact}||_2$')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'convergence_study_GS_2D.png',bbox_inches='tight', dpi = 600)

# JACOBI
#1 Dimension
Jacobi_dim1_order2 = np.loadtxt("output_Jacobi_dim1_order2.dat",skiprows=1)


Jacobi_dim1_order2_fit, cov = curve_fit(f=power_law, xdata=Jacobi_dim1_order2[0:8,0], ydata=Jacobi_dim1_order2[0:8,1], bounds=(-np.inf, np.inf))
Jacobi_dim1_order2_x = np.logspace(np.log10(Jacobi_dim1_order2[0,0]), np.log10(Jacobi_dim1_order2[6,0]),10000)

#ABSOLUTE ERRORS===========================================================
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Jacobi_dim1_order2[:,0],Jacobi_dim1_order2[:,1],'ro',label=r'Jacobi $2^{nd}$')

plot = plt.loglog(Jacobi_dim1_order2_x,power_law(Jacobi_dim1_order2_x, *Jacobi_dim1_order2_fit),'r--',label=r'Fit: $O( N^{%5.4f})$' %Jacobi_dim1_order2_fit[1] )

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'$||T-T_{exact}||_2/||T_{exact}||_2$')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'convergence_study_Jacobi_1D.png',bbox_inches='tight', dpi = 600)

#2 Dimension
Jacobi_dim2_order2 = np.loadtxt("output_Jacobi_dim2_order2.dat",skiprows=1)


Jacobi_dim2_order2_fit, cov = curve_fit(f=power_law, xdata=Jacobi_dim2_order2[0:5,0], ydata=Jacobi_dim2_order2[0:5,1], bounds=(-np.inf, np.inf))
Jacobi_dim2_order2_x = np.logspace(np.log10(Jacobi_dim2_order2[0,0]), np.log10(Jacobi_dim2_order2[4,0]),10000)

#ABSOLUTE ERRORS===========================================================
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Jacobi_dim2_order2[:,0],Jacobi_dim2_order2[:,1],'ro',label=r'Jacobi $2^{nd}$')

plot = plt.loglog(Jacobi_dim2_order2_x,power_law(Jacobi_dim2_order2_x, *Jacobi_dim2_order2_fit),'r--',label=r'Fit: $O( N^{%5.4f})$' %Jacobi_dim2_order2_fit[1] )

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'$||T-T_{exact}||_2/||T_{exact}||_2$')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'convergence_study_Jacobi_2D.png',bbox_inches='tight', dpi = 600)


################################
# PERFORMANCE TIMINGS
################################

# GAUSS-SEIDEL ======================================
    
#1 Dimension
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Gauss_dim1_order2[:,0],Gauss_dim1_order2[:,2],'ro--',label=r'Gauss-Seidel $2^{nd}$')
plot = plt.loglog(Gauss_dim1_order4[:,0],Gauss_dim1_order4[:,2],'bX--',label=r'Gauss-Seidel $4^{th}$')

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'Runtime [s]')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'runtime_GS_1D.png',bbox_inches='tight', dpi = 600)

#2 Dimension
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Gauss_dim2_order2[:,0],Gauss_dim2_order2[:,2],'ro--',label=r'Gauss-Seidel $2^{nd}$')
plot = plt.loglog(Gauss_dim2_order4[:,0],Gauss_dim2_order4[:,2],'bX--',label=r'Gauss-Seidel $4^{th}$')

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'Runtime [s]')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'runtime_GS_2D.png',bbox_inches='tight', dpi = 600)


# JACOBI =============================================
#1 Dimension
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Jacobi_dim1_order2[:,0],Jacobi_dim1_order2[:,2],'ro--',label=r'Jacobi $2^{nd}$')
manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'Runtime [s]')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'runtime_Jacobi_1D.png',bbox_inches='tight', dpi = 600)

#2 Dimension
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(Jacobi_dim2_order2[:,0],Jacobi_dim2_order2[:,2],'ro--',label=r'Jacobi $2^{nd}$')

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'Runtime [s]')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'runtime_Jacobi_2D.png',bbox_inches='tight', dpi = 600)


################################
# RESULTS
################################
# GAUSS-SEIDEL ======================================
Gauss_dim1_order2_plot = np.loadtxt("ref_sol_Gauss-Seidel_dim1_order2_n100.dat",skiprows=1)
  
#1 Dimension
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.plot(Gauss_dim1_order2_plot[:,0],Gauss_dim1_order2_plot[:,2],'ro',label=r'Gauss-Seidel $2^{nd}$')
plot = plt.plot(Gauss_dim1_order2_plot[:,0],Gauss_dim1_order2_plot[:,1],'k-',label=r'Analytical')

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'T [C]')
plt.xlabel(r'$x [m]$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'plot_GS_1D_order2_n100.png',bbox_inches='tight', dpi = 600)


#2 Dimension
#Second order
Gauss_dim2_order2_plot = np.loadtxt("ref_sol_Gauss-Seidel_dim2_order2_n75.dat",skiprows=1)

X = np.reshape(Gauss_dim2_order2_plot[:,0], (75, 75))
Y = np.reshape(Gauss_dim2_order2_plot[:,1], (75, 75))
T = np.reshape(Gauss_dim2_order2_plot[:,3], (75, 75))

fig = plt.figure(figsize=(15,7.5) , dpi=100)
ax = fig.gca(projection='3d')
plot = ax.plot_surface(X,Y,T, cmap=cm.coolwarm, linewidth=0, antialiased=False)


manager = plt.get_current_fig_manager()
manager.window.showMaximized()
ax.set_xlabel('x [m]')
ax.set_ylabel('y [m]')
ax.set_zlabel('T [C]')
#legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'plot_GS_2D_order2_n75.png',bbox_inches='tight', dpi = 600)

#Fourth order
Gauss_dim2_order4_plot = np.loadtxt("ref_sol_Gauss-Seidel_dim2_order4_n75.dat",skiprows=1)

X = np.reshape(Gauss_dim2_order4_plot[:,0], (75, 75))
Y = np.reshape(Gauss_dim2_order4_plot[:,1], (75, 75))
T = np.reshape(Gauss_dim2_order4_plot[:,3], (75, 75))

fig = plt.figure(figsize=(15,7.5) , dpi=100)
ax = fig.gca(projection='3d')
plot = ax.plot_surface(X,Y,T, cmap=cm.coolwarm, linewidth=0, antialiased=False)


manager = plt.get_current_fig_manager()
manager.window.showMaximized()
ax.set_xlabel('x [m]')
ax.set_ylabel('y [m]')
ax.set_zlabel('T [C]')
#legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'plot_GS_2D_order4_n75.png',bbox_inches='tight', dpi = 600)

# JACOBI =============================================
#1 Dimension
Jacobi_dim1_order2_plot = np.loadtxt("ref_sol_Jacobi_dim1_order2_n100.dat",skiprows=1)

ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.plot(Jacobi_dim1_order2_plot[:,0],Jacobi_dim1_order2_plot[:,2],'ro',label=r'Jacobi $2^{nd}$')
plot = plt.plot(Jacobi_dim1_order2_plot[:,0],Jacobi_dim1_order2_plot[:,1],'k-',label=r'Analytical')

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'T [C]')
plt.xlabel(r'$x [m]$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'plot_Jacobi_1D_order2_n100.png',bbox_inches='tight', dpi = 600)


#2 Dimension
#Second order
Jacobi_dim2_order2_plot = np.loadtxt("ref_sol_Jacobi_dim2_order2_n75.dat",skiprows=1)

X = np.reshape(Jacobi_dim2_order2_plot[:,0], (75, 75))
Y = np.reshape(Jacobi_dim2_order2_plot[:,1], (75, 75))
T = np.reshape(Jacobi_dim2_order2_plot[:,3], (75, 75))

fig = plt.figure(figsize=(15,7.5) , dpi=100)
ax = fig.gca(projection='3d')
plot = ax.plot_surface(X,Y,T, cmap=cm.coolwarm, linewidth=0, antialiased=False)

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
ax.set_xlabel('x [m]')
ax.set_ylabel('y [m]')
ax.set_zlabel('T [C]')
#legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'plot_Jacobi_2D_order2_n75.png',bbox_inches='tight', dpi = 600)


#Analytical ====================================
Jacobi_dim2_order2_plot = np.loadtxt("ref_sol_Jacobi_dim2_order2_n75.dat",skiprows=1)

X = np.reshape(Jacobi_dim2_order2_plot[:,0], (75, 75))
Y = np.reshape(Jacobi_dim2_order2_plot[:,1], (75, 75))
T = np.reshape(Jacobi_dim2_order2_plot[:,2], (75, 75))

fig = plt.figure(figsize=(15,7.5) , dpi=100)
ax = fig.gca(projection='3d')
plot = ax.plot_surface(X,Y,T, cmap=cm.coolwarm, linewidth=0, antialiased=False)

manager = plt.get_current_fig_manager()
manager.window.showMaximized()
ax.set_xlabel('x [m]')
ax.set_ylabel('y [m]')
ax.set_zlabel('T [C]')
#legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'plot_Jacobi_2D_order2_n75_Analytical.png',bbox_inches='tight', dpi = 600)

#2D plot ====================================
Jacobi_dim2_order2_plot = np.loadtxt("ref_sol_Jacobi_dim2_order2_n75.dat",skiprows=1)

X = np.reshape(Jacobi_dim2_order2_plot[:,0], (75, 75))
Y = np.reshape(Jacobi_dim2_order2_plot[:,1], (75, 75))
T = np.reshape(Jacobi_dim2_order2_plot[:,2], (75, 75))

fig = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.contourf(X,Y,T, cmap=cm.coolwarm, linewidth=0, antialiased=False)
plt.axis('equal')
plt.xlim([0,1])
plt.ylim([0,1])
clb = plt.colorbar()
plt.xlabel('x [m]')
plt.ylabel('y [m]')
clb.set_label('Temperature [C]')
plt.savefig(f'2D_plot.png',bbox_inches='tight', dpi = 600)
'''
manager = plt.get_current_fig_manager()
manager.window.showMaximized()

#ax.set_zlabel('T [C]')
#legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)

'''



