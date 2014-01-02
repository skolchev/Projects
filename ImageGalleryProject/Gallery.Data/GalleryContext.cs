using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gallery.Data
{
    public class GalleryContext : DbContext
    {
        public GalleryContext() :
            base("GalleryDatabase")
        {
        }

        public DbSet<User> Users { get; set; }

        public DbSet<Album> Albums { get; set; }

        public DbSet<Image> Images { get; set; }

        public DbSet<Comment> Comments { get; set; }

        public DbSet<Gallery.Models.Gallery> Galleries { get; set; }
    }
}
