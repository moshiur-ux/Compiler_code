import numpy as np
import matplotlib.pyplot as plt

A_c = 3 #float(input('Enter carrier amplitude: '))
f_c = 5 #float(input('Enter carrier frquency: '))
A_m = 2 #float(input('Enter message amplitude: '))
f_m = 2 #float(input('Enter message frquency: '))


t = np.linspace(0, 1, 1000)

carrier = A_c*np.cos(2*np.pi*f_c*t)
modulator = A_m*np.cos(2*np.pi*f_m*t)
product = A_c*(1+np.cos(2*np.pi*f_m*t))*np.cos(2*np.pi*f_c*t)

plt.subplot(3,1,1)
plt.title('Amplitude Modulation')
plt.plot(modulator)
plt.ylabel('Amplitude')
plt.xlabel('Message signal')

plt.subplot(3,1,2)
plt.plot(carrier)
plt.ylabel('Amplitude')
plt.xlabel('Carrier signal')

plt.subplot(3,1,3)
plt.plot(product)
plt.ylabel('Amplitude')
plt.xlabel('AM signal')

plt.subplots_adjust(hspace=1)
plt.show()
