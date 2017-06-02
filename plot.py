
import numpy as np
import matplotlib.pyplot as plt

with open("data.txt") as f:
    data = f.read()

data = data.split('\n')

theta = [row.split(' ')[0] for row in data]
x = [row.split(' ')[0] for row in data]
y = [row.split(' ')[1] for row in data]

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("ROC Space")
ax1.set_xlabel('False positive rate')
ax1.set_ylabel('True positive rate')

ax1.plot(x,y, c='r')

leg = ax1.legend()

fig.savefig('roc.pdf')
plt.show()