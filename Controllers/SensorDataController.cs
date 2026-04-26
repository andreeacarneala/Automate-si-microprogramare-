using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using temperature;
using temperature.Data;

[ApiController]
[Route("api/[controller]")]
public class SensorDataController : ControllerBase
{
    private readonly AppDbContext _context;

    public SensorDataController(AppDbContext context)
    {
        _context = context;
    }

    [HttpPost]
    public async Task<IActionResult> Post([FromBody] SensorData data)
    {
        data.Timestamp = DateTime.UtcNow;
        _context.SensorData.Add(data);
        await _context.SaveChangesAsync();
        return Ok(new { message = "Date salvate cu succes", id = data.Id });
    }

    [HttpGet]
    public async Task<IActionResult> Get()
    {
        var data = await _context.SensorData
            .OrderByDescending(x => x.Timestamp)
            .ToListAsync();

        return Ok(data);
    }

    [HttpGet("{id}")]
    public async Task<IActionResult> GetById(int id)
    {
        var data = await _context.SensorData.FindAsync(id);

        if (data == null)
            return NotFound();

        return Ok(data);
    }
}