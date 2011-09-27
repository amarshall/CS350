#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

void runServer(key_t key) {
  int shmId = shmget(key, 256, 0664 | IPC_CREAT);
  if(shmId == -1) perror("shmid");

  char* shmData = shmat(shmId, NULL, 0);
  if(shmData == (char*)-1) perror("shmdata");

  *shmData = '%';
  while(*shmData == '%') sleep(1);
  printf("%s\n", shmData);

  shmctl(shmId, IPC_RMID, NULL);
}

void runClient(key_t key) {
  int shmId = shmget(key, 256, 0664);
  if(shmId == -1) perror("shmid");

  char* shmData = shmat(shmId, NULL, 0);
  if(shmData == (char*)-1) perror("shmdata");

  int inputLength = 0;

  while(inputLength < 256) {
    char c = getchar();
    if(c == '\n') break;
    shmData[inputLength++] = c;
  }
  shmData[inputLength] = '\0';
}

int main(int argc, char** argv) {
  key_t key = 3141596;

  if(argc != 2) {
    fprintf(stderr, "Invalid arguments.");
  } else if(strcmp(argv[1], "-s") == 0) {
    runServer(key);
  } else if(strcmp(argv[1], "-c") == 0) {
    runClient(key);
  }

  return 0;
}
