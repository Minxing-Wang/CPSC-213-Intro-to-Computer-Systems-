#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

struct Person_class{
	void* super; 
	void (* toString ) (void* , char*, int);
};

struct Person{
	struct Person_class* class; 
	char* name; 
	
}; 

void Person_toString(void* this, char* buf, int size) {
	struct Person* person = this; 
	snprintf(buf, size, "Name: %s" , person->name);
}

struct Person_class Person_class_obj = {NULL, Person_toString};

struct Person* new_Person(char* pname){
	struct Person* obj = malloc (sizeof(struct Person));
	obj->class = &Person_class_obj;
	obj->name = strdup(pname); 
	return obj; 
}

struct Student_class{
	struct Person_class* super; 
	void (* toString ) (void* , char*, int); 

}; 

struct Student {
	struct Student_class* class ;
	char* name; 
	int sid; 
	
};

void Student_toString (void* this, char* buf, int size){
	struct Student* student = this; 
	char buf1[size];
	student->class->super->toString(student, buf1, size);
	snprintf(buf, size, "%s, SID: %i", buf1, student->sid ); 
}

struct Student_class Student_class_obj = {&Person_class_obj, Student_toString};

struct Student* new_Student(char* pname, int ssid){
	struct Student* obj = malloc (sizeof (struct Student));
	obj->class = &Student_class_obj;
	obj->name = strdup(pname); 
	obj->sid = ssid; 
	return obj; 
}

void print(void* this){
	struct Person* per =  this;
	char buf[1000]; 
	per->class->toString(per, buf, sizeof(buf));
	printf("%s\n", buf);
}

int main() {
	int i ;
	
	struct Person* Alex = new_Person("Alex");
	struct Student* Alice = new_Student("Alice", 300);
	void* people[] = {Alex, Alice}; 

	for(i = 0 ; i <2 ; i++){
		print(people[i]);
	}
	
}
