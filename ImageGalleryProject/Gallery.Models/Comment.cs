using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;

namespace Gallery.Models
{
    public class Comment
    {
        public int ID { get; set; }

        public string Text { get; set; }

        public virtual User Author { get; set; }

        public int? Image_ID { get; set; }
        [ForeignKey("Image_ID")]
        public virtual Image Image { get; set; }
    }
}
