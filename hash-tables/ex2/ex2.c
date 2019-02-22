#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));
  char *ret;
  int num = 1;

  // YOUR CODE HERE
  for (int i = 0; i < length; i++)
  {
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }

  // Find start area of trip
  ret = hash_table_retrieve(ht, "NONE");
  route[0] = strdup(ret);

  while (strcmp(ret, "NONE") != 0)
  {
    // new ret by using previous ret value
    ret = hash_table_retrieve(ht, ret);
    if (ret != NULL)
    {
      route[num] = strdup(ret);
    }
    num++;
  }

  destroy_hash_table(ht);
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
    free(route[i]);
  }

  free(route);
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
