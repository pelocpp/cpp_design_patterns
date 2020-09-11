// ===========================================================================
// RenderListStrategy.h
// ===========================================================================

class RenderListStrategy
{
public:
    virtual ~RenderListStrategy() = default;

    virtual void start(std::ostringstream&) {};
    virtual void addListItem(std::ostringstream&, const std::string& item) {};
    virtual void end(std::ostringstream&) {};
};

// ===========================================================================
// End-of-File
// ===========================================================================
