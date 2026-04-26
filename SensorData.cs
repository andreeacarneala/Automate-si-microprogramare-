namespace temperature
{
    public class SensorData
    {
        public int Id { get; set; }  // cheie primară
        public double Temperature { get; set; }
        public DateTime Timestamp { get; set; }
    }
}