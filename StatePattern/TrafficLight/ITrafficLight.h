namespace StatePattern
{
    class TrafficLight;  // TODO Kann das wieder weg ...

    class ITrafficLight
    {
    public:
        virtual void Change(TrafficLight* light) = 0;
        virtual void ReportState() = 0;
    };
}
