import numpy as np
from matplotlib import pyplot as plt

data = np.random.randint(0,2,10)
time_org = np.arange(len(data))
signal = np.zeros(len(data)*2, dtype = int)

for i in range(0,len(data)*2,2):
    if data[i//2] == 0:
        signal[i] = 1
        signal[i+1] = -1
    else:
        signal[i] = -1
        signal[i+1] = 1


print(signal)
time = np.arange(len(signal))
plt.step(time, signal,where='post')
plt.title('Manchestor')
plt.xlabel('Amplitude')
plt.ylabel('Time')
plt.text(0, 2, data)

plt.grid(True)
plt.yticks([-2,-1,0,1,2,3])
plt.xticks(time_org*2,time_org)
plt.show()
