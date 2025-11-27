// ===========================================================================
// ControlPimpl.h - Pimpl Idiom with separate header file
// ===========================================================================

namespace PimplVariantWithSeparateHeaderFile {

    class ControlPimpl {
    private:
        std::string m_text;
        int m_width;
        int m_height;
        bool m_visible;

        void draw();

    public:
        ControlPimpl() : m_text(""), m_width(0), m_height(0), m_visible(true) {}

        void setText(std::string text);
        void resize(const int width, const int height);
        void show();
        void hide();
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
