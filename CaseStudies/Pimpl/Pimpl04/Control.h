// ===========================================================================
// Control.h - Pimpl Idiom with separate header file
// ===========================================================================

namespace PimplVariantWithSeparateHeaderFile {

    class ControlPimpl;

    class Control {
    private:
        // single property: opaque pointer / pointer to impl
        std::unique_ptr<ControlPimpl> m_pimpl;

    public:
        // public class interface
        Control();
        ~Control();

        Control(Control&& op) noexcept;           // move semantics
        Control& operator=(Control&&) noexcept;   // move semantics
        Control(const Control&);                  // copy semantics
        Control& operator=(const Control&);       // copy semantics

        void setText(std::string);
        void resize(const int width, const int height);
        void show();
        void hide();
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
