#include "Tetris.h"
Music current_music;
Sound sfx[SFX_LAST];

Music bg_musics[MUSIC_LAST];


int TetrisLoadMusic()
{
    InitAudioDevice();

    bg_musics[MUSIC_MAIN] = LoadMusicStream("resources/music/bg_music.mp3");
    bg_musics[MUSIC_MENU] = LoadMusicStream("resources/music/menu_music.mp3");
    bg_musics[MUSIC_LOST] = LoadMusicStream("resources/music/go_music.mp3");
    
    current_music = bg_musics[MUSIC_MENU];
    SetMusicVolume(bg_musics[MUSIC_MAIN], .15f);
    PlayMusicStream(current_music);

    sfx[SFX_MOVE] = LoadSound("resources/sfx/move.wav");
    sfx[SFX_ROTATE] = LoadSound("resources/sfx/rotate.wav");
    sfx[SFX_LAND] = LoadSound("resources/sfx/softland.wav");
    sfx[SFX_HARDLAND] = LoadSound("resources/sfx/hardland.wav");
    sfx[SFX_TETRIS] = LoadSound("resources/sfx/tetris.wav");
    sfx[SFX_SINGLE] = LoadSound("resources/sfx/single.wav");
    sfx[SFX_HOLD] = LoadSound("resources/sfx/hold.wav");
    sfx[SFX_LVLUP] = LoadSound("resources/sfx/lvlup.wav");
    sfx[SFX_GAME_OVER] = LoadSound("resources/sfx/game_over.mp3");

    return 0;
}


int TetrisUnloadMusic()
{
    for(int i = 0; i < SFX_LAST -1; i++)
    {
        UnloadSound(sfx[i]);
    }

    UnloadMusicStream(current_music);   // Unload music stream buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    return 0;
}

int TetrisPlaySfx(const int sfx_num){

    PlaySound(sfx[sfx_num]);

    return 0;
}

int TetrisChangeMusic(const int music)
{

    StopMusicStream(current_music);


    current_music = bg_musics[music];
    //SetMusicVolume(*current_music, .15f);

    PlayMusicStream(current_music);

    return 0;
}

int TetrisLoopBgMusic(){

    if (!IsMusicStreamPlaying(current_music))
    {
        StopMusicStream(current_music);
        PlayMusicStream(current_music);
    }

    UpdateMusicStream(current_music);
    return 0;

}