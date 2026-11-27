/**
 *Importing basic libraries for Struct
 */
#include "types.h"
#include "utils.h"
#include <stdio.h>

/**
 * Implementation of the Team using a Linked List,
 * since players can join (e.g Surivors in the beach)
 * or can leave iff they die
 */
typedef struct Team {
  i8 Castaway_Id;
  b8 Alive;
  i8 Castaway_health;
  struct Team *next;
} Team;

Team *InitializeTeam(*Settings);
void RemoveCastaway(*Settings, head, Expedition_Castaway);
void AddCastaway(*Settings, head);
