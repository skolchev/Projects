using SapphireForum.Application.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;

namespace SapphireForum.Application.Models
{
    public class Post
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public string Title { get; set; }

        [Required]
        public string Text { get; set; }

        public DateTime PostDate { get; set; }
        public string UserId { get; set; }
        public virtual ApplicationUser User { get; set; }
        public int CategoryId { get; set; }
        public virtual Category Category { get; set; }
        public virtual ICollection<Tag> Tags { get; set; }
        public virtual ICollection<Comment> Comments { get; set; }

        public Post()
        {
            this.Tags = new HashSet<Tag>();
            this.Comments = new HashSet<Comment>();
        }
    }
}
