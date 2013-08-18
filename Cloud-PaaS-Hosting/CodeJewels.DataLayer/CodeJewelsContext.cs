using Jewels.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeJewels.DataLayer
{
    public class CodeJewelsContext : DbContext
    {
        public DbSet<CodeJewel> CodeJewels { get; set; }
        public DbSet<Category> Categories { get; set; }
        public DbSet<Vote> Votes { get; set; }

        public CodeJewelsContext()
            : base("CodeJewelsDb")
        {
        }
    }
}
