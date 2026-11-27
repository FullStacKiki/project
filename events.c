#ifndef EVENTS_H
#define EVENTS_H
/**
 * Defining Combat constants
 */
#define BOAR_FATAL 3
#define BOAR_DAMAGE 2
#define SNAKE_FATAL 3
#define SNAKE_DAMAGE 3
#define LEECHES 2
#define JAGUAR_FATAL 4
#define JAGUAR_DAMAGE 4
/**
 * Creating a Rolling Dice function so we don't
 * need to rand()%6 + 1 every time.
 */
int RollingDice() {
  srand(NULL) DiceRoll = rand() % 6 + 1;
  return DiceRoll;
}

/**
 * Creating the beach event when someone enters the beach
 */
void beach(Gameplay *Settings, Team head, Expedition_Castaway) {
  i32 DiceRoll = RollingDice();
  switch (DiceRoll) {
  case 1:
    printf("The Castaway enters the beach and has fun playing with the sand "
           "and sea shells\n");
    break;
  case 2:
    Settings->Food = Settings->Food + 2;
    printf("The Castaway enters the beach and catches a crab + 2 food!\n");
    break;
  case 3:
    Settings->Wood = Settings->Wood + 2;
    printf("The Castaway enters the beach and finds a driftwood: + 2 wood!\n");
    break;
  case 4:
    Settings->Rope = Settings->Rope + 1;
    Settings->Wood = Settings->Wood + 1;
    printf("The Castaway enters the beach and finds a floating barrel: + 1 "
           "rope, + 1 food!\n");
    break;
  case 5:
    i32 Damage = RollingDice();
    Expedition_Castaway->Castaway_health =
        Expedition_Castaway->Castaway_health - Damage;
    printf("The Castaway enters the beach and finds some sharp rocks , (rolls "
           "%d) : - %d health (%d -> %d)!\n",
           Damage, Damage, Expedition_Castaway->Castaway_health + Damage,
           Expedition_Castaway->Castaway_health);
    if (Expedition_Castaway->Castaway_health <= 0) {
      RemoveCastaway(*Settings, head, Expedition_Castaway);
      printf("Castaway %d did not survived the expedition!\n",
             Expedition_Castaway);
      Expedition = false;
    }
    break;
  default:
    AddCastaway(*Settings, head);
    printf("Castaway enters the beach and finds another Survivor: + 1 "
           "Castaway!\n");
    break;
  }
}
/**
 * Forest event implementation
 */
void forest(Gameplay *Settings, Team head, Expedition_Castaway) {
  i32 RollDice = RollingDice();
  switch (RollDice) {
  case 1:
    Settings->Food = Settings->Food + 2;
    printf("Castaway enters the forest and finds some fruit tree: + 2 food!\n");
    break;
  case 2:
    Settings->Wood = Settings->Wood + 3;
    printf(
        "Castaway enters the forest and finds some fallen logs: + 3 wood!\n");
    break;
  case 3:
    i32 Coin_flip = rand() % 2 + 1;
    if (Coin_flip == 1) {
      printf("Castaway enters the forests and finds some monkeys, but they ran "
             "away!\n");
    } else if (Coin_flip == 2) {
      Settings->Food = Settings->Food - 2;
      printf("Castaway enters the forest and finds some monkey and they stole "
             "your food!\n");
    }
    break;
  case 4:
    i32 TotalDamage = 0;
    i32 EscapeDice = RollingDice();
    while (EscapeDice < BOAR_FATAL) {
      TotalDamage += BOAR_DAMAGE;
      EscapeDice = RollingDice();
    }
    Expedition_Castaway->Castaway_health -= TotalDamage;
    if (Expedition_Castaway->Castaway_health <= 0) {
      RemoveCastaway(*Settings, head, Expedition_Castaway);
      printf("The Castaway did not survived the Boar Attack!\n");
      expedition = false;
    } else {
      Settings->Food = Settings->Food + 4;
      printf("The Castaway enters the forest and fights a wild Boar, health(%d "
             "-> %d), + 4 food!\n",
             Expedition_Castaway->Castaway_health + TotalDamage,
             Expedition_Castaway->Castaway_health);
    }
    break;
  case 5:
    i32 EscapeDice = RollingDice();
    i32 TotalDamage = 0;
    while (EscapeDice < SNAKE_FATAL) {
      TotalDamage += SNAKE_DAMAGE;
      EscapeDice = RollingDice();
    }
    Expedition_Castaway->Castaway_health -= TotalDamage;
    if (Expedition_Castaway->Castaway_health <= 0) {
      RemoveCastaway(*Settings, head, Expedition_Castaway);
      printf(
          "The Castaway enters the forest, but ended up dying from a snake!\n");
      expedition = false;
    } else {
      printf("The Castaways enters the forest and fights the snake, health (%d "
             "-> %d)!\n",
             Expedition_Castaway->Castaway_health + TotalDamage,
             Expedition_Castaway->Castaway_health);
    }
    break;
  default:
    Settings->Wood = Settings->Wood + 1;
    Expedition_Castaway->Castaway_health =
        Expedition_Castaway->Castaway_health - 2;
    if (Expedition_Castaway->Castaway_health <= 0) {
      RemoveCastaway(*Settings, head, Expedition_Castaway);
      printf("The Castaway enters the forest but could not survived due to "
             "thorny brambles!\n");
      expedition = false;
    } else {
      printf(
          "The Castaway enters the forest but encounters some thorny trambles: "
          "-2 health , +1 wood!\n");
    }
    break;
  }
}
/**
 * Implementing the swamp
 */
