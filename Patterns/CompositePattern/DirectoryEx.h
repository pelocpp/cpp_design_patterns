// ===========================================================================
// DirectoryEx.h
// ===========================================================================

class DirectoryEx : public IFileComponent {
public:
    // c'tor(s), d'tor
    DirectoryEx() = default;
    DirectoryEx(const std::string& name);
    ~DirectoryEx() = default;

    // getter
    std::string getName();

    // public interface
    void addFileComponent(std::shared_ptr<IFileComponent>);
    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<std::shared_ptr<IFileComponent>> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
