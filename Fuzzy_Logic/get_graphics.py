def main():
    import matplotlib.pyplot as plt
    import numpy as np

    with open('avg1.list') as avg1_list:
	    avg1 = avg1_list.read()

    avg1 = avg1.split()
    avg1 = [float(item) for item in avg1]
    seconds = np.arange(5, avg1.__len__() * 10 + 5, 10)

    fig, ax = plt.subplots()
    plt.plot(seconds, avg1)
    ax.set_xlabel('время от начала дня (сек)')
    ax.set_ylabel('Load Average 1')
    plt.show()

    with open('ram.list') as ram_list:
        ram = ram_list.read()

    ram = ram.split()
    ram = [float(item) for item in ram]
    seconds = np.arange(5, ram.__len__() * 10 + 5, 10)

    fig, ax = plt.subplots()
    plt.plot(seconds, ram)
    ax.set_xlabel('время от начала дня (сек)')
    ax.set_ylabel('free RAM')
    plt.show()

if __name__ == "__main__":
    main()
