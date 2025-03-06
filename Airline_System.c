#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define NAMELEN 127

typedef struct Passenger {
	char name[NAMELEN];
	struct Passenger *next;
} Passenger;

typedef struct Flight {
	char name[NAMELEN];
	struct Flight *next;
	struct Passenger *first;
} Flight;

Flight *create_flight(char Name[]) {
	Flight *new_node = (Flight*)malloc(sizeof(Flight));
	if(new_node == NULL) {
		fprintf(stderr, "Flight allocation failed!\n");
		return NULL;
	}
	strcpy(new_node->name, Name);
	new_node->next = NULL;
	new_node->first = NULL;
	return new_node;
}

Passenger *create_passenger(char Name[]) {
	Passenger *new_node = (Passenger*)malloc(sizeof(Passenger));
	if(new_node == NULL) {
		fprintf(stderr, "Passenger allocation failed\n");
		return NULL;
	}
	strcpy(new_node->name, Name);
	new_node->next = NULL;
	return new_node;
}

void append_flight(Flight **head, char name[]) {
	Flight *new_node = create_flight(name);
	if(*head == NULL) {
		*head = new_node;
		return;
	}
	Flight *current = *head;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = new_node;
}

void append_passenger(Passenger **head, char name[]) {
	Passenger *new_node = create_passenger(name);
	if(*head == NULL) {
		*head = new_node;
		return;
	}
	Passenger *current = *head;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = new_node;
}

void remove_passenger(Passenger **head, char name[]) {
	Passenger *current = *head;
	Passenger *previous = NULL;
	if(*head == NULL) {
		return;
	}
	if(strcmp(current->name, name) == 0) {
		*head = current->next;
		free(current);
		return;
	}
	while(current != NULL && strcmp(current->name, name) != 0) {
		previous = current;
		current = current->next;
	}

	if(current == NULL) {
		fprintf(stderr, "Nothing to remove!\n");
		return;
	}
	previous->next = current->next;
	free(current);
}

Passenger *search_passenger(char name[], Passenger **head) {
	Passenger *current = *head;
	while(current != NULL) {
		if(strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

Flight *search_flight(char name[], Flight **head) {
	Flight *current = *head;
	while(current != NULL) {
		if(strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

bool reserve_ticket(char flight[], char passenger[], Flight **head) {
	Passenger *new_node = create_passenger(passenger);
	if(new_node == NULL) {
		fprintf(stderr, "Passenger couldn't be created\n");
		return false;
	}
	Flight *current = search_flight(flight, head);
	if(current != NULL) {
		append_passenger(&(current->first), passenger);
		return true;
	}
	return false;
}

bool cancel_reservation(char flight[], char passenger[], Flight **head) {
	Flight *flight_tmp = search_flight(flight, head);
	if(flight_tmp == NULL) {
		return false;
	}
	remove_passenger(&(flight_tmp->first), passenger);
	return true;
}

bool check_reservation(char flight[], char passenger[], Flight **head) {
	Flight *tmp_flight = search_flight(flight, head);
	if(tmp_flight == NULL) {
		printf("Flight not found\n");
		return false;
	}
	Passenger *tmp_passenger = search_passenger(passenger, &(tmp_flight->first));
	if(tmp_passenger == NULL) {
		printf("Passenger on flight %s not found\n", tmp_flight->name);
		return false;
	}
	return true;
}

void display_passengers(char flight_name[], Flight **head) {
	Flight *flight = search_flight(flight_name, head);
	if(flight == NULL) {
		printf("Flight not found!\n");
		return;
	}
	Passenger *current = flight->first;
	printf("Start of Passenger list:\n");
	while(current != NULL) {
		printf("%s\n", current->name);
		current = current->next;
	}
	printf("End of Passenger list!");
}

void menu(Flight **head) {
	int temp;
	char flight[NAMELEN];
	char passenger[NAMELEN];
	printf("Welcome to the Simple Airline Reservation System!\n");
	printf("You have the following options: \n");
	printf("\t 1. Reserve a ticket\n");
	printf("\t 2. Cancel a reservation\n");
	printf("\t 3. Check if ticket is reserved\n");
	printf("\t 4. Display the passengers\n");
	printf("\nEnter your choice: \n");

	scanf("%d", &temp);
	switch(temp) {
		case 1: printf("Enter the flight\n");
			scanf("%s", flight);
			printf("Enter your name\n");
			scanf("%s", passenger);
			if(reserve_ticket(flight, passenger, head)) {
				printf("Reservation was successful!\n");
			}
			else {
				printf("Failed to reserve the flight\n");
			}
			break;
		case 2: printf("Enter the flight\n");
			scanf("%s", flight);
			printf("Enter your name\n");
			scanf("%s", passenger);
			if(cancel_reservation(flight, passenger, head)) {
				printf("Cancelation successful\n");
			}
			else{
				printf("Failed to cancel, please try again\n");
			}
			break;
		case 3: printf("Enter the flight\n");
			scanf("%s", flight);
			printf("Enter your name\n");
			scanf("%s", passenger);
			if(check_reservation(flight, passenger, head)) {
				printf("Reservation exists!\n");
			}
			else {
				printf("No result!\n");
			}
			break;
		case 4: printf("Enter the flight\n");
			scanf("%s", flight);
			display_passengers(flight, head);
			break;
		default: printf("No option recognized\n");
			 break;
	}
}

void free_all_memory(Flight **head) {
    Flight *current_flight = *head;
    while(current_flight != NULL) {
        Passenger *current_passenger = current_flight->first;
        while(current_passenger != NULL) {
            Passenger *tmp = current_passenger;
            current_passenger = current_passenger->next;
            free(tmp);
        }
        
        Flight *tmp = current_flight;
        current_flight = current_flight->next;
        free(tmp);
    }
    *head = NULL;
}

int main(void) {
	Flight *head = NULL;

	append_flight(&head, "Quantas Hawaii->Paris");
	append_flight(&head, "KLM Honululu->Paris");
	append_flight(&head, "Delta Cologne->Shanghai");
	append_flight(&head, "Quantas Riad->Tokyo");
	append_flight(&head, "Lufthansa Warsaw->Paris");
	append_flight(&head, "Lufthansa Berlin->Milan");

	while(true) {
		menu(&head);
	}
	free_all_memory(&head);
	return 0;
}
