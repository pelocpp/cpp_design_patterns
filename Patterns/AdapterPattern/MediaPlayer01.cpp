// ===========================================================================
// MediaPlayer.cpp // Adapter Pattern // Classical Approach (Object Adapter)
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>

namespace ApdaterPatternClassicalApproach {

    // ===========================================================================

    // interface MediaPlayer
    class IMediaPlayer 
    {
    public:
        virtual ~IMediaPlayer() {};

        virtual void play(std::string audioType, std::string fileName) = 0;
    };

    // ---------------------------------------------------------------------------

    // interface IVlcMediaPlayer
    class IVlcMediaPlayer
    {
    public:
        virtual ~IVlcMediaPlayer() {};

        virtual void playVlc(std::string fileName) = 0;
    };

    // interface IMp4MediaPlayer
    class IMp4MediaPlayer
    {
    public:
        virtual ~IMp4MediaPlayer() {};

        virtual void playMp4(std::string fileName) = 0;
    };

    // ===========================================================================

    // class 'AudioPlayer' implementing 'MediaPlayer' interface,
    // no adapter addition
    // 
    class AudioPlayer : public IMediaPlayer
    {
    public:
        void play(std::string audioType, std::string fileName) override;
    };

    void AudioPlayer::play(std::string audioType, std::string fileName)
    {
        // inbuilt support to play mp3 music files
        if (audioType == std::string("mp3")) {
            std::cout << "Playing mp3 file: name = " << fileName << std::endl;
        }
        else {
            std::cout << "Invalid media: " << audioType << " format not supported!" << std::endl;
        }
    }

    // ===========================================================================

    // concrete class VlcPlayer, implementing interface IVlcMediaPlayer
    class VlcPlayer : public IVlcMediaPlayer
    {
    public:
        virtual void playVlc(std::string fileName) override
        {
            std::cout << "Playing vlc file: name = " << fileName << std::endl;
        }
    };

    // concrete class Mp4Player, implementing interface IMp4MediaPlayer
    class Mp4Player : public IMp4MediaPlayer
    {
    public:
        virtual void playMp4(std::string fileName) override
        {
            std::cout << "Playing mp4 file: name = " << fileName << std::endl;
        }
    };

    // ===========================================================================

    // create adapter class implementing the MediaPlayer interface
    // containing two adaptees (VlcPlayer and Mp4Player)

    class MediaAdapter : public IMediaPlayer
    {
    private:
        std::shared_ptr<IVlcMediaPlayer> m_vlcPlayer;
        std::shared_ptr<IMp4MediaPlayer> m_mp4Player;

    public:
        // c'tor
        MediaAdapter(std::string audioType);

        void play(std::string audioType, std::string fileName) override;
    };

    MediaAdapter::MediaAdapter(std::string audioType) 
    {
        if (audioType == std::string("vlc")) {
            m_vlcPlayer = std::make_shared<VlcPlayer>();
        }
        else if (audioType == std::string("mp4")) {
            m_mp4Player = std::make_shared<Mp4Player>();
        }
    }

    void MediaAdapter::play(std::string audioType, std::string fileName)
    {
        if (audioType == std::string("vlc")) {
            m_vlcPlayer->playVlc(fileName);
        }
        else if (audioType == std::string("mp4")) {
            m_mp4Player->playMp4(fileName);
        }
    }

    // ===========================================================================

    // create class 'AudioPlayerExtended'
    // implementing 'MediaPlayer' interface
    // with adapter addition
    class AudioPlayerExtended : public IMediaPlayer
    {
    private:
        std::shared_ptr<MediaAdapter> m_mediaAdapter;

    public:
        void play(std::string audioType, std::string fileName) override;
    };

