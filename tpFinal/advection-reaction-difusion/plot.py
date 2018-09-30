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

class TimeSerie:
	def __init__(self):
	    self.times = list()		
	    self.values = list()
	
	def add(self, time, value):
	    self.times.append(time)
	    self.values.append(value)
	    
	def total_time(self):
	    return self.times[-1]
	        	    
	def value_at(self, time):
	    if len(self.values) == 0:
	        return None
	    if len(self.values) == 1 and self.times[0] <= time:
	        return self.values[0]
	    if self.times[-1] <= time:
	        return self.values[-1]
	        
	    for idx in range(0, len(self.times)):
	        if self.times[idx] == time:
	            return self.values[idx]
	    
	        if self.times[idx] > time:
	            return self.values[idx-1]
	            
	    return None
	    
	@staticmethod
	def fromDatFile(datFile):
	    ts = TimeSerie()
	    ts.file = datFile
	    
	    with open(datFile) as f:
	        for line in f:
	            time, value = line.split()
	            ts.add(float(time), float(value))	        
	    
	    return ts
	    
def load(path):
    dat_files = glob.glob(r'%s/u*.dat' % (path))
    print "Found %d result files in %s" % (len(dat_files), path) 
    data = np.empty(len(dat_files), dtype=object)
    for f in dat_files:
        index = re.findall(r'\[([^]]*)\]', f)
        index = int(index[0])-1 # zero-based in python, solver is 1-based
        
        ts = TimeSerie.fromDatFile(f)
        data[index] = ts
       # print "%s [%d]has %d times and %d values" % (ts.file, index, len(ts.times), len(ts.values))
    
    return data

class plotter:
    def __init__(self, data):
        self.data = data
        self.bar_plot = None
        self.interval = 100.0 #ms
        self.final_time = max([ts.total_time() for ts in data]) # in s
        self.total_frames = int(math.ceil(self.final_time * 1000 / self.interval))
        
        print "totFrame: %d" % self.total_frames
        print "final t: %f" % self.final_time

    def valuesForTime(self, time):
        x = np.empty(len(self.data), dtype=float)
        
        for idx, ts in enumerate(self.data):
            x[idx] = ts.value_at(time) 
            
        return x

    def animate(self, frame):
        time = (frame * self.interval) / 1000.0 # in s
        print "plotting frame #%d for time %f" % (frame, time)
        
        self.ax.set_title("\nt=%f" % time, size=16)
        y = self.valuesForTime(time)
        # update each bar
        for i, b in enumerate(self.bar_plot):
            b.set_height(y[i])


    def plot(self):
	    #fig, self.ax = plt.subplots(figsize=(40,15))
		fig, self.ax = plt.subplots()
		fig.suptitle("Adveccion-Difusion-Reaccion model\n", fontsize=20)
			
		rng = range(0, len(self.data))
		
		# first plot for t=0
		t=0
		self.bar_plot = plt.bar(rng, self.valuesForTime(t), linewidth = 0, align='edge', width=1)
		
		plt.xlim(rng[0], rng[-1])
		plt.ylim(-0.1, 1.1)
		self.ax.set_title("\nt=%f"%t, size=16)	    
		plt.xlabel("variable espacial: x", fontsize=16)
		plt.ylabel("estado: u(x, t)", fontsize=16)

	    # self.animate(80)
	    #plt.show()

		print "starting animation"
		anim = animation.FuncAnimation(fig, self.animate,repeat=False,blit=False, frames=self.total_frames, interval=self.interval)
		
		# Set up formatting for the movie files
		# Writer = animation.writers['avconv']
		# writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)
		# anim.save('adr.mp4', writer=writer)
		
		plt.show()

if __name__ == '__main__':
    resultsPath = sys.argv[1]
    data = load(resultsPath)
    plotter(data).plot()

