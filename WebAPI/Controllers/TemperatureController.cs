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
    public class TemperatureController : Controller
    {
        private readonly ApplicationContext DB;

        public TemperatureController(ApplicationContext db)
        {
            this.DB = db;
        }

        // GET api/values
        [HttpGet]
        public IEnumerable<Temperature> Get()
        {
            var test = this.DB.Temperature.OrderByDescending(t => t.MeasuredAt).ToList();

            return test;
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public Temperature Get(Guid id)
        {
            return this.DB.Temperature.Where(ms => ms.Id == id).FirstOrDefault();
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]Temperature model)
        {
            model.Id = Guid.NewGuid();
            model.MeasuredAt = DateTime.UtcNow;
            
            this.DB.Temperature.Add(model);
            this.DB.SaveChanges();
        }
    }
}
