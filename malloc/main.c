#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void *ft_malloc(size_t size) {
  void *p = sbrk(0);
  void *request = sbrk(size);
  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  } else {
    assert(p == request); // Not thread safe.
    return p;
  }
}

int main() {

	char *t = ft_malloc(1);
	t[0] = '7';
	t[1] = '1';
	t[2] = '8';
	t[3] = '\n';

	printf("t %s\n", t);
}
