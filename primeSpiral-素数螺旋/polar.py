import matplotlib.pyplot as plt
import numpy as np

theta = np.arange(0, 2*np.pi, 0.06)
print(theta)
ax1 = plt.subplot(111, projection = 'polar')
#ax2 = plt.subplot(122)
ax1.plot(theta, theta/6, 'ro', lw=1.0)
#ax2.plot(theta, theta/6, 'ob', lw=2)
plt.show()
