// ===========================================================================
// File.h
// ===========================================================================

class File : public IFileComponent {
public:
    File() {}
    File(const std::string& name, const std::string& data);
    ~File() {}

    // getter
    std::string getName();
    std::string getData();

    void display(const std::string&) const override;

private:
    std::string m_name;
    std::string m_data;
};

// ===========================================================================
// End-of-File
// ===========================================================================
