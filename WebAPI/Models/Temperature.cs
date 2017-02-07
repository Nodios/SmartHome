using System;
using System.Collections.Generic;

namespace SmartHome.Models
{
    public partial class Temperature
    {
        public Guid Id { get; set; }
        public int MeasuredTemperature { get; set; }
        public int? Humidity { get; set; }
        public DateTime MeasuredAt { get; set; }
    }
}
