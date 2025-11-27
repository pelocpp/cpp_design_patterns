// ===========================================================================
// FolderStrategy.h
// ===========================================================================

class FolderStrategy : public ExplorationStrategy
{
public:
    FolderStrategy() = default;
    ~FolderStrategy() = default;

    void explore(const std::string& path) override;
    void printResults() override;

private:
    void exploreHelper(const std::string& path);
};

// ===========================================================================
// End-of-File
// ===========================================================================
