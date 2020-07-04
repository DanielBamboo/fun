import numpy as np
import matplotlib.pyplot as plt
 
plt.style.use('ggplot')
a, b = 2.0, 2.0
n = 20
theta = np.linspace(0, 2 * np.pi, num=2000)
plt.subplot(111, projection='polar')
y = a + b * theta
for i in range(n):
    x = theta + 2.0 * np.pi * i / n
    plt.plot(x, y)
plt.plot(theta, [a] * len(theta))
plt.show()
