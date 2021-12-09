"""
CSE 380 Tools and Techniques Project 2
Plotting the HDF5 files
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

import numpy as np              #import numpy library
import matplotlib.pyplot as plt #library for plotting
plt.rcParams.update({'font.size': 22})
import h5py

f = h5py.File('data.h5')

Tcomputed = f['T computed [C]'][:]    
Texact    = f['T exact [C]'][:]
x         = f['x [m]'][:]
dim       = f['Dimension'][0]
N         = f['N'][0]

if dim == 1:
    #1 Dimension
    ax = plt.figure(figsize=(15,7.5) , dpi=100)
    plot = plt.plot(x,Tcomputed,'ro',label=r'Computed')
    plot = plt.plot(x,Texact,'k-',label=r'Analytical')
    
    manager = plt.get_current_fig_manager()
    manager.window.showMaximized()
    plt.ylabel(r'T [C]')
    plt.xlabel(r'$x [m]$')
    legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
    plt.savefig(f'1D_n{N}.png',bbox_inches='tight', dpi = 600)

elif dim ==2: 
    y = f['y [m]'][:]
    
    #2 Dimension
    #Second order
    X = np.reshape(x, (N , N))
    Y = np.reshape(y, (N , N))
    Tcomp = np.reshape(Tcomputed, (N , N))
    
    fig = plt.figure(figsize=(15,7.5) , dpi=100)
    ax = fig.gca(projection='3d')
    plot = ax.plot_surface(X,Y,Tcomp, cmap=cm.coolwarm, linewidth=0, antialiased=False)
    
    manager = plt.get_current_fig_manager()
    manager.window.showMaximized()
    ax.set_xlabel('x [m]')
    ax.set_ylabel('y [m]')
    ax.set_zlabel('T [C]')
    #legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
    plt.tight_layout()
    plt.savefig(f'2D_n{N}_computed.png',bbox_inches='tight', dpi = 600)
    
    #Analytical ====================================
    Tanaly = np.reshape(Texact, (N, N))
    
    fig = plt.figure(figsize=(15,7.5) , dpi=100)
    ax = fig.gca(projection='3d')
    plot = ax.plot_surface(X,Y,Tanaly, cmap=cm.coolwarm, linewidth=0, antialiased=False)
    
    manager = plt.get_current_fig_manager()
    manager.window.showMaximized()
    ax.set_xlabel('x [m]')
    ax.set_ylabel('y [m]')
    ax.set_zlabel('T [C]')
    #legend = plt.legend(loc='best', shadow=False, fontsize='x-large')
    plt.tight_layout()
    plt.savefig(f'2D_n{N}_Analytical.png',bbox_inches='tight', dpi = 600)