using System;
using System.Collections.Generic;

namespace SmartHome.Models
{
    public partial class WaterLevel
    {
        public Guid Id { get; set; }
        public int MeasuredWaterLevel { get; set; }
        public DateTime MeasuredAt { get; set; }
    }
}
