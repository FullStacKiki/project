#ifndef TEAM_H
#define TEAM_H
/**
 * Importing necessary libraries or some other code blocks
 * e.g Stdlib (Malloc) and utils.c for *Settings data
 */
#include "utils.c"
#include <stdlib.h>
/**
 * Initializing Team Stats usign the Settings
 * This need to happen when the game starts so that the player
 * cannot modify anymore their number or hp.
 */
Team *InitializeTeam(*Settings) {
  /**
   * Iterating to the number of castaways and assigning default values
   */
  Team *head = NULL;
  Team *tail = NULL;
  for (i32 i = 1; i < Settings->Default_castaway_number + 1; ++i) {
    Team *temp = malloc(sizeof(Team));
    temp->Castaway_Id = i;
    temp->Alive = true;
    temp->Castaway_health = Settings->Default_castaway_health;
    temp->next = NULL;
    /**
     * If there is no head then temp = head, otherwise is just
     * an ordindary part of the node
     */
    if (!head) {
      head = temp;
    } else {
      tail->next = temp;
    }
    tail = temp;
  }
  return head;
}
/**
 * Removing castaway from the linked list in case the
 */
void RemoveCastaway(Gameplay *Settings, Team *head, i32 Expedition_Castaway) {
  for (Team *curr = head; curr != NULL; curr = curr->next) {
    if (Expedition_Castaway == curr->Castaway_Id &&
        curr->Castaway_health <= 0) {
      curr->Alive = 0;
      free(curr);
    }
  }
}

/**
 * Adding the castaway in special occasion e.g Beach survivor.
 */
void AddCastaway(Gameplay *Settings, Team *head) {
  for (Team *curr = head; curr != NULL; curr = curr->next) {
    if (curr->next == NULL) {
      /**
       * Whenever there's a new joing castaway, scroll the list,
       * when the castaway->next points to nothing (NULL), then we allocate
       * a new castaway and put that the tail points to this new entry.
       * Last but not least we add all of his statistics
       */
      Settings->Default_castaway_number++;
      Team *Survivor = malloc(sizeof(Team));
      curr->next = Survivor;
      Survivor->next = NULL;
      Survivor->Id = Default_castaway_number;
      Survivor->Alive = true;
      Survivor->Castaway_health = 6;
      break;
    }
  }
}

#endif
