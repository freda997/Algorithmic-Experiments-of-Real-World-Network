import numpy
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math
import scipy
import scipy.interpolate as ip
'''project 3 network plotting'''

def log_array(arr):
    return np.array([math.log(e, 10) for e in arr])

def get_regression_line_coefficients_linlog(x, y,d):
    return np.polyfit(log_array(x), y, d)

def get_regression_line_coefficients_loglog(x, y):  #linear
    return np.polyfit(log_array(x), log_array(y), 1)

# def linear_regression(x,y,name):
#     def plot_size_vs_times_log_log(x,y,name):
#         plt.subplot(2, 1, 1)
#         plt.loglog(x, y, 's', label=name)
#         plt.grid(which='both')
#         plt.legend()

#     def plot_regression_lines(x,y): 
#         plt.subplot(2, 1, 2)
#         m, b = get_regression_line_coefficients(x, y)
#         x = np.array(range(9))
#         plt.plot(x, m*x + b, label=f'y ~ {round(m, 2)}x + {round(b, 2)}')
#         plt.legend()
#         plt.grid(which='both')
#         plt.xticks(x)
#         plt.yticks(np.arange(5))

#     plot_size_vs_times_log_log(x,y,name)
#     plot_regression_lines(x,y)
#     plt.savefig(name+".png")
#     plt.show()
    
def lin_log(x,y,degree):
    def plot_original(x,y):
        plt.subplot(2,1,1)
        plt.plot(x, y, 's')
        #plt.plot(x, ry, label='log n reference',color='r')
        plt.xscale('log')
        plt.grid(which='both')
    def plot_regression_lines(x,y): 
        plt.subplot(2, 1, 2)
        
        m, b = get_regression_line_coefficients_linlog(x, y,degree)
        print("m,b= ",m,b)
        x1=np.array(range(7))
        plt.plot(x1, m*x1 + b, label=f'y ~ {round(m, 2)}x + {round(b, 2)}',color='b')
        plt.legend()
        plt.grid(which='both')
        plt.xticks(x1)
        plt.yticks(np.arange(0,1.5))
    plot_original(x,y)
    plot_regression_lines(x,y)
    plt.savefig("ClCoPlot.png")
    plt.show()
def plot_n_diameter():  
    
    timings = pd.read_csv("network.csv", sep=',')
    n = timings['n'].values
    diameter = timings['diameter'].values
    n = list(n)
    diameter = list(diameter)
    for c in range(len(n)):
        if diameter[0]==0.0:
            n.pop(0)
            diameter.pop(0)
        else:
            break
    print("Diameter plot: ")
    print(list(diameter))
    print(list(n))
    x = list(n)
    y = list(diameter)
    assert len(x)==len(y)
    lin_log(x,y,1)

def plot_n_cc():  
    timings = pd.read_csv("network.csv", sep=',')
    n = timings['n'].values
    cc = timings['cc'].values
    n = list(n)
    cc = list(cc)
    for c in range(len(n)):
        if cc[0]==0.0:
            n.pop(0)
            cc.pop(0)
        else:
            break
    print("cc plot: ")
    print(list(cc))
    print(list(n))
    x = list(n)
    y = list(cc)
    #plt.loglog(x, y, 's',basex=2,basey=2)
    assert len(x)==len(y)
    plt.axis([min(n),max(n),min(cc),max(cc)])
    lin_log(x,y,1)
    plt.close()

def removeZeroInY(x,y):
    startZeros=0;
    counting=True
    temp=0;
    for i in range(len(x)):
        if counting and y[i]==0:
            startZeros+=1
        elif y[i]==0:
            temp=i-1
            break
        else:
            counting=False
    x=x[:i+startZeros]
    y=y[:i+startZeros]
    return (x,y,)
            
def plot_degree_distribution_linlin(name):
    timings = pd.read_csv(name+".csv", sep=',')
    plt.title("Degree distribution (lin-lin)")
    plt.xlabel('degree')
    plt.ylabel('# of nodes with the degree')
    n = timings['n'].values
    cc = timings['nc'].values
    x = list(n)
    y = list(cc)

    x,y=removeZeroInY(x,y)
    print(y)
    
    plt.plot(x,y,'s')
    plt.grid(which='both')
    plt.savefig(name+"lin.png")
    plt.show()
    plt.close()

        
def plot_degree_distribution_loglog(name):
    timings = pd.read_csv(name+".csv", sep=',')
    plt.title("Degree distribution (log-log)")
    plt.xlabel('degree')
    plt.ylabel('# of nodes with the degree')
    n = timings['n'].values
    cc = timings['nc'].values
    x = list(n)
    y = list(cc)
    x,y=removeZeroInY(x,y)
    #removeZeroInY(x,y)
    plt.loglog(x,y,'s')
    plt.grid(which='both')
    plt.savefig(name+"log.png")
    plt.show()
    plt.close()
plot_degree_distribution_linlin("degDis100000")
plot_degree_distribution_loglog("degDis100000")
#plot_n_diameter()
#plot_n_cc()