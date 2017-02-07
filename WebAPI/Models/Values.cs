using System;
using System.Collections.Generic;

namespace SmartHome.Models
{
    public partial class Values
    {
        public IEnumerable<Gas> Gas { get; set; }
        public IEnumerable<Moisture> Moisture { get; set; }
        public IEnumerable<Temperature> Temperature { get; set; }
        public IEnumerable<WaterLevel> WaterLevel { get; set; }
        public IEnumerable<MovementSensor> Movement { get; set; }
    }
}
