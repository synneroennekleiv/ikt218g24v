
extern "C"{
    #include "libc/stdint.h"
    #include "libc/stddef.h"
    #include "libc/stdbool.h"
    #include <multiboot2.h>
    #include <monitor.h>
    #include <keyboard.h>
    #include <descriptor_tables.h>
    #include <keyboard.h>
    #include <isr.h>
    #include <memory/memory.h>
    #include <libc/stdio.h>
    #include <system.h>
    #include <libc/stdio.h>
    #include <song/song.h>
    #include <song/frequencies.h>
    #include <pit.h>
}



// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

// Outside of main
SongPlayer* create_song_player() {
    auto* player = new SongPlayer();
    player->play_song = play_song_impl;
    return player;
}

extern "C" int kernel_main(void);

int kernel_main() {
    

   // Trigger interrupts to test handlers
    /*asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    // Enable interrupts
    asm volatile("sti");*/




    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();



    // Main loop
    /*printf("Kernel main loop\n");
    while(true) {
        // Kernel main tasks
    }

    // This part will not be reached
    printf("Done!\n");*/

    // How to play music
    Song* songs[] = {
    	new Song({music_1, sizeof(music_1) / sizeof(Note)})
    };
    uint32_t n_songs = sizeof(songs) / sizeof(Song*);

    SongPlayer* player = create_song_player();

    //player->play_song(songs[0]);

    while(true){
        for(uint32_t i =0; i < n_songs; i++){
            printf("Playing Song...\n");
            player->play_song(songs[i]);
            printf("Finished playing the song.\n");
        }
    }


   /* while(true){
      for(uint32_t i =0; i < n_songs; i++){
          printf("Playing Song...\n");
          player->play_song(songs[i]);
          printf("Finished playing the song.\n");
      }
    };*/

    while(1);


    return 0;
}