// ===========================================================================
// RenderTextProcessor.h
// ===========================================================================

class RenderTextProcessor
{
public:
    void setOutputFormat(std::unique_ptr<RenderListStrategy>&&);
    void appendList(const std::vector<std::string>&);
    std::string toString() const;
    void clear();

private:
    std::ostringstream m_oss;
    std::unique_ptr<RenderListStrategy> m_format;
};

// ===========================================================================
// End-of-File
// ===========================================================================
