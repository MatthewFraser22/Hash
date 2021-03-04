

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

int hash(char* word) {
	unsigned int hash = 0, i;
	for (i = 0; word[i] != '\0'; i++) {
		hash = 31 * hash + word[i];
	}
	return hash % htsize;
}

HTNODE *new_hashnode(char *name, int value) {
	HTNODE *nn = (HTNODE *) malloc(sizeof(HTNODE));

	strcpy(nn->name, name);
	nn->value = value;
	nn->next = NULL;

	return nn;
}

HASHTABLE *new_hashtable(int size) {
	HASHTABLE *ht = (HASHTABLE *) malloc(sizeof(HASHTABLE));
	ht->hnp = (HTNODE**) malloc(sizeof(HTNODE**) * size);

	int i;
	for (i = 0; i < size; i++) {
		*(ht->hnp + i) = NULL;
	}


	ht->size = size;
	ht->count = 0;

	return ht;
}

HTNODE *search(HASHTABLE *ht, char *name) {
	int i = hash(name);
	HTNODE *p = ht->hnp[i];

	if (p != NULL) {
		while (p != NULL) {
			if (strcmp(p->name, name) == 0) {
				return p;
			}

			p = p->next;
		}
	}
	return NULL;
}

int insert(HASHTABLE *ht, HTNODE *np) {
	//hash the name
	int i = hash(np->name);

	HTNODE *p = *(ht->hnp + i), *pp = NULL;

	if (p == NULL) {
		*(ht->hnp + i) = np;
	} else {
		while (p && 0 < strcmp(np->name, p->name)) {
			pp = p;
			p = p->next;
		}
		if (strcmp(np->name, p->name) == 0) {
			p->value = np->value;
			free(np);
			return 0;

		}
		if (pp == NULL) {
			*(ht->hnp + i) = np;
		} else {
			pp->next = np;
		}
		np->next = p;
	}
	ht->count++;
	return 1;
}

int delete(HASHTABLE *ht, char *name) {
	int i = hash(name);
	HTNODE *p = *(ht->hnp + i), *pp = NULL;

	if (p != NULL) {
		while (strcmp(p->name, name) > 0) {
			pp = p;
			p = p->next;
		}
		if (strcmp(p->name, name) == 0) {
			if (pp) {
				pp->next = p->next;
			} else {
				*(ht->hnp + i) = NULL;
			}
			free(p);
			ht->count--;
			return 1;
		}
	}
	return 0;
}

void clean_hash(HASHTABLE **htp) {
	if (*htp == NULL)
		return;
	HASHTABLE *ht = *htp;
	HTNODE *sp = ht->hnp[0], *p, *temp;
	int i;
	for (i = 0; i < ht->size; i++) {
		p = ht->hnp[i];
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		ht->hnp[i] = NULL;
	}
	free(ht->hnp);
	ht->hnp = NULL;
	*htp = NULL;
}

void display_hashtable(HASHTABLE *ht, int option) {
	int i = 0;
	HTNODE *p;
	if (option == 0) {
		printf("size:  %d\n", ht->size);
		printf("count: %d\n", ht->count);
		printf("hash data:\nindex: list of the data elements");
		for (i = 0; i < ht->size; i++) {
			p = *(ht->hnp + i);
			if (p)
				printf("\n%2d: ", i);

			while (p) {
				printf("(%s, %d) ", p->name, p->value);
				p = p->next;
			}
		}
		printf("\n");
	} else {

		for (i = 0; i < ht->size; i++) {
			p = *(ht->hnp + i);
			while (p) {
				printf("%s=%d\n", p->name, p->value);
				p = p->next;
			}
		}

	}

}

