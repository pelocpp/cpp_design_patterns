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
    virtual void playVlc(std::string fileName) = 0;
    virtual void playMp4(std::string fileName) = 0;
};

// ===========================================================================

// concrete class AdvancedMediaPlayer, implementing interface AdvancedMediaPlayer
class VlcPlayer : public AdvancedMediaPlayer {
public:
    void playVlc(std::string fileName) override {
        std::cout << "Playing vlc file: name = " << fileName << std::endl;
    }

    // do nothing
    void playMp4(std::string fileName) override {}
};

// concrete class AdvancedMediaPlayer, implementing interface AdvancedMediaPlayer
class Mp4Player : public AdvancedMediaPlayer {
public:
    // do nothing
    void playVlc(std::string fileName) override {}


    void playMp4(std::string fileName) override {
        std::cout << "Playing mp4 file: name = " << fileName << std::endl;
    }
};

// ===========================================================================

// create adapter class implementing the MediaPlayer interface
class MediaAdapter : public MediaPlayer {
private:
    std::shared_ptr<AdvancedMediaPlayer> m_advancedMusicPlayer;

public:
    // c'tor
    MediaAdapter(std::string audioType);

    void play(std::string audioType, std::string fileName) override;
};

MediaAdapter::MediaAdapter(std::string audioType) {

    if (audioType == std::string("vlc")) {
        m_advancedMusicPlayer = std::make_shared<VlcPlayer>();
    }
    else if (audioType == std::string("mp4")) {
        m_advancedMusicPlayer = std::make_shared<Mp4Player>();
    }
}

void MediaAdapter::play(std::string audioType, std::string fileName) {

    if (audioType == std::string("vlc")) {
        m_advancedMusicPlayer->playVlc(fileName);
    }
    else if (audioType == std::string("mp4")) {
        m_advancedMusicPlayer->playMp4(fileName);
    }
}

// ===========================================================================

// create concrete class 'AudioPlayer' implementing the 'MediaPlayer' interface

class AudioPlayer : public MediaPlayer {
private:
    std::shared_ptr<MediaAdapter> m_mediaAdapter;

public:
    void play(std::string audioType, std::string fileName) override;
};

void AudioPlayer::play(std::string audioType, std::string fileName) {

    // inbuilt support to play mp3 music files
    if (audioType == std::string("mp3")) {
        std::cout << "Playing mp3 file: name = " << fileName << std::endl;
        return;
    }

    // use m_mediaAdapter is providing support to play other file formats
    if (audioType == std::string("vlc") or audioType == std::string("mp4")) {

        m_mediaAdapter = std::make_shared<MediaAdapter>(audioType);
        m_mediaAdapter->play(audioType, fileName);
        return;
    }
    else {
        std::cout << "Invalid media: " << audioType << " format not supported!" << std::endl;
    }
}
// ===========================================================================

void test_media_player()
{
    AudioPlayer audioPlayer;

    audioPlayer.play("mp3", "beyond the horizon.mp3");
    audioPlayer.play("mp4", "alone again.mp4");
    audioPlayer.play("vlc", "far far away.vlc");
    audioPlayer.play("avi", "mind me.avi");
}

// ===========================================================================
// End-of-File
// ===========================================================================
