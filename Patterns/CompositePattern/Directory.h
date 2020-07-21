// ===========================================================================
// Directory.h
// ===========================================================================

class Directory : public FileComponent {
public:
    // c'tor(s)
    Directory() = default;
    Directory(const std::string& name);

    // getter
    std::string getName();

    // public interface
    void addFileComponent(FileComponent*);
    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<FileComponent*> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
