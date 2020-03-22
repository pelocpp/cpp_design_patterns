// ===========================================================================
// Directory.h
// ===========================================================================

class Directory : public FileComponent {
public:
    Directory() = default;
    Directory(const std::string& name);

    // getter
    std::string getName();

    // public interface
    void addFileComponent(FileComponent* fc);

    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<FileComponent*> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
