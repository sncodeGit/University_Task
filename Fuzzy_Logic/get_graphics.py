def main():
    import matplotlib.pyplot as plt
    import numpy as np

    with open('requests_per_seconds.list') as requests_list:
	    requests = requests_list.read()

    requests = requests.split()
    requests = [int(item) for item in requests]
    seconds = np.arange(requests.__len__())

    plt.plot(seconds, requests)
    plt.show()

    with open('avg1.list') as avg1_list:
	    avg1 = avg1_list.read()

    avg1 = avg1.split()
    avg1 = [float(item) for item in avg1]
    seconds = np.arange(5, avg1.__len__() * 10 + 5, 10)

    plt.plot(seconds, avg1)
    plt.show()

if __name__ == "__main__":
    main()
