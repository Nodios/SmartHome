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
    public class MoistureController : Controller
    {
        private readonly ApplicationContext DB;

        public MoistureController(ApplicationContext db)
        {
            this.DB = db;
        }

        // GET api/values
        [HttpGet]
        public IEnumerable<Moisture> Get()
        {
            return this.DB.Moisture.OrderByDescending(t => t.MeasuredAt).ToList();
        }

        

        // POST api/values
        [HttpPost]
        public void Post([FromBody]Moisture model)
        {
            model.Id = Guid.NewGuid();
            model.MeasuredAt = DateTime.UtcNow;

            this.DB.Moisture.Add(model);
            this.DB.SaveChanges();
        }
    }
}
