def get_x_y_steps(x, y, where="post"):
    if where == "post":
        x_step = [x[0]] + [_x for tup in (x, x)[1:] for _x in tup]
        y_step = [_y for tup in (y, y)[:-1] for _y in tup] + [y[-1]]
    elif where == "pre":
        x_step = [_x for tup in (x, x)[:-1] for _x in tup] + [x[-1]]
        y_step = [y[0]] + [_y for tup in (y, y)[1:] for _y in tup]
    return x_step, y_step

import numpy as np
from matplotlib import pyplot as plt

data = np.random.randint(0,2,25)
data = [0,1,0,0,1,1,1,0]
time = np.arange(len(data))
signal = np.zeros(len(data), dtype = int)

for i in range(len(data)):
    if data[i] == 0:
        signal[i] = 1
    else:
        signal[i] = -1
    
x,y=get_x_y_steps(time, signal)
plt.step(x,y)
plt.title('Unipolar')
plt.xlabel('Amplitude')
plt.ylabel('Time')
plt.text(0, 2, data)

# plt.text(3, 8)
plt.grid(True)
plt.yticks([-2,-1,0,1,2,3])
plt.xticks(time)
plt.show()
