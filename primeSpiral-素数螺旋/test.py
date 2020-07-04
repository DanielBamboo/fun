import numpy as np
import matplotlib.pyplot as plt

x = np.arange(-11, 11)
print(x)
y = 2*x + 5
plt.title("Matpltlib demo")
plt.xlabel("x axis caption")
plt.ylabel("y axis caption")
plt.plot(x, y, 'ob')
plt.show()
