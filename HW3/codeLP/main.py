from math import sin, cos, pi

import matplotlib.pyplot as plt
import numpy as np
from pulp import LpVariable, LpProblem, LpMinimize, LpStatus

# Exercise 1
inputs = np.array([(1, 3), (2, 5), (3, 7), (5, 11), (7, 14), (8, 15), (10, 19)])

t = LpVariable("t")
a = LpVariable("a")
b = LpVariable("b")

prop = LpProblem("problem1", LpMinimize)

prop += t  # Objective

for x, y in inputs:  # add constraints
    prop += a * x + b - y <= t
    prop += -a * x - b + y <= t

status = prop.solve()

print LpStatus[status]

a = a.varValue
b = b.varValue
t = t.varValue

print a
print b
print t

# points for draw line
x1 = inputs[0, 0]
y1 = a * x1 + b

x2 = inputs[-1, 0]
y2 = a * x2 + b

plt.figure(1)
plt.scatter(inputs[:, 0], inputs[:, 1])
plt.plot([x1, x2], [y1, y2], 'k-')

plt.savefig('ex1.png')


# Exercise 2
import csv

with open('Corvallis.csv') as csvfile:
    readCSV = csv.reader(csvfile, delimiter=';')

    Ts = []
    ds = []
    for i, row in enumerate(readCSV):
        if i == 0:
            continue
        Ts.append(float(row[7]))
        ds.append(int(row[8]))

t = LpVariable("t")
x0 = LpVariable("x0")
x1 = LpVariable("x1")
x2 = LpVariable("x2")
x3 = LpVariable("x3")
x4 = LpVariable("x4")
x5 = LpVariable("x5")

prop = LpProblem("problem2", LpMinimize)

prop += t  # Objective

for T, d in zip(Ts, ds):
    a = x0 + x1 * d + x2 * cos(2 * pi * d / 365.25) + x3 * sin(2 * pi * d / 365.25) \
            + x4 * cos(2 * pi * d / (365.25 * 10.7)) + x5 * sin(2 * pi * d / (365.25 * 10.7)) - T
    prop += a <= t
    prop += a >= -t

status = prop.solve()

print LpStatus[status]

t = t.varValue
x0 = x0.varValue
x1 = x1.varValue
x2 = x2.varValue
x3 = x3.varValue
x4 = x4.varValue
x5 = x5.varValue

print t, x0, x1, x2, x3, x4, x5


def calculate_T(d):
    return x0 + x1 * d + x2 * cos(2 * pi * d / 365.25) + x3 * sin(2 * pi * d / 365.25) \
    + x4 * cos(2 * pi * d / (365.25 * 10.7)) + x5 * sin(2 * pi * d / (365.25 * 10.7))

d0 = ds[0]
T0 = x0 + x1 * d

dn = ds[-1]
Tn = x0 + x1 * d

T1 = [calculate_T(d) for d in ds]

plt.figure(2)
plt.scatter(ds, Ts, linewidths=0.001, alpha=0.1)
plt.plot(ds, T1, 'r-')
plt.plot([d0, dn], [T0, Tn], 'k-')
plt.legend(['Best fit curve', 'Linear curve: x_0 + x_1*d'])

plt.savefig('ex2.png')

