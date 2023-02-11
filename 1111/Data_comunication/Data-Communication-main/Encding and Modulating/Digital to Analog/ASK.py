import matplotlib.pylab as plt
import numpy as num

F1=10 
F2=2 

A=3
t=num.arange(0,1,0.001)
x=A*num.sin(2*num.pi*F1*t)
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
v=[]
for i in range(len(t)):
    v.append(A*num.sin(2*num.pi*F1*t[i])*u[i])
    
plt.subplot(3,1,1)
plt.plot(t,x)
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.title('Carrier')
plt.grid(True)

plt.subplot(3,1,2)
plt.plot(t,u)
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.title('Square wave Pulses')
plt.grid(True)

plt.subplot(3,1,3)
plt.plot(t,v)
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.title('ASK Signal')
plt.grid(True)
plt.tight_layout()
plt.show()

