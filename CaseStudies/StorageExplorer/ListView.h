// ===========================================================================
// ListView.h
// ===========================================================================

/* 
 * Simple console based ListView control
 */
class ListView
{
private:
    int m_cols;
    std::vector<std::string> m_titles;
    std::vector<std::vector<std::string>> m_data;

public:
    // c'tor
    ListView();

    void setColumns(int);
    void setColumnHeader(std::initializer_list<std::string> titles);
    void addData(std::vector<std::string>);
    void show();
};

// ===========================================================================
// End-of-File
// ===========================================================================
