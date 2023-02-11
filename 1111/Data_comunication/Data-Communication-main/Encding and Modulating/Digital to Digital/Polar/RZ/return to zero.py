import numpy as np
from matplotlib import pyplot as plt

data = np.random.randint(0,2,10)
time = np.linspace(0,len(data),len(data)*2)
signal = np.zeros(2*len(data), dtype = int)

for i in range(0,2*len(data),2):
    if data[i//2] == 1:
       signal[i] = 1
    else:
        signal[i] = -1
    signal[i+1] = 0
    

plt.step(time, signal,where='post')
plt.title('RZ')
plt.xlabel('Amplitude')
plt.ylabel('Time')
plt.text(0, 2, data)

# plt.text(3, 8)
plt.grid(True)
plt.yticks([-2,-1,0,1,2,3])
plt.xticks(np.arange(len(data)))
plt.show()
