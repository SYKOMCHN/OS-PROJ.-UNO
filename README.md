# ```OPERATING SYSTEMS ASSIGNMENT WAN```

<i>Assignment Requirements:</i> <br/> <br/>
```The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.```

## ```INSTALLATION/ENVIROMENT ```
- ``` Linux OS/Enviorment ``` <br>
- ``` Flavor ? : Ubuntu``` <br>
- ``` Virtual Box``` <br>
- ``` Visual Studio Code ``` <br>
- ``` C++ Language/Library ``` <br>

## ```IMPLEMENTATION ```
- ``` producer.cpp: ``` cpp file to store the producer side of the program. <br>
- ``` consumer.cpp: ``` cpp file to store the consumer side of the program. <br> <br>

## ```Description: ``` 
``` The Producer-Consumer Problem involves having the produce memory into a set size buffer while consuming them after. Both process access the (shm_open) and (mmap), which is a shared memory. The variables sem_t empty, full, mutex are the semaphores that check if there are free spots in the array (buffer), check if the spots in the array are full , and make sures the that mutual exclusion happens. Mutual exclusion makes sure that one  process runs and finishes before the other, so there will be no race conditions (; when both producer and consumer try to modify the same shared variable without proper synchronization). The producer waits for an array to be empty before producing, while the consumer waits for an array to be filled before consuming. ```

- ``` To compile Producer: ``` g++ producer.cpp -pthread -lrt -o producer
- ``` To compile Consumer: ``` g++ consumer.cpp -pthread -lrt -o consumer
- ``` To Run Both File: ``` ./producer & ./consumer & <br>



## ``` EXAMPLE / RESULT ```

![michael_jackson](https://github.com/user-attachments/assets/f7889b1c-235a-48b4-a686-8017f68e65e6)
