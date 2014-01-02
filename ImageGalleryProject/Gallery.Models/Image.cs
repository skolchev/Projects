using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Gallery.Models
{
    public class Image
    {
        public Image()
        {
            this.Comments = new HashSet<Comment>();
        }
        public int ID { get; set; }

        public string Title { get; set; }

        public DateTime? DateUploaded { get; set; }

        public string Url { get; set; }

        public virtual ICollection<Comment> Comments { get; set; }
    }
}
