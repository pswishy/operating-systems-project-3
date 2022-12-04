#include "list.h"
#define DEFAULT_ROOM "Lobby"
#include <time.h>

struct USER *head = NULL;
struct ROOM *roomhead = NULL;
struct USERSINROOMS *usersinroomhead = NULL;

int main(int argc, char **argv) {
  roomhead = insertFirstRoom(roomhead,DEFAULT_ROOM);
  roomhead = insertFirstRoom(roomhead,"Room A");
  roomhead = insertFirstRoom(roomhead,"Room B");
  roomhead = insertFirstRoom(roomhead,"Room C");
  printListRoom(roomhead);
  printf("\n-------------------------------\n");
  
  head = insertFirstU(head, 28, "Evolone");
  head = insertFirstU(head, 23328, "Jaiyla");
  head = insertFirstU(head, 177, "Edith");
  printListU(head); 
  printf("\n-------------------------------\n");
  
  usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room A");
  usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room B");
  usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room C");
  usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room A");
  usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room D");
  usersinroomhead = insertFirstUsersInRooms(usersinroomhead,"Room B");
  printListUsersInRooms(usersinroomhead);
  
  return 0;
}