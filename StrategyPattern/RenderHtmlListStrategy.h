class HtmlListStrategy : public ListStrategy
{
public:
    void start(std::ostringstream&) override;
    void end(std::ostringstream&) override;
    void addListItem(std::ostringstream&, const std::string&) override;
};