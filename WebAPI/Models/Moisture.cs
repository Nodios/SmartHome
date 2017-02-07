using System;
using System.Collections.Generic;

namespace SmartHome.Models
{
    public partial class Moisture
    {
        public Guid Id { get; set; }
        public int Moisture1 { get; set; }
        public DateTime MeasuredAt { get; set; }
    }
}
