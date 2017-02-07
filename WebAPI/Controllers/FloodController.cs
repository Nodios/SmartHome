using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using SmartHome.DAL;
using SmartHome.Models;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace SmartHome.Controllers
{
    [Route("api/[controller]")]
    public class FloodController : Controller
    {
        private readonly ApplicationContext DB;

        public FloodController(ApplicationContext db)
        {
            this.DB = db;
        }

        // GET api/values
        [HttpGet]
        public IEnumerable<WaterLevel> Get()
        {
            return this.DB.WaterLevel.OrderByDescending(t => t.MeasuredAt).ToList();
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public WaterLevel Get(Guid id)
        {
            return this.DB.WaterLevel.Where(wl => wl.Id == id).FirstOrDefault();
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]WaterLevel model)
        {
            model.Id = Guid.NewGuid();
            model.MeasuredAt = DateTime.UtcNow;

            this.DB.WaterLevel.Add(model);
            this.DB.SaveChanges();
        }
    }
}
