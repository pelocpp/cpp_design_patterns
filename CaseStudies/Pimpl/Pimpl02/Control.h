// ===========================================================================
// Control.h - Pimpl Idiom
// ===========================================================================

namespace PimplVariant {

    class ControlPimpl;

    class Control {
    private:
        // single property: opaque pointer / pointer to impl
        std::unique_ptr<ControlPimpl> m_pimpl;

    public:
        // public class interface
        Control();
        ~Control();

        void setText(std::string);
        void resize(const int width, const int height);
        void show();
        void hide();
    };
}

// ===========================================================================
// End-of-File
// ===========================================================================
