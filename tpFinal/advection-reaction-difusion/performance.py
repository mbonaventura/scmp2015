#!/usr/bin/python

import numpy as np
import math

import matplotlib
# matplotlib.use("Agg") # to save animation as video
import matplotlib.pyplot as plt
import matplotlib.animation as animation

import glob, os
import sys
import re

def plot(data):
	N, perf, title = data

	fig, ax = plt.subplots()
	fig.suptitle(title, fontsize=20)
	plt.xlabel("Tamano de la grilla (N)", fontsize=16)
	plt.ylabel("Tiempo de ejecucion (seg)", fontsize=16)
	ax.grid()


	# log x and y axis
	
	for algorithm in perf:
		y_data = np.array(perf[algorithm]).astype(np.double)
		N_data = np.array(N).astype(np.double)
		mask = np.isfinite(y_data) # avoid discontinuous lines in the presence of NaN
		ax.loglog(N_data[mask], y_data[mask], label=algorithm, linestyle='-', marker='*',)
	
	ax.legend(loc="upper left")

	# in case 2:
	plt.ylim(0, pow(10,4))

	plt.show()
	


# simulation times for the case of d=0.0001 r=1000
def perf_case1():
	title = "Caso1: d=1e-4; r=1000"
	N =          [100	, 200	, 500	, 1000	,2000	,5000	,10000]
	perf = {
		"QSS3":  [0.133 ,0.155	,29.2	,118	,135.482,np.NaN	,1240.365],
		"LIQSS": [0.016, None	,0.073	,0.15	,0.313	,0.787	,1.666],
		"LIQSS2":[0.006, np.NaN	, 0.021	,0.037	,0.11	,0.943	,30.431],
		"LIQSS3":[0.014, np.NaN	, 0.117	,0.896	,6.411	,37.57	,327.302],
		"DASSL": [0.072, 0.102	,2.317	,14.368	,15.313	,104.421,290.367],
		"DOPRI": [0.066, np.NaN, 0.338	,0.736	,1.489	,5.115	,16.373],		
	}

	return (N, perf, title)

# simulation times for the case2 of d=0.5 r=0.1
def perf_case2():
	title = "Caso2: d=0.5; r=0.1"
	N =          [100	, 200	, 500	, 1000	,2000		,5000	,10000]
	perf = {
		"QSS3":  [0.279	,2.077	,32.442	,259.768,2140.076	,np.NaN	, np.NaN],
		"LIQSS": [0.01	,0.03	,0.293	,2.978	,25.097		,456.884, 4248.34],
		"LIQSS2":[0.027	,0.214	,3.327	,29.364	,250.594	,4300	, np.NaN],
		"LIQSS3":[0.2	,1.586	,22.83	,208.992,1688.529	,26545.789, np.NaN],
		"DASSL": [0.005	,0.015	,0.098	,0.52	,1.666		,12.03	, 53.443],
		"DOPRI": [0.007	,0.042	,0.621	,5.025	,39.001		,427.02	, 995.482],				
	}

	return (N, perf, title)


if __name__ == '__main__':
    # plot(perf_case1())
    plot(perf_case2())

