#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

/////////////////////////////// USERLIST ////////////////////////////////

//display the list
void printListU(struct USER *head) {
  struct USER *ptr = head;
  struct USER *dm;
  printf("[Users:\n");
  //start from the beginning
  while(ptr != NULL) {
    printf("USERNAME: %s \n ID: %d ",ptr->username , ptr->socket);
    dm = ptr->dmhead;
    printf("\n [DM: ");
    while(dm != NULL) {
      printf("(%s,%d) ",dm->username, dm->socket);
      dm = dm->next;
    }
    printf("]");
    printListRoom(ptr->head); 
    ptr = ptr->next;
    printf("\n");    
  }
  printf("]\n");
}

void display_users(struct USER *head, char *buf, int self) {
  struct USER *ptr = head;
  char tmpbuf[1024];
  if (ptr == NULL) {
    sprintf(buf,"no logins!\n");
  }
  else {
    sprintf(buf,"[USERS]: ");
    while(ptr != NULL) {
      if(lengthRoom(ptr->head) == 0 && lengthU(ptr->dmhead) == 0 && ptr->socket != self) {  // not belong to any groups or any DMs
        sprintf(tmpbuf,"%s", ptr->username);
        strcat(buf, tmpbuf);
        ptr = ptr->next;
        if(ptr == NULL) {
          strcat(buf, "]\n");
        }
        else {
          strcat(buf, ", ");
        }         
      }
    }
  }
}

//insert link at the first location
struct USER* insertFirstU(struct USER *head, int socket, char *username) {  
  if(findU(head,username) == NULL) {       
    //create a link
    struct USER *link = (struct USER*) malloc(sizeof(struct USER));
    link->socket = socket;
    strcpy(link->username,username);
    //point it to old first USER
    link->next = head;
    //point first to new first USER
    head = link;
  }
  else {
    printf("Duplicate: %s\n", username);
  } 
  return head;
}

//delete first item
struct USER* deleteFirstU(struct USER *head) {
  //save reference to first link
  struct USER *tempLink = head;
  //mark next to first link as first 
  head = head->next;
  //return the deleted link
  free(tempLink);
  return head;
}

//is list empty
bool isEmptyU(struct USER *head) {
  return head == NULL;
}

int lengthU(struct USER *head) {
  int length = 0;
  struct USER *current;
  for(current = head; current != NULL; current = current->next) {
    length++;
  }
  return length;
}

//find a link with given socket
struct USER* findSocketU(struct USER *head, int socket) {
  //start from the first link
  struct USER* current = head;
  //if list is empty
  if(head == NULL) {
    return NULL;
  }
  //navigate through list
  while(current->socket != socket) {
    //if it is last USER
    if(current->next == NULL) {
      return NULL;
    } 
    else {
      //go to next link
      current = current->next;
    }
  }      
  //if socket found, return the current Link
  return current;
}

//find a link with given user
struct USER* findU(struct USER *head, char* username) {
  //start from the first link
  struct USER* current = head;
  //if list is empty
  if(head == NULL) {
    return NULL;
  }
  //navigate through list
  while(strcmp(current->username, username) != 0) {
    //if it is last USER
    if(current->next == NULL) {
      return NULL;
    } 
    else {
      //go to next link
      current = current->next;
    }
  }      
  //if username found, return the current Link
  return current;
}

//delete a link with given socket
struct USER* deleteSocketU(struct USER *head, int socket) {
  //start from the first link
  struct USER* current = head;
  struct USER* previous = NULL;
  //if list is empty
  if(head == NULL) {
    return NULL;
   }
  else {
    if(findSocketU(head,socket) == false) {
      printf("Socket: %d Does Not Exist!\n",socket);
      return head;
    }
  }
  //navigate through list
  while(current->socket != socket) {
    //if it is last USER
    if(current->next == NULL) {
      return NULL;
    } 
    else {
      //store reference to current link
      previous = current;
      //move to next link
      current = current->next;
    }
  }
  //found a match, update the link
  if(current == head) {
    //change first to point to next link
    head = head->next;
  } 
  else {
    //bypass the current link
    previous->next = current->next;
  }    
  free(current);
  printf("Socket: %d Has Been Removed\n",socket);
  return head;
}

