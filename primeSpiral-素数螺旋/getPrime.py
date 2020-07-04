import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

plt.figure(dpi=80)
#447^2 = 200,000
#w = 447

#173^2 = 30000
#w = 173

w = 1000
primes = np.array([n for n in range(2, w**2+1) if all(
    n%m != 0 for m in range(2, int(np.sqrt(n))+1))])


print(primes)

ax1 = plt.subplot(111, projection='polar')
ax1.set_ylim(0, w**2)
new_ticks = np.linspace(0, w**2, 50)
plt.yticks(new_ticks)
#plt.rcParams['figure.dpi']=200000
plt.rcParams['figure.dpi']=1000000
plt.scatter(primes, primes, marker='.', cmap=cm.binary)
#plt.rcParams['figure.figsize'] = (8.0, 4.0)
plt.axis('off')
plt.show()
