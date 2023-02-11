import numpy as np
import matplotlib.pyplot as plt
carrier = 220.0
modulator = 490.0
beta = 1.0
x1 = np.linspace(0.0, 0.03, num=2000)
y1 = np.sin(carrier * np.pi * x1)
y2 = np.cos(modulator * np.pi * x1)
y3 = np.sin(carrier * np.pi * x1 + beta * y2)
plt.subplots_adjust(left = 0.1, bottom = 0.25)
plt.subplot(3, 1, 1)
carrierObj = plt.plot(x1, y1)
plt.title('Phase Modulation')
plt.ylabel('Amplitude')
plt.xlabel('Carrier')
plt.subplot(3, 1, 2)
modulatorObj, = plt.plot(x1, y2)
plt.ylabel('Amplitude')
plt.xlabel('Modulator')
plt.subplot(3, 1, 3)
modulatedObj, = plt.plot(x1, y3)
plt.ylabel('Amplitude')
plt.xlabel('Modulated Carrier')
plt.tight_layout()
plt.show()