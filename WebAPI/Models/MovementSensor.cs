using System;
using System.Collections.Generic;

namespace SmartHome.Models
{
    public partial class MovementSensor
    {
        public Guid Id { get; set; }
        public DateTime MovementDetected { get; set; }
    }
}
