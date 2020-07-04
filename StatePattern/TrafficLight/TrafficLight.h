namespace StatePattern
{
    class TrafficLight
    {
    private:
        ITrafficLight* m_state;

    public:
        // public ITrafficLight State{ get; set; }
        //void setState(ITrafficLight* state) { m_state = state; }
        //ITrafficLight* getState() { return m_state; } // WIE SOLL DAS FUNKTIONIEREN ???

        void setState(ITrafficLight* state);
        ITrafficLight* getState();

        void Change();
        void ReportState();
    };
}
