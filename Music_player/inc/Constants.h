#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>
#include <utility>

namespace Constants {

    enum class PlaybackState { 
        STOPPED, 
        PLAYING, 
        PAUSED 
    };

    //Constants
    inline constexpr char WHITESPACE = ' ';
    inline constexpr char TAB = '\t';
    inline constexpr char FULL_STOP = '.';
    inline constexpr char NEW_LINE = '\n';
    inline constexpr char CHARACTER_B = 'b';
    inline constexpr char CHARACTER_P = 'p';
    inline const std::string PLAYLIST_FILE_PATH = "playlists.txt";
    inline const std::string SONGS_FOLDER_PATH = "Songs";
    inline const std::string MARKER = ">> ";
    inline const std::string MULTIPLE_SPACES = "   ";
    inline const std::string MP3_EXTENSION = ".mp3";

    // Music Player
    inline const std::string MSG_WELCOME = 
    "\n========================================\n"
    "         Welcome to Music Player        \n"
    "========================================\n";

    inline const std::string MSG_MAIN_MENU = 
    "\n===============OPERATIONS===============\n"
        "1. My Playlists\n"
        "2. Display All Songs\n"
        "3. Search\n"
        "4. Pause/Resume\n"
        "5. Exit\n"
    "========================================\n";

    inline const std::string MSG_INPUT_CHOICE = "\nEnter your choice: ";
    inline const std::string MSG_INVALID_CHOICE = "Invalid Choice! Please choose an option from menu.\n";
    inline const std::string MSG_PROGRAM_EXIT = "\nThank you for using the application!\n";

    inline const std::string MSG_SEARCH_PROMPT  = "Enter song name: ";        
    inline const std::string MSG_SEARCH_EMPTY   = "Song not found.";          
    inline const std::string MSG_SEARCH_FOUND   = "Found: ";                  
    inline const std::string MSG_SEARCH_ACTION  = "p. Play    b. Back\nEnter choice: ";  

    // Input Handler
    inline const std::string WHITESPACE_CHARS = " \t\r\n";
    inline const std::string EMPTY_STRING = "";
    inline const std::string MSG_INVALID_INTEGER = "Invalid Input. Please enter an integer: ";
    inline const std::string MSG_EMPTY_INPUT = "Input cannot be empty! Enter again: ";

    //Persistance Manager
    inline const std::string PLAYLIST_PREFIX = "PLAYLIST:";
    inline const std::string SEPARATOR = "|";

    //Library
    const std::string MSG_LIBRARY_HEADER  = "\n========================================\n"
                                            "           MUSIC LIBRARY\n"
                                            "========================================\n";
    const std::string MSG_LIBRARY_EMPTY   = "No songs found in library.";
    const std::string MSG_LIBRARY_PROMPT  = "Enter number to play (0 to go back): ";

    //Playlist Controller
    inline const std::string MSG_PLAYLIST_MENU =
    "\n===============PLAYLIST OPERATIONS===============\n"
    "1. Open Playlist\n"
    "2. Create Playlist\n"
    "3. Delete Playlist\n"
    "4. Back\n"
    "========================================\n";

    inline const std::string MSG_PLAYLIST_DETAIL_MENU =
    "\n===============SONGS OPERATIONS===============\n"
    "1. Play/Pause\n"
    "2. Next\n"
    "3. Previous\n"
    "4. Add Song\n"
    "5. Remove Song\n"
    "6. Move Song Upward\n"
    "7. Move Song Downward\n"
    "8. Back\n"
    "========================================\n";

    inline const std::string MSG_PLAYLISTS_HEADER = "============ MY PLAYLISTS ============\n";
    inline const std::string MSG_SONGS_HEADER = "============ SONGS ============\n";
    inline const std::string MSG_NO_PLAYLISTS = "No playlists found.\n";
    inline const std::string MSG_PLAYLIST_EMPTY = "Playlist is empty.\n";
    inline const std::string MSG_ENTER_PLAYLIST_NAME = "\nEnter playlist name: ";
    inline const std::string MSG_ENTER_SONG_NAME = "Enter song name: ";
    inline const std::string MSG_CANNOT_MOVE = "Cannot move song in that direction.";
    inline const std::string MSG_PLAYLIST_CREATED = "Playlist created successfully.\n";
    inline const std::string MSG_PLAYLIST_ALREADY_EXISTS= "Playlist already exists.\n";
    inline const std::string MSG_PLAYLIST_DELETED = "Playlist deleted successfully.\n";
    inline const std::string MSG_PLAYLIST_NOT_FOUND = "Playlist not found.\n";
    inline const std::string MSG_PAUSED = "Paused.\n";
    inline const std::string MSG_SONG_ADDED = "Song added successfully.\n";
    inline const std::string MSG_SONG_ALREADY_EXISTS = "Song already exists in playlist.\n";
    inline const std::string MSG_SONG_REMOVED = "Song removed successfully.\n";
    inline const std::string MSG_SONG_NOT_FOUND = "Song not found.\n";
    inline const std::string MSG_SONG_MOVED_UP = "Song moved upward.\n";
    inline const std::string MSG_SONG_MOVED_DOWN = "Song moved downward.\n";
    inline const std::string MSG_SONG_ALREADY_TOP = "Song is already at the top.\n";
    inline const std::string MSG_SONG_ALREADY_BOTTOM = "Song is already at the bottom.\n";
    inline const std::string MSG_NOW_PLAYING = "Now playing: ";
    inline const std::string MSG_INVALID_INDEX = "Invalid number. Please try again.\n";
    inline const std::string MSG_PAUSED_SONG = "Song is paused!\n";
    inline const std::string MSG_PLAYING_SONG = "Playing the Song!\n";
    inline const std::string MSG_ADDED = " [Added]";

    //Application
    inline const std::string MSG_PLAY_PROMPT = "\nPress p to play or b to go back: ";
    inline const std::string MSG_FOUND = "Found: ";

    // Audio errors
    inline const std::string MSG_AUDIO_ENGINE_FAILED = "Failed to initialize audio engine.\n";
    inline const std::string MSG_AUDIO_LOAD_FAILED = "Failed to load song: ";
    inline const std::string MSG_AUDIO_START_FAILED = "Failed to start song: ";

    // Persistence errors
    inline const std::string MSG_FILE_SAVE_FAILED = "Could not open file for saving: ";
    inline const std::string MSG_FILE_LOAD_FAILED = "Could not open file for loading: ";
}

#endif
