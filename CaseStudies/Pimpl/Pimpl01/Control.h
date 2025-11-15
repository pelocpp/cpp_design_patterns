// ===========================================================================
// Control.h - No Pimpl Idiom
// ===========================================================================

namespace NoPimplVariant {

    class Control {
    private:
        // properties
        std::string m_text;
        int m_width = 0;
        int m_height = 0;
        bool m_visible = true;

        // private methods
        void draw();

    public:
        // public class interface
        Control();
        void setText(std::string);
        void resize(const int width, const int height);
        void show();
        void hide();
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
