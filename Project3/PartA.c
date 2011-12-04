#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
  int currentPlayer;
  int numTurns;
} Data;

Data* data;

void waitForTurn(int me, int next) {
  for(int numTurns = data->numTurns; numTurns > 0; --numTurns) {
    while(data->currentPlayer != me) usleep(1000);
    printf("Process %d: %d left\n", me, numTurns);
    data->currentPlayer = next;
  }
  exit(0);
}

pid_t spawn(int me, int next) {
  pid_t pid = fork();
  if(pid > 0) {
    return pid;
  } else if(pid == 0) {
    waitForTurn(me, next);
  } else if(pid < 0) { perror("fork"); exit(1); }
  return 0;
}

int main(int argc, char** argv) {
  if(argc != 3) {
    fprintf(stderr, "Invalid arguments.\n");
    exit(1);
  }

  key_t key = ftok(argv[0], 3141596);
  int shmId = shmget(key, 256, 0664 | IPC_CREAT);
  if(shmId == -1) { perror("shmid"); exit(1); }
  data = shmat(shmId, NULL, 0);
  if(data == (Data*)-1) { perror("shmdata"); exit(1); }

  int numProcesses = atoi(argv[1]);
  data->numTurns = atoi(argv[2]);
  pid_t* processList = malloc(numProcesses * sizeof(pid_t));

  for(int i = 0; i < numProcesses; ++i) {
    int num = (i + 1) % numProcesses;
    int next = (num + 1) % numProcesses;
    processList[i] = spawn(num, next);
  }

  for(int i = 0; i < numProcesses; ++i) {
    waitpid(processList[i], NULL, 0);
    printf("Process %d done.\n", processList[i]);
  }

  return 0;
}