void swamp(Gameplay *Settings, Team head, Expedition_Castaway) {
  i32 Rolldice = RollingDice();
  switch (RollDice) {
  case 1:
    Expedition_Castaway->Castaway_health =
        Expedition_Castaway->Castaway_health - LEECHES;
    if (Expedition_Castaway->Castaway_health <= 0) {
      RemoveCastaway(*Settings, head, Expedition_Castaway);
      printf("The Castaway enters the swamp, but could not survive the damage "
             "of the leeches!\n");
      expedition = false;
    } else {
      printf("The Castaway enters the swamp and find some leeches, health(%d "
             "-> %d)!\n",
             Expedition_Castaway->health + LEECHES,
             Expedition_Castaway->Castaway_health);
    }
    break;
  case 2:
    Expedition_Castaway->Castaway_health =
        Expedition_Castaway->Castaway_health - LEECHES;
    if (Expedition_Castaway->Castaway_health <= 0) {
      RemoveCastaway(*Settings, head, Expedition_Castaway);
      printf("The Castaway enters the swamp, but could not survive the damage "
             "of the leeches!\n");
      expedition = false;
    } else {
      printf("The Castaway enters the swamp and find some leeches, health(%d "
             "-> %d)!\n",
             Expedition_Castaway->health + LEECHES,
             Expedition_Castaway->Castaway_health);
    }
    break;
  default:
    Settings->Food = Settings->Food + 1;
    printf("The Castaway enters the swamp and finds some food: +1 Food!\n");
    break;
  }
}
/**
 * Implementation of the shipwreck event
 */
void shiprwreck(Gameplay *Settings, Team head, Expedition_Castaway) {
  Expedition_Castaway->Castaway_health =
      Expedition_Castaway->Castaway_health - 2;
  if (Expedition_Castaway->Castaway_health <= 0) {
    RemoveCastaway(*Settings, head, Expedition_Castaway);
    printf("The Castaway enters the shipwreck, but could not survive the hull "
           "attack!\n");
    expedition = false;
  } else {
    Settings->Lighthouse_oil = true;
    Settings->Food = Settings->Food + 3;
    printf("The Castaway enters the shipwreck and after figthing the hull he "
           "manages to get the Lighthouse oil and +1 wood!\n");
  }
}

b8 fibonacci_sequence(i32 FibonacciInt) {
  i32 t_0 = 0;
  i32 t_1 = 0;
  i32 t_2 = 1;
  t_i = 0;
  b8 fibonacci = 0;
  while (t_i < 500) {
    t_i = t_2 + t_1 + t_0;
    t_2 = t_i;
    t_1 = t_2;
    t_0 = t_1;
    if (FibonacciInt == t_i) {
      fibonacci = 1;
      return fibonacci;
    }
  }
  return fibonacci;
}
/**
 * Implementation of the Coral Cave using the fibonacci sequence above
 */
void Coral_Cave(Gameplay *Settings, Team head, Expedition_Castaway) {
  i32 FibonacciInt = rand() % 500 + 1;
  b8 fibonacciBelong = fibonacci_sequence(FibonacciInt);
  b8 option = 0;
  printf("Does the %d belong to the Fibonacci Sequence (Yes = 1, No = 0): ",
         FibonacciInt);
  scanf("%d", &option);
  if (option == fibonacciBelong) {
    Settings->Lighthouse_lens = true;
    printf("You guessed it right, you just got the Lighthouse Lens!\n");
  } else {
    Expedition_Castaway->Castaway_health =
        Expedition_Castaway->Castaway_health - 3;
    if (Expedition_Castaway->Castaway_health <= 0) {
      RemoveCastaway(*Settings, head, Expedition_Castaway);
      printf("You guessed wrong and you got trapped into the coral cave!\n");
      expedition = false;
    } else {
      printf("You guessed wrong, the coral cave fell and you lost 3 health!\n");
    }
  }
}
/**
 * Implementation of the Jaguar's Den
 */
void Jaguar_Den(Gameplay *Setting, Team head, Expedition_Castaway) {
  i32 DiceRoll = RollingDice();
  i32 TotalDamage = 0;
  while (DiceRoll < JAGUAR_FATAL) {
    TotalDamage += JAGUAR_DAMAGE;
    DiceRoll = RollingDice();
  }
  Expedition_Castaway->Castaway_health =
      Expedition_Castaway->Castaway_health - TotalDamage;
  if (Expedition_Castaway->Castaway_health <= 0) {
    RemoveCastaway(*Settings, head, Expedition_Castaway);
    pritnf("The Castaway enters the Jaguard's Den but could not survive the "
           "fight!\n");
    expedition = false;
  } else {
    Settings->Lighthouse_key = true;
    Settings->Food = Settings->Food + 4;
    printf("The Castaway enters the Jaguar's Den and after a long fight he "
           "wins and earns the Lighthouse Key [health(%d -> %d)] and +4 food",
           Expedition_Castaway->Castaway_health + TotalDamage,
           Expedition_Castaway->Castaway_health);
  }
}
#endif
