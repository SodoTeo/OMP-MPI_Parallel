import threading as th
import time

N = 10

#Lists constraction
firstsourcearray, secondsourcearray, thirdarray = ([] for i in range(3))


#num of threads
threads = 10

#filling arrays
for i in range(N):
    firstsourcearray.append(i * 2.0)
    secondsourcearray.append(i * 3.0)


def worker(id):
    thirdarray.append(firstsourcearray[id] + secondsourcearray[id])
    print("The total Sum of Two Lists =  ", thirdarray)

#timer start
start = time.time()

if __name__ == "__main__":
    thr = list()

    #threads initialisation
    for i in range(threads):
        x = th.Thread(target=worker, args=(i,))
        thr.append(x)
        x.start()
#timer stop
end = time.time()

print("time took for paraller in millisecs " , (time.time() - start) * 1000)
