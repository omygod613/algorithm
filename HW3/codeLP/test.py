from math import sin, cos, pi

import matplotlib.pyplot as plt
import numpy as np
from pulp import *

# Exercise 1
inputs = np.array([(1, 3), (2, 5), (3, 7), (5, 11), (7, 14), (8, 15), (10, 19)])

# s1 = LpVariable("s1")
# s2 = LpVariable("s2")
# s3 = LpVariable("s3")
# s4 = LpVariable("s4")
# s5 = LpVariable("s5")
# s6 = LpVariable("s6")
# s7 = LpVariable("s7")
# s = [s1, s2, s3, s4, s5, s6, s7]

s = [LpVariable("s"+str(i)) for i in range(1, 7)]


a = LpVariable("a")
b = LpVariable("b")

prop = LpProblem("problem1", LpMinimize)

# prop += s1 + s2 + s3 + s4 + s5 + s6 + s7  # Objective
prop += sum(s)

for p, s_i in zip(inputs, s):  # add constraints
    x, y = p
    prop += a * x + b - y <= s_i
    prop += -a * x - b + y <= s_i

status = prop.solve()

print LpStatus[status]

a = a.varValue
b = b.varValue

print a
print b

# points for draw line
x1 = inputs[0, 0]
y1 = a * x1 + b

x2 = inputs[-1, 0]
y2 = a * x2 + b

plt.figure(1)
plt.scatter(inputs[:, 0], inputs[:, 1])
plt.plot([x1, x2], [y1, y2], 'k-')

plt.savefig('ex1_2.png')