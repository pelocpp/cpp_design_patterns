namespace StatePattern
{
    class YellowLight : public ITrafficLight
    {
    public:
        void Change(TrafficLight* light) override;
        void ReportState() override;
    };
}
