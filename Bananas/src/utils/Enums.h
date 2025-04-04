#pragma once


// - Game play stuff ---------------------

struct StanceDetails {

    int8_t stanceY;
    int8_t foreground;        
    int8_t middleground;        
    int8_t background;        
    
};


enum class EntityType : uint8_t {
    None,
    Player,
    Barrel,
};

enum class ItemType : uint8_t {
    None,
    Banana,
    Banana_Hidden,
    Puff,
};


enum class GameState : uint8_t {

    SplashScreen_Start,
        SplashScreen_00 = SplashScreen_Start,
        SplashScreen_01,
        SplashScreen_02,
        SplashScreen_03,
    SplashScreen_End,

    Title_Init,
    Title_Start,
        Title_Play_Game = Title_Start,
        Title_Sounds,
        Title_Highs,
	Title_End,

    PlayGame_Init,
    PlayGame,
    HighScore_Activate,
    HighScore,
};

inline GameState &operator++(GameState &c) {
  c = static_cast<GameState>( static_cast<uint8_t>(c) + 1 );
  return c;
}

inline GameState operator++(GameState &c, int) {
  GameState result = c;
  ++c;
  return result;
}

inline GameState &operator--( GameState & c ) {
  c = static_cast<GameState>( static_cast<uint8_t>(c) - 1 );
  return c;
};

inline GameState operator--( GameState & c, int ) {
  GameState result = c;
  --c;
  return result;
};

enum Stance : uint16_t {

    Player_Start,

        Player_Start_RH = Player_Start,
            Player_Idle_RH = Player_Start,
            Player_Walk_RH_00,
            Player_Walk_RH_01,
            Player_Walk_RH_02,
            Player_Walk_RH_03,
            Player_Standing_Jump_RH_00,
            Player_Standing_Jump_RH_01,
            Player_Standing_Jump_RH_02,
            Player_Standing_Jump_RH_03,
            Player_Standing_Jump_RH_04,
            Player_Standing_Jump_RH_05,
            Player_Standing_Jump_RH_06,
            Player_Standing_Jump_RH_07,
            Player_Running_Jump_RH_00,
            Player_Running_Jump_RH_01,
            Player_Running_Jump_RH_02,
            Player_Running_Jump_RH_03,
            Player_Running_Jump_RH_04,
            Player_Running_Jump_RH_05,
            Player_Running_Jump_RH_06,
            Player_Running_Jump_RH_07,
            Player_Climbing_Vine_Up_RH_00,
            Player_Climbing_Vine_Up_RH_01,
            Player_Climbing_Vine_Up_RH_02,
            Player_Climbing_Vine_Up_RH_03,
            Player_Climbing_Vine_Down_RH_00,
            Player_Climbing_Vine_Down_RH_01,
            Player_Climbing_Vine_Down_RH_02,
            Player_Climbing_Vine_Down_RH_03,

            Player_Falling_1L_A_RH_00,
            Player_Falling_1L_A_RH_01,
            Player_Falling_1L_A_RH_02,
            Player_Falling_1L_A_RH_03,
            Player_Falling_1L_A_RH_04,
            Player_Falling_1L_A_RH_05,
            Player_Falling_1L_A_RH_06,
            Player_Falling_1L_A_RH_07,

            Player_Falling_1L_B_RH_00,
            Player_Falling_1L_B_RH_01,
            Player_Falling_1L_B_RH_02,
            Player_Falling_1L_B_RH_03,
            Player_Falling_1L_B_RH_04,
            Player_Falling_1L_B_RH_05,
            Player_Falling_1L_B_RH_06,
            Player_Falling_1L_B_RH_07,

        Player_End_RH = Player_Falling_1L_B_RH_07,

        Player_Start_LH,
            Player_Idle_LH = Player_Start_LH,

            Player_Walk_LH_00,
            Player_Walk_LH_01,
            Player_Walk_LH_02,
            Player_Walk_LH_03,

