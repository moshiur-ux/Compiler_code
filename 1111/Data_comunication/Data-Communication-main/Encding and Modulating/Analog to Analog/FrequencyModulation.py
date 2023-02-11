import numpy as np
import matplotlib.pyplot as plt

modulator_frequency = 4
carrier_frequency = 40
modulation_index = 1

time = np.linspace(0,1,1000)
modulator = np.sin(2 * np.pi * modulator_frequency * time) * modulation_index
carrier = np.sin(2 * np.pi * carrier_frequency * time)
product = np.zeros_like(modulator)

for i, t in enumerate(time):
    product[i] = np.sin(2 * np.pi * (carrier_frequency * t + modulator[i]))

plt.subplot(3, 1, 1)
plt.title('Frequency Modulation')
plt.plot(time,modulator)
plt.ylabel('Amplitude')
plt.xlabel('Modulator signal')
plt.subplot(3, 1, 2)
plt.plot(time,carrier)
plt.ylabel('Amplitude')
plt.xlabel('Carrier signal')
plt.subplot(3, 1, 3)
plt.plot(time,product)
plt.ylabel('Amplitude')
plt.xlabel('Output signal')
plt.tight_layout()
plt.show()