using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SapphireForum.Application.Models
{
    public class PostDTO
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Text { get; set; }
        public DateTime PostDate { get; set; }
        public virtual ApplicationUser User { get; set; }
        public Category Category { get; set; }
        public ICollection<Tag> Tags { get; set; }

        public int CommentsCount { get; set; }
    }
}