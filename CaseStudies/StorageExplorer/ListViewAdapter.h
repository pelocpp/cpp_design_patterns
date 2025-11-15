// ===========================================================================
// ListViewAdapter.h
// ===========================================================================

class ListViewAdapter : public IExplorationObserver
{
private:
    std::shared_ptr<ListView> m_listView;

public:
    ListViewAdapter();
    ~ListViewAdapter();

    void update(std::map<std::string, long>) override;

private:
};

// ===========================================================================
// End-of-File
// ===========================================================================
