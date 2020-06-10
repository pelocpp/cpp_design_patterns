// ===========================================================================
// MediaPlayer02.cpp // Adapter Pattern // Class adapter approach
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ApdaterPatternClassAdapterApproach {

    // interface MediaPlayer
    class MediaPlayer {
    public:
        virtual void play(std::string audioType, std::string fileName) = 0;
    };

    // ===========================================================================

    // concrete class VlcPlayer - new service functionality
    class VlcPlayer {
    public:
        void playVlc(std::string fileName) {
            std::cout << "Playing vlc file: name = " << fileName << std::endl;
        }
    };

    // concrete class Mp4Player - new service functionality
    class Mp4Player {
    public:
        void playMp4(std::string fileName) {
            std::cout << "Playing mp4 file: name = " << fileName << std::endl;
        }
    };

    // ===========================================================================

    // create concrete class 'AudioPlayer' implementing the 'MediaPlayer' interface
    // without new services additions
    class AudioPlayer : public MediaPlayer {
    public:
        void play(std::string audioType, std::string fileName) override;
    };

    void AudioPlayer::play(std::string audioType, std::string fileName) {

        // inbuilt support to play mp3 music files
        if (audioType == std::string("mp3")) {
            std::cout << "Playing mp3 file: name = " << fileName << std::endl;
            return;
        }
        else {
            std::cout << "Invalid media: " << audioType << " format not supported!" << std::endl;
        }
    }

    // ===========================================================================

    // Create adapter class 'MediaAdapter':
    // This implementation uses inheritance: the new adapter inherits behaviors 
    // from both the existing client and from missing / incompatible services.
    // Obviously this approach can only be implemented in programming languages
    // that support multiple inheritance, such as C++.

    class MediaAdapter : public MediaPlayer, public VlcPlayer, public Mp4Player {
    public:
        // c'tor
        MediaAdapter() = default;
        void play(std::string audioType, std::string fileName) override;
    };

    void MediaAdapter::play(std::string audioType, std::string fileName) {

        // traditional support to play mp3 music files
        if (audioType == std::string("mp3")) {
            std::cout << "Playing mp3 file: name = " << fileName << std::endl;
            return;
        }

        // use new inherited service classes to play additional file formats
        if (audioType == std::string("vlc")) {
            playVlc(fileName);
            return;
        }
        else if (audioType == std::string("mp4")) {
            playMp4(fileName);
            return;
        }
        else {
            std::cout << "Invalid media: " << audioType << " format not supported!" << std::endl;
        }
    }
}

// ===========================================================================

/**
 * The client code supports all classes that follow the MediaPlayer interface.
 */
static void clientCode(std::shared_ptr<ApdaterPatternClassAdapterApproach::MediaPlayer>& player) {
    player->play("mp3", "beyond the horizon.mp3");
    player->play("mp4", "alone again.mp4");
    player->play("vlc", "far far away.vlc");
    player->play("avi", "mind me.avi");
}

void test_media_player_02()
{
    using namespace ApdaterPatternClassAdapterApproach;
    std::shared_ptr <MediaPlayer> audioPlayer1 = std::make_shared<AudioPlayer>();
    clientCode(audioPlayer1);
    std::cout << std::endl;
    std::shared_ptr <MediaPlayer> audioPlayer2 = std::make_shared<MediaAdapter>();
    clientCode(audioPlayer2);
    std::cout << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
