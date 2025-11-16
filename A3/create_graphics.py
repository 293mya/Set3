import pandas as pd
import matplotlib.pyplot as plt


def make_plot(std_file, intro_file, title, output_name):
    std = pd.read_csv(std_file, sep=";")
    intro = pd.read_csv(intro_file, sep=";")

    plt.plot(std["size"], std["time"], label="quick_sort")
    plt.plot(intro["size"], intro["time"], label="intro_sort")
    plt.xlabel("Размер массива")
    plt.ylabel("Время, нс")
    plt.title(title)
    plt.grid(True)
    plt.legend()
    plt.savefig(output_name, dpi=200)
    plt.close()


def main():
    make_plot(
        std_file="random_array_std_sort.csv",
        intro_file="random_array_intro_sort.csv",
        title="Случайные массивы",
        output_name="random.png",
    )

    make_plot(
        std_file="reversed_array_std_sort.csv",
        intro_file="reversed_array_intro_sort.csv",
        title="Обратно отсортированные массивы",
        output_name="reversed.png",
    )

    make_plot(
        std_file="almost_sorted_array_std_sort.csv",
        intro_file="almost_sorted_array_intro_sort.csv",
        title="Почти отсортированные массивы",
        output_name="almost_sorted.png",
    )


if __name__ == "__main__":
    main()
