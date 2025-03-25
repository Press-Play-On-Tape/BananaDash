#pragma once


// - Game play stuff ---------------------

struct StanceDetails {

    int8_t stanceY;
    int8_t foreground;        
    int8_t middleground;        
    int8_t background;        
    
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
        Title,
	Title_End,

    PlayGame_Init,
    PlayGame,
    HighScore_Activate,
    HighScore,
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
        Player_End_RH = Player_Running_Jump_RH_07,

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
        Player_End_LH = Player_Running_Jump_LH_07,

    Player_End,

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



