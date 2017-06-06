
import numpy as np
import matplotlib.pyplot as plt

data = open("result/strongclassifier", "r") 

data = data.split('\n')

alpha = [row.split(' ')[0] for row in data]
x = xrange(1, len(alpha))

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Alpha")
ax1.set_xlabel('round')
ax1.set_ylabel('alpha')

ax1.plot(x,alpha, c='r')

leg = ax1.legend()

fig.savefig('result/alpha.png',dpi=300)
plt.show()
