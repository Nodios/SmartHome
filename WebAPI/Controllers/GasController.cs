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
    public class GasController : Controller
    {
        private readonly ApplicationContext DB;

        public GasController(ApplicationContext db)
        {
            this.DB = db;
        }

        // GET api/values
        [HttpGet]
        public IEnumerable<Gas> Get()
        {
            return this.DB.Gas.OrderByDescending(t => t.MeasuredAt).ToList();
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public Gas Get(Guid id)
        {
            return this.DB.Gas.Where(g => g.Id == id).FirstOrDefault();
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]Gas model)
        {
            model.Id = Guid.NewGuid();
            model.MeasuredAt = DateTime.UtcNow;

            this.DB.Gas.Add(model);
            this.DB.SaveChanges();
        }
    }
}
