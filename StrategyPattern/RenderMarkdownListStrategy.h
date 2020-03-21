class MarkdownListStrategy : public ListStrategy
{
public:
    void addListItem(std::ostringstream&, const std::string&) override;
};