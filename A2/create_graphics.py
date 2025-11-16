import pandas as pd
import matplotlib.pyplot as plt


random_std = pd.read_csv("random_array_standart_merge_sort.csv", sep=";")
random_hybrid = pd.read_csv("random_array_merge_and_insertion_sort.csv", sep=";")

plt.plot(random_std["size"], random_std["time"], label="Стандартный MERGE")
plt.plot(random_hybrid["size"], random_hybrid["time"], label="MERGE+INSERTION")
plt.xlabel("Размер массива")
plt.ylabel("Время, нс")
plt.title("Случайные массивы")
plt.grid(True)
plt.legend()
plt.savefig("random_arrays_compare.png", dpi=200)
plt.close()

rev_std = pd.read_csv("reversed_array_standart_merge_sort.csv", sep=";")
rev_hybrid = pd.read_csv("reversed_array_merge_and_insertion_sort.csv", sep=";")

plt.plot(rev_std["size"], rev_std["time"], label="Стандартный MERGE")
plt.plot(rev_hybrid["size"], rev_hybrid["time"], label="MERGE+INSERTION")
plt.xlabel("Размер массива")
plt.ylabel("Время, нс")
plt.title("Обратно отсортированные массивы")
plt.grid(True)
plt.legend()
plt.savefig("reversed_arrays_compare.png", dpi=200)
plt.close()

almost_std = pd.read_csv("almost_sorted_array_standart_merge_sort.csv", sep=";")
almost_hybrid = pd.read_csv("almost_sorted_array_merge_and_insertion_sort.csv", sep=";")

plt.plot(almost_std["size"], almost_std["time"], label="Стандартный MERGE")
plt.plot(almost_hybrid["size"], almost_hybrid["time"], label="MERGE+INSERTION")
plt.xlabel("Размер массива")
plt.ylabel("Время, нс")
plt.title("Почти отсортированные массивы")
plt.grid(True)
plt.legend()
plt.savefig("almost_sorted_arrays_compare.png", dpi=200)
plt.close()
