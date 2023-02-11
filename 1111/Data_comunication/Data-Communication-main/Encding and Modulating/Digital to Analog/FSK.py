import matplotlib.pyplot as plt
import numpy as num
A=5
f1=33
f2=2
t=num.arange(0,1,0.001)
x=A*num.sin(2*num.pi*f1*t)
 
plt.subplot(3,1,1)
plt.plot(t,x)
plt.xlabel("time")
plt.ylabel("Amplitude")
plt.title("Carrier")
plt.grid(True)

u=[]
b=[0.2,0.4,0.6,0.8,1.0]
s=1
for i in t:
    if(i==b[0]):
        b.pop(0)
        if(s==0):
            s=1
        else:
            s=0
    u.append(s)

plt.subplot(3,1,2)
plt.plot(t,u)
plt.xlabel('time')
plt.ylabel('Amplitude')
plt.title('Message Signal')
plt.grid(True)

v=[]
for i in range(len(t)):
    if(u[i]==1):
        v.append(A*num.sin(2*num.pi*f1*t[i]))
    else:
        v.append(num.sin(2*num.pi*f1*t[i])*-1)

plt.subplot(3,1,3)
plt.plot(t,v)
plt.xlabel("t")
plt.ylabel("Amplitude")
plt.title("FSK")
plt.grid(True)
plt.tight_layout()
plt.show()
