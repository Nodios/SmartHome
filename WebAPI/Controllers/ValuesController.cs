using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using SmartHome.DAL;
using SmartHome.Models;

namespace SmartHome.Controllers
{
    [Route("api/[controller]")]
    public class ValuesController : Controller
    {
        private ApplicationContext DB;

        public ValuesController(ApplicationContext db){
            this.DB = db;
        }

        // GET api/values
        [HttpGet]
        public Values Get()
        {
            Values model = new Values();

            model.Gas = this.DB.Gas.OrderByDescending(t => t.MeasuredAt).ToList();
            model.Moisture = this.DB.Moisture.OrderByDescending(t => t.MeasuredAt).ToList();
            model.Movement = this.DB.MovementSensor.OrderByDescending(t => t.MovementDetected).ToList();
            model.Temperature = this.DB.Temperature.OrderByDescending(t => t.MeasuredAt).ToList();
            model.WaterLevel = this.DB.WaterLevel.OrderByDescending(t => t.MeasuredAt).ToList();

            return model;
        }
    }
}
