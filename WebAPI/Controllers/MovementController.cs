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
    public class MovementController : Controller
    {
        private readonly ApplicationContext DB;

        public MovementController(ApplicationContext db)
        {
            this.DB = db;
        }

        // GET api/values
        [HttpGet]
        public IEnumerable<MovementSensor> Get()
        {
            return this.DB.MovementSensor.OrderByDescending(t => t.MovementDetected).ToList();
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public MovementSensor Get(Guid id)
        {
            return this.DB.MovementSensor.Where(ms => ms.Id == id).FirstOrDefault();
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]MovementSensor model)
        {
            model.Id = Guid.NewGuid();
            
            this.DB.MovementSensor.Add(model);
            this.DB.SaveChanges();
        }
    }
}
