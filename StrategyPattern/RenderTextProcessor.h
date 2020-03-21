class TextProcessor
{
public:
    void setOutputFormat(const OutputFormat);
    void appendList(const std::vector<std::string>&);
    std::string toString() const;
    void clear();

private:
    std::ostringstream m_oss;
    std::unique_ptr<ListStrategy> m_listStrategy;
};
