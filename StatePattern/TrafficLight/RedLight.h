namespace StatePattern
{
    class RedLight : public ITrafficLight
    {
    public:
        void Change(TrafficLight* light) override;
        void ReportState() override;
    };
}
