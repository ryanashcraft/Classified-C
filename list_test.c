/**
 * Author: Ryan Ashcraft
 *
 * test.c
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

 #include "list.h"

typedef struct Student {
	char *first_name;
	char *last_name;
	int grade;
	unsigned int gtid;
} Student;

void print_num(void *);

Student *create_student(const char *, const char *, int, unsigned int);
void print_student(void *);
void free_student(void *);
int student_eq(const void *, const void *);
int student_is_failing(const void *);

int is_not_null(const void *);
int is_null(const void *);

int compare_student_by_grade(const void *, const void *);

void test_case(char *name, void (*test_op)(void));
void print_list_size(struct llist *);

void test_empty_list(void);
void test_add_front(void);
void test_add_front_remove(void);
void test_add_multiple_front(void);
void test_find_occurrence_fail_empty(void);
void test_find_occurrence_success(void);
void test_freed_list(void);
void test_add_front_multiple(void);
void test_add_back_multiple(void);
void test_add_ints(void);
void test_size(void);

void test_remove_front(void);
void test_remove_back(void);

void test_remove_index(void);
void test_remove_index_first(void);
void test_remove_index_last(void);
void test_remove_index_single(void);
void test_remove_above_bounds(void);
void test_remove_below_bounds(void);

void test_remove_data(void);
void test_remove_data_all(void);
void test_remove_data_none(void);
void test_remove_data_empty(void);

void test_remove_if(void);
void test_remove_if_always(void);
void test_remove_if_never(void);
void test_remove_if_empty(void);

void test_is_empty_true(void);
void test_is_empty_false(void);

void test_front(void);
void test_back(void);
void test_get_index(void);

void test_add_order(void);

Student *create_student(const char *first_name, const char *last_name, int grade, unsigned int gtid) {    
    Student *student = malloc(sizeof(struct Student));
    assert(student);
    
    student->first_name = malloc(sizeof(char) * strlen(first_name) + 1);
    assert(student->first_name);
    sprintf(student->first_name, "%s", first_name);
    
    student->last_name = malloc(sizeof(char) * strlen(last_name) + 1);
    assert(student->last_name);
    sprintf(student->last_name, "%s", last_name);
    
    student->grade = grade;
    student->gtid = gtid;
    
	return student;
}

void print_student(void *data) {
    Student *student = (Student *)data;
    printf("Student: %s %s\n", student->first_name, student->last_name);
    printf("Grade: %d\n", student->grade);
    printf("GtID: %d\n", student->gtid);
} 

void print_num(void *data) {
    int *num = (int *)data;
    printf("%d\n", *num);
}

void free_student(void *data) {
    Student *student = (Student *)data;
    free(student->first_name);
    free(student->last_name);
    
    free(data);
}

int student_eq(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    
    if (studentA->grade != studentB->grade) {
        return 0;
    } else if (studentA->gtid != studentB->gtid) {
        return 0;
    } else if (strncmp(studentA->first_name, studentB->first_name, strlen(studentA->first_name)) != 0) {
        return 0;
    } else if (strncmp(studentB->last_name, studentA->last_name, strlen(studentA->last_name)) != 0) {
        return 0;
    }
    
	return 1;
}

int student_is_failing(const void *data) {
	Student *student = (Student *)data;
	return (student->grade < 70);
}

int is_not_null(const void *data) {
    return (data != NULL);
}

int is_null(const void *data) {
    return (data == NULL);
}

int compare_student_by_grade(const void *a, const void *b) {
    Student *student_a = (Student *)a;
    Student *student_b = (Student *)b;

    return student_a->grade - student_b->grade;
}

int main(void)  {
  	test_case("An empty list should print nothing.", test_empty_list);
 	
    test_case("A list with one student should print that student.", test_add_front);
 	test_case("Test adding and removing a single student. Should print nothing.", test_add_front_remove);
 	test_case("A list with two students should print those two students.", test_add_multiple_front);
	
    test_case("Finding occurence when a node is not in the list should fail.", test_find_occurrence_fail_empty);
	test_case("Finding occurence when a node is in the list should work.", test_find_occurrence_success);
 	
    test_case("A freed, empty list should print nothing.", test_freed_list);
	
    test_case("Test pushing multiple students to front.", test_add_front_multiple);
	test_case("Test pushing multiple students to back.", test_add_back_multiple);
    
    test_case("A list with ints should print integers.", test_add_ints);
	
    test_case("Test size function. Size should be 4.", test_size);
    
    test_case("Test remove from front.", test_remove_front);
    test_case("Test remove from back.", test_remove_back);
    
    test_case("Test remove at index. Brandon should not be in the list.", test_remove_index);
    test_case("Test remove at index. Nick should not be in the list.", test_remove_index_first);
    test_case("Test remove at index. Ryan should not be in the list.", test_remove_index_last);
    test_case("Test remove at index. List should be empty after removal.", test_remove_index_single);
    test_case("Test remove at index above upper bound. The list shouldn't be affected.", test_remove_above_bounds);
    test_case("Test remove at index below lower bound. The list shouldn't be affected.", test_remove_below_bounds);
    
	test_case("Test remove data. There shouldn't be any Brandons in the list.", test_remove_data);
    test_case("Test remove data. The list should be empty after removals.", test_remove_data_all);
    test_case("Test remove data. The list shouldn't be affected.", test_remove_data_none);
    test_case("Test remove data on empty list.", test_remove_data_empty);
    
	test_case("Test conditional remove. There shouldn't be anyone with less than a 70 in the list.", test_remove_if);
    test_case("Test conditional remove. The list should be empty after removals.", test_remove_if_always);
    test_case("Test conditional remove. The list shouldn't be affected.", test_remove_if_never);
    test_case("Test conditional remove on empty list.", test_remove_if_empty);
	
    test_case("Test is empty. Should be true.", test_is_empty_true);
    test_case("Test is empty. Should be false.", test_is_empty_false);
    
    test_case("Test front retrieval.", test_front);
    test_case("Test back retrieval.", test_back);
    test_case("Test index retrieval.", test_get_index);
    
    test_case("Test add in order.", test_add_order);

  	return 0;
}

void test_case(char *desc, void (*test_op)(void)) {
    static int test_num = 0;
    test_num++;
    
    printf("\n\
****************************************************************************\n\
* TEST CASE %d\n\
* %s\n\
****************************************************************************\n", test_num, desc);

    test_op();
}

void print_list_size(struct llist *llist) {
    printf("size of list: %d\n", size(llist));
}

void test_empty_list() {
    list *llist = create_list();

    traverse(llist, print_student);
    print_list_size(llist);

    empty_list(llist, free_student);
    free(llist);
}

void test_add_front() {
    list *llist = create_list();
    
    push_front(llist, create_student("Nick", "Polive", 56, 239402128));
    
    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_add_front_remove() {
    list *llist = create_list();
    
    push_front(llist, create_student("Nick", "Polive", 56, 239402128));
    
 	remove_front(llist, free_student);

    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_add_multiple_front() {
    list *llist = create_list();

    push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
 	push_front(llist, create_student("George", "Burdell", 65, 902313373));
    
 	traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_find_occurrence_fail_empty() {
    list *llist = create_list();
    
    Student *student1 = create_student("Nurse", "Joy", 3, 131313137);
    
    printf("%d\n", find_occurrence(llist, student1, student_eq));

    free_student(student1);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_find_occurrence_success() {
    list *llist = create_list();
    
    push_front(llist, create_student("George", "Burdell", 65, 902313373));
    push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
    
    Student *student1 = create_student("George", "Burdell", 65, 902313373);
    Student *student2 = create_student("Baron", "von Baris", 92, 123456789);
    
	printf("%d\n", find_occurrence(llist, student1, student_eq));
    printf("%d\n", find_occurrence(llist, student2, student_eq));
    
    free_student(student1);
    free_student(student2);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_freed_list() {
    list *llist = create_list();
    
    push_front(llist, create_student("George", "Burdell", 65, 90231337));
    push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
    
    empty_list(llist, free_student);
    
    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_add_front_multiple() {
    list *llist = create_list();
    
    push_back(llist, create_student("George", "Washington", 1, 902313373));
    push_back(llist, create_student("Teddy", "Roosevelt", 2, 902313373));
    push_back(llist, create_student("George", "Bush", 3, 000));
    
    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_add_back_multiple() {
    list *llist = create_list();

    push_front(llist, create_student("George", "Washington", 1, 902313373));
    push_front(llist, create_student("Teddy", "Roosevelt", 2, 902313373));
    push_front(llist, create_student("George", "Bush", 3, 000));
    
    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_add_ints() {
    list *llist = create_list();
        
    int *test9a = malloc(sizeof(int));
    *test9a = 5;
    int *test9b = malloc(sizeof(int));
    *test9b = 6;
    push_front(llist, test9a);
    push_front(llist, test9b);
    traverse(llist, print_num);
    print_list_size(llist);

    empty_list(llist, free);
    free(llist);
}

void test_size() {
    list *llist = create_list();
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_front(void) {
    list *llist = create_list();
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    remove_front(llist, free_student);

    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_back(void) {
    list *llist = create_list();
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    remove_back(llist, free_student);
   
    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_index() {
    list *llist = create_list();
    int success;
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    
    success = remove_index(llist, 2, free_student);
    printf("remove success: %d\n", success);
	traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_index_first(void) {
    list *llist = create_list();
    int success;
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    
    success = remove_index(llist, 0, free_student);
    printf("remove success: %d\n", success);
	traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_index_last(void) {
    list *llist = create_list();
    int success;
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    
    success = remove_index(llist, 3, free_student);
    printf("remove success: %d\n", success);
	traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_index_single(void) {
    list *llist = create_list();
    int success;
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    
    success = remove_index(llist, 0, free_student);
    printf("remove success: %d\n", success);
	traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_above_bounds() {
    list *llist = create_list();
    int success;
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    
    success = remove_index(llist, 20, free_student);
    printf("remove success: %d\n", success);
	traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_below_bounds() {
    list *llist = create_list();
    int success;
    
    push_back(llist, create_student("Nick", "Polive", 56, 239402128));
    push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
    push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
    
    success = remove_index(llist, -1, free_student);
    printf("remove success: %d\n", success);
	traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}

void test_remove_data() {
	list *llist = create_list();
    int remove_count;
    
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
	push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));

	Student *brandonCopy = create_student("Brandon", "Whitehead", 0, 000000000);
	
    remove_count = remove_data(llist, brandonCopy, student_eq, free_student);
	printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    print_list_size(llist);
    
    free_student(brandonCopy);

	empty_list(llist, free_student);
	free(llist);
}

void test_remove_data_all() {
	list *llist = create_list();
    int remove_count;
    
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    
	Student *brandonCopy = create_student("Brandon", "Whitehead", 0, 000000000);
	
    remove_count = remove_data(llist, brandonCopy, student_eq, free_student);
    printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    print_list_size(llist);

    free_student(brandonCopy);
    
	empty_list(llist, free_student);
	free(llist);
}

void test_remove_data_none() {
	list *llist = create_list();
    int remove_count;
    
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 56, 239402128));
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
	push_back(llist, create_student("Ryan", "Ashcraft", 90, 902708035));
	push_back(llist, create_student("Brandon", "Whitehead", 0, 000000000));
    
	Student *brandonCopy = create_student("Brandon", "Whitehead", 0, 123456);
	
    remove_count = remove_data(llist, brandonCopy, student_eq, free_student);
	printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    print_list_size(llist);
    
    free_student(brandonCopy);
    
	empty_list(llist, free_student);
	free(llist);
}

void test_remove_data_empty() {
    list *llist = create_list();
    int remove_count;
    
	Student *brandonCopy = create_student("Brandon", "Whitehead", 0, 123456);
	
    remove_count = remove_data(llist, brandonCopy, student_eq, free_student);
	printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    print_list_size(llist);
    
    free_student(brandonCopy);
    
	empty_list(llist, free_student);
	free(llist);
}

void test_remove_if() {
	list *llist = create_list();
    int remove_count;
    
	push_back(llist, create_student("Brandon", "Whitehead", 100, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 70, 239402128));
	push_back(llist, create_student("Ryan", "Ashcraft", 92, 902708035));

	remove_count = remove_if(llist, student_is_failing, free_student);
	printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    print_list_size(llist);

	empty_list(llist, free_student);
	free(llist);
}

void test_remove_if_always() {
    list *llist = create_list();
    int remove_count;
    
	push_back(llist, create_student("Brandon", "Whitehead", 100, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 70, 239402128));
	push_back(llist, create_student("Ryan", "Ashcraft", 92, 902708035));
    
	remove_count = remove_if(llist, is_not_null, free_student);
	printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    print_list_size(llist);
    
	empty_list(llist, free_student);
	free(llist);
}

void test_remove_if_never() {
    list *llist = create_list();
    int remove_count;
    
	push_back(llist, create_student("Brandon", "Whitehead", 100, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 70, 239402128));
	push_back(llist, create_student("Ryan", "Ashcraft", 92, 902708035));
    
	remove_count = remove_if(llist, is_null, free_student);
    printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    print_list_size(llist);
    
	empty_list(llist, free_student);
	free(llist);
}

void test_remove_if_empty() {
    list *llist = create_list();
    int remove_count;
    
	remove_count = remove_if(llist, is_not_null, free_student);
    printf("remove count: %d\n", remove_count);
	traverse(llist, print_student);
    
	empty_list(llist, free_student);
	free(llist);
}

void test_is_empty_true() {
    list *llist = create_list();
    
    push_front(llist, create_student("James", "Smith", 80, 90280835));
    remove_back(llist, free_student);
    
    printf("empty: %d\n", is_empty(llist));
    
    empty_list(llist, free_student);
    free(llist);
}

void test_is_empty_false() {
    list *llist = create_list();
    
    push_front(llist, create_student("James", "Smith", 80, 90280835));
    
    printf("empty: %d\n", is_empty(llist));
    
    empty_list(llist, free_student);
    free(llist);
}

void test_front() {
    list *llist = create_list();
    
	push_back(llist, create_student("Brandon", "Whitehead", 100, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 70, 239402128));
	push_back(llist, create_student("Ryan", "Ashcraft", 92, 902708035));
    
    printf("front student:\n");
    print_student(front(llist));
    
	empty_list(llist, free_student);
	free(llist);
}

void test_back() {
    list *llist = create_list();
    
	push_back(llist, create_student("Brandon", "Whitehead", 100, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 70, 239402128));
	push_back(llist, create_student("Ryan", "Ashcraft", 92, 902708035));
    
    printf("back student:\n");
    print_student(back(llist));
    
	empty_list(llist, free_student);
	free(llist);
}

void test_get_index() {
    list *llist = create_list();
    
	push_back(llist, create_student("Brandon", "Whitehead", 100, 000000000));
	push_back(llist, create_student("Nick", "Polive", 56, 239402128));
	push_back(llist, create_student("Foo", "Fighter", 70, 239402128));
	push_back(llist, create_student("Ryan", "Ashcraft", 92, 902708035));
    
    printf("student at index 1:\n");
    Student *student = get_index(llist, 1);
    if (student != NULL) {
        print_student(student);
    }
    
	empty_list(llist, free_student);
	free(llist);
}

void test_add_order(void) {
    list *llist = create_list();
    set_list_sort_op(llist, compare_student_by_grade);
    
    push_in_order(llist, create_student("Brandon", "Whitehead", 100, 000000000));
    push_in_order(llist, create_student("Nick", "Polive", 56, 239402128));
    push_in_order(llist, create_student("Foo", "Fighter", 70, 239402128));
    push_in_order(llist, create_student("Ryan", "Ashcraft", 92, 902708035));
    
    traverse(llist, print_student);
    print_list_size(llist);
    
    empty_list(llist, free_student);
    free(llist);
}