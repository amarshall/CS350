#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 256

typedef struct {
  int a;
  int b;
  sem_t lock;
  sem_t printable;
} Data;

int main(int argc, char** argv) {
  if(argc != 3) { fprintf(stderr, "Invalid arguments.\n"); exit(1); }

  key_t key = ftok(argv[0], 3141596);

  int shmId = shmget(key, SHM_SIZE, 0664 | IPC_CREAT);
  if(shmId == -1) { perror("shmid"); exit(1); }
  Data* data = shmat(shmId, NULL, 0);
  if(data == (Data*)-1) { perror("shmdata"); exit(1); }
  sem_init(&data->lock, 1, 0);
  sem_init(&data->printable, 1, 0);

  pid_t pid = fork();
  if(pid > 0) {

    data->a = atoi(argv[1]);
    data->b = atoi(argv[2]);
    sem_post(&data->lock);

    sem_wait(&data->printable);
    sem_wait(&data->lock);
    printf("%d\n", data->a);
    sem_post(&data->lock);
    sem_post(&data->printable);

  } else if(pid == 0) {

    sem_wait(&data->lock);
    data->a = data->a * data->b;
    sem_post(&data->lock);
    sem_post(&data->printable);

  } else { perror("fork"); exit(1); }

  return 0;
}
