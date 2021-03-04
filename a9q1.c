
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "hash.h"

int htsize = 10;

int main(int argc, char *argv[]) {
  int n = 8;	
  if (argc > 1) htsize = atoi(argv[1]);
  if (argc > 2) n = atoi(argv[2]);
  
  HASHTABLE *ht = new_hashtable(htsize);
  
  int i;
  char name[10];
  for (i=0; i<n; i++) {
	name[0] = i+'a';
  	name[1] = '\0';
	insert(ht, new_hashnode(name, i));
  }
  
  printf("hash table after insertion\n");
  display_hashtable(ht, 0);
  
  printf("\nsearch data by name %s\n", "a");
  HTNODE *hn = search(ht, "a");
  if (hn != NULL) {
    printf("Find data element: (%s, %d)\n", hn->name, hn->value);
  } else {
    printf("Not found\n");
  }

  printf("delete data by name %s\n", "a");
  delete(ht, "a");
  hn = search(ht, "a");
  if (hn != NULL) {
    printf("Find data element: (%s, %d)\n", hn->name, hn->value);
  } else {
    printf("Not found\n");
  }
 
  display_hashtable(ht, 0);
  display_hashtable(ht, 1);
  clean_hash(&ht);
  
  return 0;
}

/*
gcc hash.c a9q1.c -o a9q1
a9q1

hash table after insertion
size:  10
count: 8
hash data:
index: list of the data elements
 0: (d, 3)
 1: (e, 4)
 2: (f, 5)
 3: (g, 6)
 4: (h, 7)
 7: (a, 0)
 8: (b, 1)
 9: (c, 2)

search data by name a
Find data element: (a, 0)
delete data by name a
Not found
size:  10
count: 7
hash data:
index: list of the data elements
 0: (d, 3)
 1: (e, 4)
 2: (f, 5)
 3: (g, 6)
 4: (h, 7)
 8: (b, 1)
 9: (c, 2)
d=3
e=4
f=5
g=6
h=7
b=1
c=2

*/
 
 
 