//delete a link with given username
struct USER* deleteU(struct USER *head, char* username) {
  //start from the first link
  struct USER* current = head;
  struct USER* previous = NULL;
  //if list is empty
  if(head == NULL) {
    return NULL;
   }
  else if(findU(head,username)== false) {
     printf("User: %s Does Not Exist!\n",username);
     return head;
   }
   //navigate through list
   while(strcmp(current->username, username) != 0) {
     //if it is last USER
     if(current->next == NULL) {
       return NULL;
     } 
     else {
       //store reference to current link
       previous = current;
       //move to next link
       current = current->next;
     }
   }
   //found a match, update the link
   if(current == head) {
     //change first to point to next link
     head = head->next;
   } 
  else {
    //bypass the current link
    previous->next = current->next;
  }   
  free(current);
  //printf("User: %s Has Been Logged Out\n",username);
  return head;
}

void destroyU(struct USER *head) {
  struct USER *cursor, *tmp;
  if(head != NULL) {
    cursor = head->next;
    head->next = NULL;
    while(cursor != NULL) {
      tmp = cursor->next;
      free(cursor);
      cursor = tmp;
    }
  }
}

/////////////////////////////// ROOMLIST ////////////////////////////////

//display the list
void printListRoom(struct ROOM *head) {
  struct ROOM *ptr = head;
  printf("\n Rooms:");
  //start from the beginning
  while(ptr != NULL) {
    printf("(%s) ",ptr->roomname);
    // printListU(ptr->head);
    ptr = ptr->next;
  }
  printf(" ]\n");
}

void display_rooms(struct USERSINROOMS *head, char *buf) {
  struct USERSINROOMS *ptr = head;
  char tmpbuf[1024];
  if (ptr == NULL) {
    sprintf(buf,"no rooms!\n");
  }
  else {
    sprintf(buf,"[Rooms: ");
    while(ptr != NULL) {
      sprintf(tmpbuf,"%s", ptr->roomname);
      ptr = ptr->next;
      strcat(buf, tmpbuf);
      if(ptr == NULL) {
        strcat(buf, "]\n");
      }
      else {
        strcat(buf, ", ");
      }    
    }
  }
}

//insert link at the first location
struct ROOM* insertFirstRoom(struct ROOM *head, char *roomname) {
  if(findRoom(head,roomname) == NULL) {        
    //create a link
    struct ROOM *link = (struct ROOM*) malloc(sizeof(struct ROOM));
    strcpy(link->roomname,roomname);
    //point it to old first USER
    link->next = head;
    //point first to new first USER
    head = link;
  }
  else {
    printf("Duplicate Room: %s\n", roomname);
  }
  return head;
}

//delete first item
struct ROOM* deleteFirstRoom(struct ROOM *head) {
  //save reference to first link
  struct ROOM *tempLink = head;
  //mark next to first link as first 
  head = head->next;
  //return the deleted link
  free(tempLink);
  return head;
}

//is list empty
bool isEmptyRoom(struct ROOM *head) {
  return head == NULL;
}

int lengthRoom(struct ROOM *head) {
  int length = 0;
  struct ROOM *current;
  for(current = head; current != NULL; current = current->next) {
    length++;
  }
  return length;
}

//find a link with given group
struct ROOM* findRoom(struct ROOM *head, char* roomname) {
  //start from the first link
  struct ROOM* current = head;
  //if list is empty
  if(head == NULL) {
    return NULL;
  }
  //navigate through list
  while(strcmp(current->roomname, roomname) != 0) {
    //if it is last USER
    if(current->next == NULL) {
      return NULL;
    } 
    else {
      //go to next link
      current = current->next;
    }
  }      
  //if username found, return the current Link
  return current;
}

//delete a link with given rooomname
struct ROOM* deleteRoom(struct ROOM *head, char* roomname) {
  //start from the first link
  struct ROOM* current = head;
  struct ROOM* previous = NULL;
  //if list is empty
  if(head == NULL) {
    return NULL;
  }
  //navigate through list
  while(strcmp(current->roomname, roomname) != 0) {
    //if it is last USER
    if(current->next == NULL) {
      return NULL;
    } 
    else {
      //store reference to current link
      previous = current;
      //move to next link
      current = current->next;
    }
  }
  //found a match, update the link
  if(current == head) {
    //change first to point to next link
    head = head->next;
  } 
  else {
    //bypass the current link
    previous->next = current->next;
  }   
  free(current);
  return head;
}

