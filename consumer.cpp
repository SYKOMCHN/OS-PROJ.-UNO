#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>

const char* SHM_NAME = "/a_shm";

struct SharedData {
    sem_t empty;
    sem_t full;
    sem_t mutex;
    int buffer[2];
    int in;
    int out;
};

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);

    SharedData* shared = static_cast<SharedData*>(
        mmap(nullptr, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );
    close(shm_fd);

    std::cout << "[Consumer] Starting consumption..." << std::endl;

    while (true) {
        sem_wait(&shared->full);  // waiting for if buffer is empty
        sem_wait(&shared->mutex); // locking the shared memory

        int item = shared->buffer[shared->out];
        std::cout << "consumer consume: " << item << " (space in array " << shared->out << ")" << std::endl;
        shared->out = (shared->out + 1) % 2;

        sem_post(&shared->mutex); // unlocking the shared memory
        sem_post(&shared->empty); // signalling that a ther is a free spot

        sleep(2);
    }

    munmap(shared, sizeof(SharedData));
    return 0;
}
