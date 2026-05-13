using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using temperature.Models;
using temperature.Data;
using Microsoft.EntityFrameworkCore;

namespace temperature.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly AppDbContext _context;

        public HomeController(
            ILogger<HomeController> logger,
            AppDbContext context)
        {
            _logger = logger;
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            var data = await _context.SensorData
                .OrderByDescending(x => x.Timestamp)
                .Take(50)
                .ToListAsync();

            return View(data);
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel
            {
                RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier
            });
        }
    }
}