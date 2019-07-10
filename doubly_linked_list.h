
#define TRUE 1
#define FALSE 0
#define BOOL int

// this is the objects in the linked list
typedef struct node {
  struct node *next;
  struct node *prev;
  int value;
  int index;
} Node;

// this is the container objectfdsfaLKS vmdsa/  for the Nodes
typedef struct linked_list {
  Node *head;
  int size;
} List;

BOOL create_list(List **list);
BOOL add_node(int value, List *list);
void print_list(List *list);
void clear_list(List *list);
void destroy_list(List **list);
Node *find_node(List *list, int value);
void remove_node(List *list, int value);
