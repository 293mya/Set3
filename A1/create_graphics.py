import pandas as pd
import matplotlib.pyplot as plt
square_data = pd.read_csv("square.csv", sep=";")

square_n = square_data.iloc[:, 0]
square_values = square_data.iloc[:, 1]

plt.plot(square_n, square_values)
plt.xlabel("N (количество точек)")
plt.ylabel("Площадь пересечения")
plt.title("Оценка площади пересечения")
plt.grid(True)
plt.savefig("square_plot.png", dpi=200, bbox_inches="tight")
plt.close()


deviation_data = pd.read_csv("deviation.csv", sep=";")

dev_n = deviation_data.iloc[:, 0]
dev_values = deviation_data.iloc[:, 1]

plt.plot(dev_n, dev_values)
plt.xlabel("N (количество точек)")
plt.ylabel("Отклонение, %")
plt.title("Относительное отклонение от точной площади")
plt.grid(True)
plt.savefig("deviation_plot.png", dpi=200, bbox_inches="tight")
plt.close()
