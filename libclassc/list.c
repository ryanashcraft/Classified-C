/**
 * CS 2110 - Fall 2011 - Homework #11
 * Edited by: Brandon Whitehead
 *
 * Implemented by: Ryan Ashcraft
 *
 * list.c
 **/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


#include "list.h"
#include "assert.h"

typedef struct lnode {
  struct lnode* prev;
  struct lnode* next;
  void *data;
} node;


static node* create_node(struct llist *list, void *data);

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void) {
  list *list = malloc(sizeof(struct llist));
  assert(list);
  
  list->head = NULL;
  list->size = 0;
  
  return list;
}

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(struct llist *list, void *data) {
  node *node = malloc(sizeof(struct lnode));
  assert(node);
  
  node->prev = NULL;
  node->next = NULL;
  node->data = data;
  
  return node;
}

void set_list_sort_op(list *llist, comp_op compare_func) {
  llist->sort_op = compare_func;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void *data) {
  node *old_tail;
  node *new_node = create_node(llist, data);
  node *old_head = llist->head;
      
  if (old_head == NULL) {
      llist->head = new_node;
      new_node->prev = new_node;
      new_node->next = new_node;
      
      llist->size++;
      
      return;
  }
      
  old_tail = llist->head->prev;
  
  new_node->prev = old_tail;
  old_tail->next = new_node;
  new_node->next = old_head;
  old_head->prev = new_node;
  
  llist->head = new_node;
  
  llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void *data) {
  push_front(llist, data);
  
  llist->head = llist->head->next;
}

void push_in_order(list *llist, void *data) {
  node *new_node;
  node *new_next;
  node *n;

  /* if no sort op is defined, just push to back */
  if (!llist->sort_op) {
    push_back(llist, data);
    return;
  }

  new_node = create_node(llist, data);
  new_next = NULL;
      
  if (llist->head == NULL) {
      llist->head = new_node;
      new_node->prev = new_node;
      new_node->next = new_node;
      
      llist->size++;
      
      return;
  }
        
  n = llist->head;
  do {
    if (llist->sort_op(new_node->data, n->data) < 0) {
      new_next = n;
      break;
    }

    n = n->next;
  } while (n != llist->head);

  if (!new_next) {
    free(new_node);
    push_back(llist, data);
  } else {
    if (new_next == llist->head) {
      llist->head = new_node;
    }

    new_node->next = new_next;
    new_node->prev = new_next->prev;

    new_node->prev->next = new_node;
    
    new_next->prev = new_node;

    llist->size++;
  }
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func) {
  node *old_head;
  node *new_head;
  node *old_tail;

  if (llist->head == NULL) {
      return -1;
  }
  
  old_head = llist->head;
  new_head = llist->head->next;
  old_tail = llist->head->prev;
  
  old_tail->next = new_head;
  new_head->prev = old_tail;
  
  if (new_head != old_head) {
      llist->head = new_head;
  } else {
      llist->head = NULL;
  }
  
  if (free_func) {
    free_func(old_head->data);
  }
  free(old_head);
  
  llist->size--;
  
  return 0;
}

/** remove_index
  *
  * Removes the indexth node of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param index index of the node to remove.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_index(list* llist, int index, list_op free_func) {
  node *n = llist->head;
  node *node_to_remove = NULL;
  
  if (!n) {
      return -1;
  }
  
  if (llist->head->next == llist->head) {
      if (index == 0) {
          node_to_remove = llist->head;
      } else {
          return -1;
      }
  }
  
  if (node_to_remove == NULL) {
      int i = 0;
      do {
          if (i == index) {
              node_to_remove = n;
              break;
          }
          
          n = n->next;
          i++;
      } while (n != llist->head);
  }
  
  if (node_to_remove != NULL) {
      node *prev_node = node_to_remove->prev;
      node *next_node = node_to_remove->next;
      
      prev_node->next = next_node;
      next_node->prev = prev_node;
      
      if (node_to_remove == llist->head) {
          if (llist->head != llist->head->next) {
              llist->head = next_node;
          } else {
              llist->head = NULL;
          }
      }
      
      free_func(node_to_remove->data);
      free(node_to_remove);
      
      llist->size--;
      
      return 0;
  }
  
  return -1;
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func) {
  node *old_tail;
  node *new_tail;

  if (llist->head == NULL) {
      return -1;
  }
  
  old_tail = llist->head->prev;
  new_tail = llist->head->prev->prev;
  
  new_tail->next = llist->head;
  llist->head->prev = new_tail;
  
  if (old_tail == llist->head) {
      llist->head = NULL;
  }
  
  free_func(old_tail->data);
  free(old_tail);
  
  llist->size--;
  
  return 0;
}

/** remove_data
  *
  * Removes ALL nodes whose data is EQUAL to the data you passed in or rather when the comparison function returns true (!0)
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list
  * @param data data to compare to.
  * @param compare_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see equal_op.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_data(list* llist, const void *data, equal_op compare_func, list_op free_func) {
	node *n = llist->head;
	node *node_to_remove = NULL;
	int count = 0;
	unsigned char head_changed = 0;
  node *next_node;

	if (!n) {
		return 0;
	}

	do {
		head_changed = 0;
    next_node = n->next;
		
		if (compare_func(n->data, data) != 0) {
			node_to_remove = n;
            
            if (n == n->next) {
                next_node = NULL;
                
                if (free_func) {
                  free_func(n->data);
                }
                free(n);
                llist->size--;
                count++;
                
                llist->head = NULL;
            } else {
                node_to_remove->prev->next = node_to_remove->next;
                node_to_remove->next->prev = node_to_remove->prev;
                if (node_to_remove == llist->head) {
                    llist->head = node_to_remove->next;
                    head_changed = 1;
                }
                if (free_func) {
                  free_func(n->data);
                }
                free(node_to_remove);
                llist->size--;
                count++;
                node_to_remove = NULL;
            }
		}
        
        n = next_node;
        next_node = NULL;
	} while (n != NULL && (n != llist->head || head_changed));

    return count;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func) {
  node *n = llist->head;
	node *node_to_remove = NULL;
	int count = 0;
	unsigned char head_changed = 0;
  node *next_node;

	if (!n) {
		return 0;
	}

	do {
		head_changed = 0;
    next_node = n->next;
        
		if (pred_func(n->data)) {
			node_to_remove = n;
            
            if (n == n->next) {
                next_node = NULL;

                free_func(n->data);
                free(n);
                llist->size--;
                count++;
                
                llist->head = NULL;
            } else {
                node_to_remove->prev->next = node_to_remove->next;
                node_to_remove->next->prev = node_to_remove->prev;
                if (node_to_remove == llist->head) {
                    llist->head = node_to_remove->next;
                    head_changed = 1;
                }
                free_func(n->data);
                free(node_to_remove);
                llist->size--;
                count++;
                node_to_remove = NULL;
            }
		}
        
		n = next_node;
	} while (n != NULL && (n != llist->head || head_changed));

    return count;
}

/** ll_front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void *ll_front(list* llist) {
  if (llist->head != NULL) {
      return llist->head->data;
  }
  
  return NULL;
}

/** ll_get_index
  *
  * Gets the data at the indexth node of the linked list
  * If the list is empty or if the index is invalid return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the indexth node in the linked list or NULL.
  */
