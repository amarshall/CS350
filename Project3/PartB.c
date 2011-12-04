#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
  int numTurns;
  sem_t processLocks[];
} Data;

Data* data;

void waitForTurn(int me, int next) {
  for(int numTurns = data->numTurns; numTurns > 0; --numTurns) {
    if(sem_wait(&data->processLocks[me]) < 0) { perror("sem_wait"); exit(1); };
    printf("Process %d: %d left\n", me, numTurns);
    if(sem_post(&data->processLocks[next]) < 0) { perror("sem_post"); exit(1); };
  }
  exit(0);
}

pid_t spawn(int me, int next) {
  pid_t pid = fork();
  if(pid > 0) {
    return pid;
  } else if(pid == 0) {
    printf("Process %d (%d) spawned\n", me, next);
    waitForTurn(me, next);
  } else if(pid < 0) { perror("fork"); exit(1); }
  exit(1);
}

int main(int argc, char** argv) {
  if(argc != 3) {
    fprintf(stderr, "Invalid arguments.\n");
    exit(1);
  }

  int numProcesses = atoi(argv[1]);

  key_t key = ftok(argv[0], 3141596);
  int shmId = shmget(key, sizeof(Data) + (numProcesses * sizeof(sem_t)), 0664 | IPC_CREAT);
  if(shmId == -1) { perror("shmid"); exit(1); }
  data = shmat(shmId, NULL, 0);
  if(data == (Data*)-1) { perror("shmdata"); exit(1); }

  data->numTurns = atoi(argv[2]);
  pid_t* processList = malloc(numProcesses * sizeof(pid_t));

  for(int i = 0; i < numProcesses; ++i) {
    int num = i % numProcesses;
    int next = (num + 1) % numProcesses;
    if(sem_init(&data->processLocks[i], 1, 0) < 0) { perror("sem_init"); exit(1); }
    processList[i] = spawn(num, next);
  }
  if(sem_post(&data->processLocks[0]) < 0) { perror("sem_post"); exit(1); };

  for(int i = 0; i < numProcesses; ++i) {
    waitpid(processList[i], NULL, 0);
    printf("Process %d done.\n", processList[i]);
  }

  if(shmctl(shmId, IPC_RMID, NULL) < 0) { perror("shmctl"); exit(1); }

  return 0;
}
