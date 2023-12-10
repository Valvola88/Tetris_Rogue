#include "Tetris.h"
Music bg_music;
Sound sfx[SFX_LAST];


int TetrisLoadMusic()
{
    InitAudioDevice();

    bg_music = LoadMusicStream("resources/music/bg_music.mp3");
    SetMusicVolume(bg_music, .15f);
    PlayMusicStream(bg_music);

    sfx[SFX_MOVE] = LoadSound("resources/sfx/move.wav");
    sfx[SFX_ROTATE] = LoadSound("resources/sfx/rotate.wav");
    sfx[SFX_LAND] = LoadSound("resources/sfx/softland.wav");
    sfx[SFX_HARDLAND] = LoadSound("resources/sfx/hardland.wav");
    sfx[SFX_TETRIS] = LoadSound("resources/sfx/tetris.wav");
    sfx[SFX_SINGLE] = LoadSound("resources/sfx/single.wav");
    sfx[SFX_HOLD] = LoadSound("resources/sfx/hold.wav");
    sfx[SFX_LVLUP] = LoadSound("resources/sfx/lvlup.wav");

    return 0;
}


int TetrisUnloadMusic()
{

    for(int i = 0; i < SFX_LAST -1; i++)
    {
        UnloadSound(sfx[i]);
    }

    UnloadMusicStream(bg_music);   // Unload music stream buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    return 0;
}

int TetrisPlaySfx(const int sfx_num){

    PlaySound(sfx[sfx_num]);

    return 0;
}
int TetrisLoopBgMusic(){
        if (!IsMusicStreamPlaying(bg_music))
        {
           StopMusicStream(bg_music);
           PlayMusicStream(bg_music);
        }

        UpdateMusicStream(bg_music);
        return 0;

}