void *ll_get_index(list* llist, int index) {
  node *n;
  int i;

  if (index < 0 || index >= llist->size) {
      return NULL;
  }
  
  n = llist->head;
  
  if (!n) {
      return NULL;
  }
  
  if (llist->head->next == llist->head) {
      if (index == 0) {
          return llist->head->data;
      } else {
          return NULL;
      }
  }
  
  i = 0;
  do {
      if (i == index) {
          return n->data;
      }
      
      n = n->next;
      i++;
  } while (n != llist->head);
  
  return NULL;
}

void* get_first_occurrence(list* llist, list_pred_args test_func, ...) {
  node *n;

  va_list args;
  va_start(args, test_func);

  n = llist->head;
  
  if (!n) {
      va_end(args);
      return NULL;
  }
  
  if (llist->head->next == llist->head) {
      if (test_func(llist->head->data, &args)) {
          va_end(args);
          return llist->head->data;
      } else {
          va_end(args);
          return NULL;
      }
  }
  
  do {
      if (test_func(n->data, &args)) {
          va_end(args);
          return n->data;
      }
      
      n = n->next;

      /* you have to call va_start again to reset arguments */
      va_start(args, test_func);
  } while (n != llist->head);
  
  va_end(args);
  return NULL;
}

/** ll_back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void *ll_back(list* llist) {    
  if (llist->head != NULL) {
      return llist->head->prev->data;
  }
  
  return NULL;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist) {
  if (llist->size == 0 && (llist->head == NULL || llist->head->data == NULL)) {
      return 1;
  }
  
  return 0;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist) {
    return llist->size;
}

/** find_first_occurence
  *
  * Tests if the search data passed in is in the linked list.
  *
  * @param llist a pointer to a linked list.
  * @param search data to search for the occurence.
  * @param compare_func a pointer to a function that returns true if two data items are equal @see equal_op.
  * @return 1 if the data is indeed in the linked list 0 otherwise.
  */
int find_occurrence(list* llist, const void *search, equal_op compare_func) {
  node *n = llist->head;
  
  if (!n) {
    return 0;
  }
  
  if (llist->head->next == llist->head
    && ((compare_func && compare_func(n->data, search) != 0) || n->data == search)) {
    return 1;
  }
  
  do {
    if ((compare_func && compare_func(n->data, search) != 0) || n->data == search) {
        return 1;
    }
    
    n = n->next;
  } while (n != llist->head);
  
  return 0;
}

/** empty_list
  *
  * Empties the list after this is called the listq should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  *
  */
void empty_list(list* llist, list_op free_func) {
	node *n = llist->head;
	node *node_to_remove = NULL;

	if (!n) {
		return;
	}

	do {
    if (free_func) {
  		free_func(n->data);
    }
		node_to_remove = n;
		n = n->next;
		free(node_to_remove);
		node_to_remove = NULL;
	} while (n != llist->head);

	llist->size = 0;
    llist->head = NULL;
}

void free_list(list* llist, list_op free_func) {
  empty_list(llist, free_func);
  free(llist);
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func) {
  node *n = llist->head;

  if (!n) {
      return;
  }
  
  if (llist->head->next == llist->head) {
      do_func(n->data);
      
      return;
  }
  
  do {
      if (do_func != NULL) {
          do_func(n->data);
      }
      n = n->next;
  } while (n != llist->head);
}

void traverse_with_args(list* llist, list_op_args do_func, ...) {
  node *n = llist->head;

  if (!n) {
      return;
  }

  va_list args;
  va_start(args, do_func);
  
  if (llist->head->next == llist->head) {
      do_func(n->data, &args);
      
      va_end(args);
      return;
  }
  
  do {
      if (do_func != NULL) {
          do_func(n->data, &args);
      }
      n = n->next;

      va_start(args, do_func);
  } while (n != llist->head);
}
