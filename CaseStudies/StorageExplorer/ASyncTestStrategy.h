// ===========================================================================
// ASyncTestStrategy.h
// ===========================================================================

class ASyncTestStrategy : public ExplorationStrategy
{
public:
    ASyncTestStrategy() = default;
    ~ASyncTestStrategy() = default;

    void explore(const std::string& path) override;
    void printResults() override;

private:
    void exploreHelper(const std::string& path);
};

// ===========================================================================
// End-of-File
// ===========================================================================
