using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SapphireForum.Application.Models
{
    public class TagDTO
    {
        public int Id { get; set; }
        public int PostsCount { get; set; }
        public string Text { get; set; }
        public ICollection<Post> Posts { get; set; }
    }
}