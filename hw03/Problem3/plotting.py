"""
CSE 380 Tools and Techniques Assignment 3
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

import numpy as np              #import numpy library
import matplotlib.pyplot as plt #library for plotting
plt.rcParams.update({'font.size': 22})

# Function to calculate the power-law with constants a and b
def power_law(x, a, b):
    return a*np.power(x, b)

simp = np.loadtxt("tempsimpson.log")
trap = np.loadtxt("temptrap.log")

simp_fit, cov = curve_fit(f=power_law, xdata=simp[0:6,0], ydata=simp[0:6,2], bounds=(-np.inf, np.inf))
simp_x = np.logspace(np.log10(simp[0,0]), np.log10(simp[5,0]),10000)

trap_fit, cov = curve_fit(f=power_law, xdata=trap[0:5,0], ydata=trap[0:5,2], bounds=(-np.inf, np.inf))
trap_x = np.logspace(np.log10(trap[0,0]), np.log10(trap[5,0]),10000)

#ABSOLUTE ERRORS===========================================================
ax = plt.figure(figsize=(15,7.5) , dpi=100)
plot = plt.loglog(simp[:,0],simp[:,2],'ro',label=r'$Simpson$')
plot = plt.loglog(trap[:,0],trap[:,2],'bX',label=r'$Trapezoidal$')
plot = plt.loglog(simp_x,power_law(simp_x, *simp_fit),'r--',label=r'$Fit: O( N^{%5.4f})$' %simp_fit[1] )
plot = plt.loglog(trap_x,power_law(trap_x, *trap_fit),'b--',label=r'$Fit: O( N^{%5.4f})$' %trap_fit[1] )
manager = plt.get_current_fig_manager()
manager.window.showMaximized()
plt.ylabel(r'$e_{rel}$')
plt.xlabel(r'$N$')
legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
plt.savefig(f'convergence_study.png',bbox_inches='tight', dpi = 600)