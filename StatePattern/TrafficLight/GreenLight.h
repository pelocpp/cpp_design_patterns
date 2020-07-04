namespace StatePattern
{
    class GreenLight : public ITrafficLight
    {
    public:
        void Change(TrafficLight* light) override;
        void ReportState() override;
    };
}
