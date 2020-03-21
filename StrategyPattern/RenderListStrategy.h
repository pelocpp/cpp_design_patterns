class ListStrategy
{
public:
    virtual ~ListStrategy() = default;

    virtual void start(std::ostringstream&) {};
    virtual void addListItem(std::ostringstream&, const std::string& item) {};
    virtual void end(std::ostringstream&) {};
};