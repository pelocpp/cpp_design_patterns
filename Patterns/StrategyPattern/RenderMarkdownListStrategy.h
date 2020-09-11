// ===========================================================================
// RenderMarkdownListStrategy.h
// ===========================================================================

class RenderMarkdownListStrategy : public RenderListStrategy
{
public:
    void addListItem(std::ostringstream&, const std::string&) override;
};

// ===========================================================================
// End-of-File
// ===========================================================================
