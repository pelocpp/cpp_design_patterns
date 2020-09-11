// ===========================================================================
// RenderHtmlListStrategy.h
// ===========================================================================

class RenderHtmlListStrategy : public RenderListStrategy
{
public:
    void start(std::ostringstream&) override;
    void end(std::ostringstream&) override;
    void addListItem(std::ostringstream&, const std::string&) override;
};

// ===========================================================================
// End-of-File
// ===========================================================================
