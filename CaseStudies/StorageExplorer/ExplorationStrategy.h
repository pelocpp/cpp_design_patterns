// ===========================================================================
// ExplorationStrategy.h
// ===========================================================================

/* This class is the base class for the concrete strategy classes:
 * 1. FolderStrategy (obtain file size grouped by folder)
 * 2. FileTypeStrategy (obtain file size grouped by file type)
 */
class ExplorationStrategy : public IExplorationStrategy
{
private:
    std::list<std::shared_ptr<IExplorationObserver>> m_list_observers;

protected:
    // For holding the exploration result.
    // The key-value pair contain the following information:
    // FolderName : Size or FileType : Size
    std::map<std::string, long> m_explorationResult;

public:
    ExplorationStrategy() = default;
    ~ExplorationStrategy() = default;

    /**
    * observer management methods
    */
    void attach(std::shared_ptr<IExplorationObserver> observer) override;
    void detach(std::shared_ptr<IExplorationObserver> observer) override;
    void onFinish() override;
};

// ===========================================================================
// End-of-File
// ===========================================================================
