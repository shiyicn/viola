
import numpy as np
import matplotlib.pyplot as plt

#open files
with open("result/strongclassifier.txt") as f:
    data = f.read()

data = data.split('\n')

alpha = [row.split(' ')[0] for row in data]
x = xrange(1, len(alpha)+1)

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("L'evolution de l'alpha")
ax1.set_xlabel('Tour')
ax1.set_ylabel('Alpha')

ax1.plot(x,alpha, c='r')

leg = ax1.legend()

fig.savefig('result/alpha.png',dpi=300)
plt.show()