            Player_Standing_Jump_LH_00,
            Player_Standing_Jump_LH_01,
            Player_Standing_Jump_LH_02,
            Player_Standing_Jump_LH_03,
            Player_Standing_Jump_LH_04,
            Player_Standing_Jump_LH_05,
            Player_Standing_Jump_LH_06,
            Player_Standing_Jump_LH_07,

            Player_Running_Jump_LH_00,
            Player_Running_Jump_LH_01,
            Player_Running_Jump_LH_02,
            Player_Running_Jump_LH_03,
            Player_Running_Jump_LH_04,
            Player_Running_Jump_LH_05,
            Player_Running_Jump_LH_06,
            Player_Running_Jump_LH_07,

            Player_Climbing_Vine_Up_LH_00,
            Player_Climbing_Vine_Up_LH_01,
            Player_Climbing_Vine_Up_LH_02,
            Player_Climbing_Vine_Up_LH_03,

            Player_Climbing_Vine_Down_LH_00,
            Player_Climbing_Vine_Down_LH_01,
            Player_Climbing_Vine_Down_LH_02,
            Player_Climbing_Vine_Down_LH_03,     

            Player_Falling_1L_A_LH_00,
            Player_Falling_1L_A_LH_01,
            Player_Falling_1L_A_LH_02,
            Player_Falling_1L_A_LH_03,
            Player_Falling_1L_A_LH_04,
            Player_Falling_1L_A_LH_05,
            Player_Falling_1L_A_LH_06,
            Player_Falling_1L_A_LH_07,

            Player_Falling_1L_B_LH_00,
            Player_Falling_1L_B_LH_01,
            Player_Falling_1L_B_LH_02,
            Player_Falling_1L_B_LH_03,
            Player_Falling_1L_B_LH_04,
            Player_Falling_1L_B_LH_05,
            Player_Falling_1L_B_LH_06,
            Player_Falling_1L_B_LH_07,

        Player_End_LH = Player_Falling_1L_B_LH_07,

    Player_End = Player_End_LH,

    Enemy_Start,

        Enemy_Start_RH = Enemy_Start,

            Enemy_Idle_RH = Enemy_Start_RH,
            Enemy_Walking_RH_00,
            Enemy_Walking_RH_01,
            Enemy_Walking_RH_02,
            Enemy_Walking_RH_03,
            Enemy_Falling_1L_RH_00,
            Enemy_Falling_1L_RH_01,
            Enemy_Falling_1L_RH_02,
            Enemy_Falling_1L_RH_03,
            Enemy_Falling_1L_RH_04,
            Enemy_Falling_1L_RH_05,
            Enemy_Falling_1L_RH_06,
            Enemy_Falling_1L_RH_07,

        Enemy_End_RH = Enemy_Falling_1L_RH_07,

        Enemy_Start_LH,

            Enemy_Idle_LH = Enemy_Start_LH,
            Enemy_Walking_LH_00,
            Enemy_Walking_LH_01,
            Enemy_Walking_LH_02,
            Enemy_Walking_LH_03,
            Enemy_Falling_1L_LH_00,
            Enemy_Falling_1L_LH_01,
            Enemy_Falling_1L_LH_02,
            Enemy_Falling_1L_LH_03,
            Enemy_Falling_1L_LH_04,
            Enemy_Falling_1L_LH_05,
            Enemy_Falling_1L_LH_06,
            Enemy_Falling_1L_LH_07,

        Enemy_End_LH = Enemy_Falling_1L_LH_07,

        Enemy_Fall_1L_00,
        Enemy_Fall_1L_01,
        Enemy_Fall_1L_02,
        Enemy_Fall_1L_03,
        Enemy_Fall_1L_04,
        Enemy_Fall_1L_05,
        Enemy_Fall_1L_06,

    None,

};


enum class Movements : uint8_t {
    None,
    Up = 1,
    Down = 2, 
    Left = 4,
    Right = 8,
    Jump = 16,
    Reverse = 32,
    JumpUp = 128,
    ThrowKey = 128,  
};

enum class Direction : uint8_t {
    Left = 1,
    Right = 2,
    None = 4
};