    void AudioPlayerExtended::play(std::string audioType, std::string fileName)
    {
        if (audioType == std::string("mp3")) {

            // inbuilt support to play mp3 music files
            std::cout << "Playing mp3 file: name = " << fileName << std::endl;
        }
        else if (audioType == std::string("vlc")) {

            // use m_mediaAdapter support to play other file format
            m_mediaAdapter = std::make_shared<MediaAdapter>(audioType);
            m_mediaAdapter->play(audioType, fileName);
        }
        else if (audioType == std::string("mp4")) {

            // use of m_mediaAdapter to play other file format
            m_mediaAdapter = std::make_shared<MediaAdapter>(audioType);
            m_mediaAdapter->play(audioType, fileName);
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
static void clientCode(std::shared_ptr<ApdaterPatternClassicalApproach::IMediaPlayer>& player)
{
    player->play("mp3", "Beyond the horizon.mp3");
    player->play("mp4", "Alone again.mp4");
    player->play("vlc", "Far far away.vlc");
    player->play("avi", "Mind me.avi");
}

void test_media_player_01()
{
    using namespace ApdaterPatternClassicalApproach;
    std::shared_ptr <IMediaPlayer> audioPlayer1{
        std::make_shared<AudioPlayer>()
    };

    clientCode(audioPlayer1);
    std::cout << std::endl;

    std::shared_ptr <IMediaPlayer> audioPlayer2{
        std::make_shared<AudioPlayerExtended>()
    };

    clientCode(audioPlayer2);
    std::cout << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================


//namespace ApdaterPatternClassicalApproach {
//
//    // interface MediaPlayer
//    class IMediaPlayer
//    {
//    public:
//        virtual ~IMediaPlayer() {};
//
//        virtual void play(std::string audioType, std::string fileName) = 0;
//    };
//
//    // interface AdvancedMediaPlayer
//    class IAdvancedMediaPlayer
//    {
//    public:
//        virtual ~IAdvancedMediaPlayer() {};
//
//        virtual void playVlc(std::string fileName) = 0;
//        virtual void playMp4(std::string fileName) = 0;
//    };
//
//    // ===========================================================================
//
//    // concrete class VlcPlayer, implementing interface IAdvancedMediaPlayer
//    class VlcPlayer : public IAdvancedMediaPlayer
//    {
//    public:
//        virtual void playVlc(std::string fileName) override
//        {
//            std::cout << "Playing vlc file: name = " << fileName << std::endl;
//        }
//
//        // do nothing
//        virtual void playMp4(std::string fileName) override {}
//    };
//
//    // concrete class Mp4Player, implementing interface AdvancedMediaPlayer
//    class Mp4Player : public IAdvancedMediaPlayer
//    {
//    public:
//        // do nothing
//        virtual void playVlc(std::string fileName) override {}
//
//        virtual void playMp4(std::string fileName) override
//        {
//            std::cout << "Playing mp4 file: name = " << fileName << std::endl;
//        }
//    };
//
//    // ===========================================================================
//
//    // create adapter class implementing the MediaPlayer interface
//    class MediaAdapter : public IMediaPlayer
//    {
//    private:
//        std::shared_ptr<IAdvancedMediaPlayer> m_advancedMusicPlayer;
//
//    public:
//        // c'tor
//        MediaAdapter(std::string audioType);
//
//        void play(std::string audioType, std::string fileName) override;
//    };
//
//    MediaAdapter::MediaAdapter(std::string audioType)
//    {
//        if (audioType == std::string("vlc")) {
//            m_advancedMusicPlayer = std::make_shared<VlcPlayer>();
//        }
//        else if (audioType == std::string("mp4")) {
//            m_advancedMusicPlayer = std::make_shared<Mp4Player>();
//        }
//    }
//
//    void MediaAdapter::play(std::string audioType, std::string fileName)
//    {
//        if (audioType == std::string("vlc")) {
//            m_advancedMusicPlayer->playVlc(fileName);
//        }
//        else if (audioType == std::string("mp4")) {
//            m_advancedMusicPlayer->playMp4(fileName);
//        }
//    }
//
//    // ===========================================================================
//
//    // create class 'AudioPlayer'
//    // implementing 'MediaPlayer' interface
//    // without adapter addition
//    class AudioPlayer : public IMediaPlayer
//    {
//    public:
//        void play(std::string audioType, std::string fileName) override;
//    };
//
//    void AudioPlayer::play(std::string audioType, std::string fileName)
//    {
//        // inbuilt support to play mp3 music files
//        if (audioType == std::string("mp3")) {
//            std::cout << "Playing mp3 file: name = " << fileName << std::endl;
//        }
//        else {
//            std::cout << "Invalid media: " << audioType << " format not supported!" << std::endl;
//        }
//    }
//
//    // ===========================================================================
//
//    // create class 'AudioPlayerExtended'
//    // implementing 'MediaPlayer' interface
//    // with adapter addition
//    class AudioPlayerExtended : public IMediaPlayer
//    {
//    private:
//        std::shared_ptr<MediaAdapter> m_mediaAdapter;
//
//    public:
//        void play(std::string audioType, std::string fileName) override;
//    };
//
//    void AudioPlayerExtended::play(std::string audioType, std::string fileName)
//    {
//        if (audioType == std::string("mp3")) {
//
//            // inbuilt support to play mp3 music files
//            std::cout << "Playing mp3 file: name = " << fileName << std::endl;
//        }
//        else if (audioType == std::string("vlc") or audioType == std::string("mp4")) {
//
//            // use of m_mediaAdapter is providing support to play other file formats
//            m_mediaAdapter = std::make_shared<MediaAdapter>(audioType);
//            m_mediaAdapter->play(audioType, fileName);
//        }
//        else {
//            std::cout << "Invalid media: " << audioType << " format not supported!" << std::endl;
//        }
//    }
//}
//
//// ===========================================================================
//
///**
//* The client code supports all classes that follow the MediaPlayer interface.
//*/
//static void clientCode(std::shared_ptr<ApdaterPatternClassicalApproach::IMediaPlayer>& player)
//{
//    player->play("mp3", "beyond the horizon.mp3");
//    player->play("mp4", "alone again.mp4");
//    player->play("vlc", "far far away.vlc");
//    player->play("avi", "mind me.avi");
//}
//
//void test_media_player_01()
//{
//    using namespace ApdaterPatternClassicalApproach;
//    std::shared_ptr <IMediaPlayer> audioPlayer1{
//        std::make_shared<AudioPlayer>()
//    };
//    clientCode(audioPlayer1);
//    std::cout << std::endl;
//
//    std::shared_ptr <IMediaPlayer> audioPlayer2{
//        std::make_shared<AudioPlayerExtended>()
//    };
//    clientCode(audioPlayer2);
//    std::cout << std::endl;
//}
