using System;
using System.Collections.Generic;

namespace SmartHome.Models
{
    public partial class Gas
    {
        public Guid Id { get; set; }
        public int? Gas1 { get; set; }
        public int? Co2 { get; set; }
        public int? Co { get; set; }
        public DateTime MeasuredAt { get; set; }
    }
}
