#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Forecast transforms Castform in weather from an opponent's move")
{
    u32 move;
    PARAMETRIZE { move = MOVE_SUNNY_DAY; }
    PARAMETRIZE { move = MOVE_RAIN_DANCE; }
    PARAMETRIZE { move = MOVE_HAIL; }
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}

SINGLE_BATTLE_TEST("Forecast transforms Castform in weather from its own move")
{
    u32 move;
    PARAMETRIZE { move = MOVE_SUNNY_DAY; }
    PARAMETRIZE { move = MOVE_RAIN_DANCE; }
    PARAMETRIZE { move = MOVE_HAIL; }
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}

DOUBLE_BATTLE_TEST("Forecast transforms Castform in weather from a partner's move")
{
    u32 move;
    PARAMETRIZE { move = MOVE_SUNNY_DAY; }
    PARAMETRIZE { move = MOVE_RAIN_DANCE; }
    PARAMETRIZE { move = MOVE_HAIL; }
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerRight, move); }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, playerLeft);
        MESSAGE("Castform transformed!");
    }
}

DOUBLE_BATTLE_TEST("Forecast transforms all Castforms present in weather")
{
    u32 move;
    PARAMETRIZE { move = MOVE_SUNNY_DAY; }
    PARAMETRIZE { move = MOVE_RAIN_DANCE; }
    PARAMETRIZE { move = MOVE_HAIL; }
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
    } WHEN {
        TURN { MOVE(playerRight, move); }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, playerLeft);
        MESSAGE("Castform transformed!");
        ABILITY_POPUP(opponentLeft, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, opponentLeft);
        MESSAGE("Foe Castform transformed!");
        ABILITY_POPUP(playerRight, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, playerRight);
        MESSAGE("Castform transformed!");
        ABILITY_POPUP(opponentRight, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, opponentRight);
        MESSAGE("Foe Castform transformed!");
    }
}

SINGLE_BATTLE_TEST("Forecast transforms Castform in weather from an ability")
{
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KYOGRE) { Ability(ABILITY_DRIZZLE); };
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}

SINGLE_BATTLE_TEST("Forecast transforms Castform in primal weather")
{
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KYOGRE) { Ability(ABILITY_DRIZZLE); Item(ITEM_BLUE_ORB); };
    } WHEN {
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PRIMORDIAL_SEA);
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}

SINGLE_BATTLE_TEST("Forecast transforms Castform back to normal when weather expires")
{
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RAIN_DANCE); }
        TURN { }
        TURN { }
        TURN { }
        TURN { }
        TURN { }
    } SCENE {
        // transforms
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
        // back to normal
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}

SINGLE_BATTLE_TEST("Forecast transforms Castform back to normal when Sandstorm is active")
{
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RAIN_DANCE); }
        TURN { MOVE(player, MOVE_SANDSTORM); }
    } SCENE {
        // transforms
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
        // back to normal
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}

SINGLE_BATTLE_TEST("Forecast transforms Castform on switch-in")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RAIN_DANCE); }
        TURN { SWITCH(player, 1); }
    } SCENE {
        // turn 1
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAIN_DANCE, player);
        // turn 2
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}

SINGLE_BATTLE_TEST("Forecast transforms Castform when weather changes")
{
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RAIN_DANCE); }
        TURN { MOVE(player, MOVE_SUNNY_DAY); }
    } SCENE {
        // transforms
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
        // transforms again
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Castform transformed!");
    }
}
