#include <iostream> //input output stream to cout, cin ,endl
#include <fcntl.h>     
#include <sys/mman.h>   // used shm_open, mmap
#include <sys/stat.h>   // using for file modes
#include <unistd.h>     // used ftruncate, close, sleep
#include <semaphore.h>  // semaphore library

const char* SHM_NAME = "/a_shm"; 

struct SharedData {
    sem_t empty;
    sem_t full;
    sem_t mutex;
    int buffer[2]; //2 is the buffer size for the producer to produce 2 max and consumer to consume 2 max
    int in;         // producaaaaaaaaaaaaaaaah
    int out;        //consumaaaaaaaaaaaaaaaaah
};

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
   
    ftruncate(shm_fd, sizeof(SharedData));

    SharedData* shared = static_cast<SharedData*>(
        mmap(nullptr, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );
 
    close(shm_fd);

                                    // initialize semaphores only if this is the first process
    sem_init(&shared->empty, 1, 2); // 2 is buffer size
    sem_init(&shared->full, 1, 0);
    sem_init(&shared->mutex, 1, 1);
    shared->in  = 0;
    shared->out = 0;
    for (int i = 0; i < 2; ++i) { //loop till i < 2 (buffer size)
        shared->buffer[i] = 0;
    }

    std::cout << "[Producer] Starting production..." << std::endl;
    int itemCounter = 0;

    while (true) {
        int item = itemCounter++;

        sem_wait(&shared->empty); // waiting if the buffer full
        sem_wait(&shared->mutex); // lock a shared memory

        shared->buffer[shared->in] = item;
        std::cout << "producer produce : " << item << " (space in array " << shared->in << ")" << std::endl;
        shared->in = (shared->in + 1) % 2;

        sem_post(&shared->mutex); // unlick a shared memory
        sem_post(&shared->full);  // sigmal that the item is available

        sleep(1);
    }

    munmap(shared, sizeof(SharedData));
    shm_unlink(SHM_NAME);
    return 0;
}
