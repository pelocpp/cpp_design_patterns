// ===========================================================================
// MediaPlayer01.cpp // Adapter Pattern // Classical Approach (Object Adapter)
// ===========================================================================

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <print>

namespace AdapterPattern {

    // ---- Target interface ------------------------------------------------------
    class IMediaPlayer {
    public:
        IMediaPlayer() = default;
        virtual ~IMediaPlayer() = default;

        IMediaPlayer(const IMediaPlayer&) = delete;
        IMediaPlayer& operator=(const IMediaPlayer&) = delete;

        virtual void play(std::string_view audioType, std::string_view fileName) = 0;
    };

    // ---- Adaptee interfaces ----------------------------------------------------
    class IVlcMediaPlayer {
    public:
        virtual ~IVlcMediaPlayer() = default;
        virtual void playVlc(std::string_view fileName) = 0;
    };

    class IMp4MediaPlayer {
    public:
        virtual ~IMp4MediaPlayer() = default;
        virtual void playMp4(std::string_view fileName) = 0;
    };

    // ---- Adaptees --------------------------------------------------------------
    class VlcPlayer final : public IVlcMediaPlayer {
    public:
        void playVlc(std::string_view fileName) override {
            std::cout << "Playing vlc file: name = " << fileName << '\n';
            std::println("Playing vlc file: name = {}", fileName);
        }
    };

    class Mp4Player final : public IMp4MediaPlayer {
    public:
        void playMp4(std::string_view fileName) override {
            std::cout << "Playing mp4 file: name = " << fileName << '\n';
            std::println("Playing mp4 file: name = {}", fileName);
        }
    };

    // ---- Adapters: one per adaptee, adaptee injected ---------------------------
    class VlcAdapter final : public IMediaPlayer {
    public:
        explicit VlcAdapter(std::unique_ptr<IVlcMediaPlayer> adaptee)
            : m_adaptee{ std::move(adaptee) } 
        {}

        void play(std::string_view /*audioType*/, std::string_view fileName) override {
            m_adaptee->playVlc(fileName);
        }

    private:
        std::unique_ptr<IVlcMediaPlayer> m_adaptee;
    };

    class Mp4Adapter final : public IMediaPlayer {
    public:
        explicit Mp4Adapter(std::unique_ptr<IMp4MediaPlayer> adaptee)
            : m_adaptee{ std::move(adaptee) }
        {}

        void play(std::string_view /*audioType*/, std::string_view fileName) override {
            m_adaptee->playMp4(fileName);
        }

    private:
        std::unique_ptr<IMp4MediaPlayer> m_adaptee;
    };

    // ---- Players ---------------------------------------------------------------
    class AudioPlayer final : public IMediaPlayer {
    public:
        void play(std::string_view audioType, std::string_view fileName) override {
            if (audioType == "mp3") {
                std::cout << "Playing mp3 file: name = " << fileName << '\n';
                std::println("Playing mp3 file: name = {}", fileName);
            }
            else {
                std::cout << "Invalid media: " << audioType << " format not supported!\n";
                std::println("Invalid media: {} format not supported!", audioType);
            }
        }
    };

    class AudioPlayerExtended final : public IMediaPlayer {
    public:
        AudioPlayerExtended()
        {
            m_adapters.emplace("vlc", std::make_unique<VlcAdapter>(std::make_unique<VlcPlayer>()));
            m_adapters.emplace("mp4", std::make_unique<Mp4Adapter>(std::make_unique<Mp4Player>()));
        }

        void play(std::string_view audioType, std::string_view fileName) override {
            if (audioType == "mp3") {
                std::cout << "Playing mp3 file: name = " << fileName << '\n';
                std::println("Playing mp3 file: name = {}", fileName);
            }
            else if (const auto it = m_adapters.find(audioType); it != m_adapters.end()) {
                it->second->play(audioType, fileName);
            }
            else {
                std::cout << "Invalid media: " << audioType << " format not supported!\n";
                std::println("Invalid media: {} format not supported!", audioType);
            }
        }

    private:
        // std::less<> enables lookup by string_view without creating a std::string
        std::map<std::string, std::unique_ptr<IMediaPlayer>, std::less<>> m_adapters;
    };

} // namespace AdapterPattern

namespace {

    void clientCode(AdapterPattern::IMediaPlayer& player) {
        player.play("mp3", "Beyond the horizon.mp3");
        player.play("mp4", "Alone again.mp4");
        player.play("vlc", "Far far away.vlc");
        player.play("avi", "Mind me.avi");
    }
}

void test_media_player_01() {

    using namespace AdapterPattern;

    AudioPlayer basic;
    clientCode(basic);
    std::println();

    AudioPlayerExtended extended;
    clientCode(extended);
}

// ===========================================================================
// End-of-File
// ===========================================================================