void destroyRoom(struct ROOM *head) {
  struct ROOM *cursor, *tmp;
  if(head != NULL) {
    cursor = head->next;
    head->next = NULL;
    while(cursor != NULL) {
      tmp = cursor->next;
      free(cursor);
      cursor = tmp;
    }
  }
}

/////////////////// USERSINROOMS FUNCTIONS //////////////////////////

//display the list SERVER SIDE
void printListUsersInRooms(struct USERSINROOMS *head) {
  struct USERSINROOMS *ptr = head; 
  struct USER *userptr = ptr->head;
  while(ptr !=NULL) {
    printf("(Room: %s)\n" , ptr->roomname);
    while(userptr != NULL) {
      printf("(User: %s)\n" , userptr->username);
      userptr = userptr->next;
    }
    ptr = ptr->next; // next item which is 2nd room and we repeat bc loop
    printf("\n");
  }
}

void display_usersinrooms(struct USERSINROOMS *head, char *buf) {
  struct USERSINROOMS *ptr = head;
  char tmpbuf[1024]; 
  if (ptr == NULL) {
    sprintf(buf,"There Are No ROOMS!\n");
  }
  else {
    sprintf(buf,"[Available Rooms]\n[ ");
    while(ptr != NULL) {
      sprintf(tmpbuf," (%s) ", ptr->roomname);
      ptr = ptr->next;
      strcat(buf, tmpbuf);
      if(ptr == NULL) {
        strcat(buf, " ]\n");
      }
      else {
        strcat(buf, ", ");
      }
    }
  }
}
 
struct USERSINROOMS* insertFirstUsersInRooms(struct USERSINROOMS *allusersinrooms, char *selectedRoom) {
  if(findUsersInRooms(allusersinrooms,selectedRoom)== NULL) {
    //create a link
    struct USERSINROOMS *link = (struct USERSINROOMS*) malloc(sizeof(struct USERSINROOMS));
    strcpy(link->roomname,selectedRoom);
    link->head = NULL;
    // point first to old first Item
    link->next = allusersinrooms;
    // point first to new first Item
    allusersinrooms = link;
  }
  else {
    printf("Duplicate Room: %s\n",selectedRoom);
  }
  return allusersinrooms;
}
    
struct USERSINROOMS* deleteFirstUsersInRooms(struct USERSINROOMS *head){
  //save reference to first link
  struct USERSINROOMS *tempLink = head;
  //mark next to first link as first 
  head = head->next;
  //return the deleted link
  free(tempLink);
  return head;
}

//is list empty?
bool isEmptyUsersInRooms(struct USERSINROOMS *head) {
  return head == NULL;
}

int lengthUsersInRooms(struct USERSINROOMS *head) {
  int length = 0;
  struct USERSINROOMS *current;
  for(current = head; current != NULL; current = current->next) {
    length++;
  }
  return length;
}

//find a link with given socket
struct USERSINROOMS* findUsersInRooms(struct USERSINROOMS *head, char* roomname) {
  struct USERSINROOMS* currentitem = head;
  //if list is empty
  if(head == NULL) {
    return NULL;
  }
  //navigate through rooms & list
  while(strcmp(currentitem->roomname, roomname) != 0) {
    //if it is last node
    if(currentitem->next == NULL) {
      return NULL;
    } 
    else {
      //go to next link
      currentitem = currentitem->next;
    }
  }      
  //if username found, return the current Link
  return currentitem;
}

//delete a link with given groupname
struct USERSINROOMS* deleteUsersInRooms(struct USERSINROOMS *head, char* roomname) {
  //start from the first link
  struct USERSINROOMS* current = head;
  struct USERSINROOMS* previous = NULL;
  //if list is empty
  if(head == NULL) {
    return NULL;
  }
  //navigate through list
  while(strcmp(current->roomname, roomname) != 0) {
    //if it is last node
    if(current->next == NULL) {
      return NULL;
    } 
    else {
      //store reference to current link
      previous = current;
      //move to next link
      current = current->next;
    }
  }
  //found a match, update the link
  if(current == head) {
    //change first to point to next link
    head = head->next;
  } 
  else {
    //bypass the current link
    previous->next = current->next;
  }  
  free(current);
  return head;
}

void destroyUsersInRooms(struct USERSINROOMS *head) {
  struct USERSINROOMS *cursor, *tmp;
  if(head != NULL) {
    cursor = head->next;
    head->next = NULL;
    while(cursor != NULL) {
      tmp = cursor->next;
      free(cursor);
      cursor = tmp;
    }
  }
} 