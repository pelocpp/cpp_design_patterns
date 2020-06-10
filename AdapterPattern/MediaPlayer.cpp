// ===========================================================================
// MediaPlayer.cpp // Adapter Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

// interface MediaPlayer
class MediaPlayer {
public:
    virtual void play(std::string audioType, std::string fileName) = 0;
};

// interface AdvancedMediaPlayer
class AdvancedMediaPlayer {
public:
    virtual void playVLC(std::string fileName) = 0;
    virtual void playMp4(std::string fileName) = 0;
};

// concrete class AdvancedMediaPlayer, implementing interface AdvancedMediaPlayer
class VlcPlayer : public AdvancedMediaPlayer {
public:
    void playVLC(std::string fileName) override {
        std::cout << "Playing vlc file: name = " << fileName << std::endl;
    }

    // do nothing
    void playMp4(std::string fileName) override {}
};

// concrete class AdvancedMediaPlayer, implementing interface AdvancedMediaPlayer
class Mp4Player : public AdvancedMediaPlayer {
public:
    // do nothing
    void playVLC(std::string fileName) override {}


    void playMp4(std::string fileName) override {
        std::cout << "Playing mp4 file: name = " << fileName << std::endl;
    }
};

// create adapter class implementing the MediaPlayer interface
class MediaAdapter : public MediaPlayer {
public:

    void play(std::string audioType, std::string fileName) override {}
};



void test_media_player() {

}

// ===========================================================================
// End-of-File
// ===========================================================================
