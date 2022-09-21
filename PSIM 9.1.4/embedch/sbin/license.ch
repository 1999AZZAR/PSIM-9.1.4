#!/bin/ch
// Purpose: copyright and license information
// History: created by Harry H. Cheng, 2/12/1995
#include <sys/stat.h> 
#include <stdlib.h>  
#include <stdio.h>

int main() {
  char licensefile[256];
  struct stat buf;
  size_t filesize;
  FILE *fp;
  unsigned char *license;

  strcpy(licensefile, getenv("CHHOME"));
  strcat(licensefile, "/license/license_Ch");
  if(stat(licensefile, &buf)!=0) {
    fprintf(stderr, "Error: license file %s does not exist\n", licensefile);
    exit(1);
  }
  filesize = buf.st_size;

  fp = fopen (licensefile, "rb");
  if (fp== NULL) {
    fprintf(stderr, "Error: open license file %s\n", licensefile);
    exit(1);
  }

  license = (unsigned char *)malloc(sizeof(unsigned char)*filesize);
  if(license == NULL) {
    fprintf(stderr, "Error: no memory for handling license file %s\n", licensefile);
    exit(1);
  }
  fread (license, sizeof (unsigned char), filesize, fp);
  fclose(fp);
  fwrite(license,sizeof(unsigned char), filesize, stdout);
  free(license);
  exit(0);
}
