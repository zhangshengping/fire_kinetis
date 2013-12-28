

#include "LED_CORE.h"


void Light1_turn()
{
    Light1_ptor |= 1<<Light1_pin;
}

void Light2_turn()
{
  Light2_ptor |= 1<<Light2_pin;
}

void Light3_turn()
{
  Light3_ptor |= 1<<Light3_pin;
}

void Light4_turn()
{
  Light4_ptor |= 1<<Light4_pin;
}

