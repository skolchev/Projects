using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Gallery.Models
{
    public class Album
    {
        public Album()
        {
            this.SubAlbums = new HashSet<Album>();
            this.Images = new HashSet<Image>();
        }
        public int ID { get; set; }

        public string Title { get; set; }

        public virtual ICollection<Album> SubAlbums { get; set; }

        public virtual ICollection<Image> Images { get; set; }

        public DateTime? DateCreated { get; set; }

        public DateTime? DateModified { get; set; }
    }
}
