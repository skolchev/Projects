using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;

namespace SapphireForum.Application.Models
{
    public class Tag
    {
        [Key]
        public int Id { get; set; }

        public string Text { get; set; }
        public virtual ICollection<Post> Posts { get; set; }

        public Tag()
        {
            this.Posts = new HashSet<Post>();
        }
    }
}
