// ===========================================================================
// Directory.h
// ===========================================================================

class Directory : public IFileComponent {
public:
    // c'tor(s)
    Directory() {};
    Directory(const std::string& name);

    // getter
    std::string getName();

    // public interface
    void addFileComponent(IFileComponent*);
    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<IFileComponent*> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
