#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

  // check if right number of arguments are given
  if (argc != 3) {
    printf("Please specify a source file and a destination file.\n");
    printf("E.g: ./copy fileA fileB\n");

    // https://www.educba.com/stderr-in-c/
    fprintf(stderr, "Expected 2 arguments, but only %d were given.\n", (argc - 1));
    return -1;
  }

  // https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
  // ensure source file exists
  if ( access( argv[1], F_OK ) == 0 ) {
    printf("Source file exists!\n");
  } else {
    printf("Source file does not exist!\n");
    return -1;
  }

  // ensure destination file does not exist
  if ( access ( argv[2], F_OK ) == -1 ) {
    printf("Destination file does not exist!\n");
  } else {
    printf("Destination file exists!\n");
    return -1;
  }

  //https://stackoverflow.com/questions/328944/how-do-i-check-if-a-file-is-a-regular-file
  struct stat sb;

  // we use lstat, because stat by default will ignore a symlink and will call it regular
  if (lstat( argv[1], &sb ) == 0 && S_ISREG(sb.st_mode)) {
    printf("Source file is regular\n");
  }

  // https://fresh2refresh.com/c-programming/c-file-handling/fgetc-function-c/ 
  FILE *sourceFile = fopen(argv[1], "r");
  FILE *destinationFile = fopen(argv[2], "w");

  
  if ( sourceFile == NULL ) {
    printf("Source file could not be opened...\n");
    return -1;
  }
  
  while (1) {
    char c = fgetc(sourceFile);
    if (c == EOF)
      break ;
    fputc(c, destinationFile);
  }

  
  
  
  printf("Hello World");
  return 0;
}
