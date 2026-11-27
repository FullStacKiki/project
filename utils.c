#ifndef UTILS_H
#define UTILS_H
/**
 *Importing stdlib for malloc
 */
#include <stdlib.h>

/**
 * Allocating memory for Gameplay and assigning default values;
 * Some of this values can be changed through the Cheat Menu or during the
 * Gameplay
 */
void InitializeGameplay(void) {
  Gameplay *Settings = malloc(sizeof(Gameplay));
  Settings->Default_castaway_number = 4;
  Settings->Default_castaway_health = 10;
  Settings->Food = 8;
  Settings->Water = 8;
  Settings->Rope = 0;
  Settings->Wood = 0;
  /**
   * Boolean values, hence default value = 0 (false)
   */
  Settings->Cistern = false;
  Settings->Fishing_rod = false;
  Settings->Lighthouse_key = false;
  Settings->Lighthouse_oil = false;
  Settings->Lighthouse_lens = false;
  Settings->Reveal_final = false;
  Settings->Reveal_map = false;
}

#endif
