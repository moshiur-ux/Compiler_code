import numpy as np
from matplotlib import pyplot as plt

data = np.random.randint(0,2,10)
time = np.arange(len(data))
signal = np.zeros(len(data), dtype = int)
for i in range(len(data)):
    if data[i] == 0:
        signal[i] = -1
    else:
        signal[i] = 1
    

plt.step(time, signal,where='post')
plt.title('NRZ-L')
plt.xlabel('Amplitude')
plt.ylabel('Time')
plt.text(0, 2, data)

# plt.text(3, 8)
plt.grid(True)
plt.yticks([-2,-1,0,1,2,3])
plt.xticks(time)
plt.show()
