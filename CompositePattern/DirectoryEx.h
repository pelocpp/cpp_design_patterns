// ===========================================================================
// DirectoryEx.h
// ===========================================================================

// TODO  Das ist noch zu klären ...
class DirectoryEx : public FileComponent  /* , public std::enable_shared_from_this<FileComponent>  */  {
public:
    // c'tor(s), d'tor
    DirectoryEx() = default;
    DirectoryEx(const std::string& name);
    ~DirectoryEx() = default;;

    // getter
    std::string getName();

    // public interface
    void addFileComponent(std::shared_ptr<FileComponent>);
    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<std::shared_ptr<FileComponent>> m_contents;
};

// ===========================================================================
// End-of-File
// ===========================================================================
