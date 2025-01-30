import matplotlib.pyplot as plt
import math
f = open("python_file.txt1", "r")
n = int(f.readline())
ans_x = [0] * n
i = 0
for elem in f:
    ans_x[i] = elem
    i += 1
mass_x = [0] * 51
mass_y2 = [0] * 51
mass_y = [0] * 51
for i in range(0, 51):
    x = i/10
    mass_x[i] = x
    mass_y2[i] = 0
    mass_y[i] = x + x / 2 * math.sin(4 * x)
    for l in range(0, 11) :
        mass_y2[i] += float(ans_x[l]) * x**l
plt.title("Графики:")
plt.xlabel("x")
plt.ylabel("y")
plt.plot(mass_x, mass_y2, label="график 2")
plt.plot(mass_x, mass_y, label="график 1")

plt.legend()
plt.show()
f.close()