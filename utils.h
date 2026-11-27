/**
 *Importing main libraries
 */
#include "types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Structure containing all the Gameplay elements
 * Gameplay conditions are initialized in the utils.c
 */
typedef struct Gameplay {
  i8 Default_castaway_number;
  i8 Default_castaway_health;
  i8 Food;
  i8 Water;
  i8 Wood;
  i8 Rope;
  b8 Cistern;
  b8 Fishing_rod;
  b8 Lighthouse_key;
  b8 Lighthouse_oil;
  b8 Lighthouse_lens;
  b8 Reveal_final;
  b8 Reveal_map;
} Gameplay;

void InitializeGameplay(void);
