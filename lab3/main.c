#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 256
#define STRING_SIZE 200

void runServer(key_t);
void runClient(key_t);

typedef struct {
  bool ready;
  char string[STRING_SIZE];
} Data;

void runServer(key_t key) {
  int shmId = shmget(key, SHM_SIZE, 0664 | IPC_CREAT);
  if(shmId == -1) perror("shmid");

  Data* data = shmat(shmId, NULL, 0);
  if(data == (Data*)-1) perror("shmdata");

  data->ready = false;
  while(!data->ready) sleep(1);
  printf("%s\n", data->string);

  shmctl(shmId, IPC_RMID, NULL);
}

void runClient(key_t key) {
  int shmId = shmget(key, SHM_SIZE, 0664);
  if(shmId == -1) perror("shmid");

  Data* data = shmat(shmId, NULL, 0);
  if(data == (Data*)-1) perror("shmdata");

  int inputLength = 0;

  while(inputLength < STRING_SIZE) {
    char c = getchar();
    if(c == '\n') break;
    data->string[inputLength++] = c;
  }
  data->string[inputLength] = '\0';
  data->ready = true;
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
