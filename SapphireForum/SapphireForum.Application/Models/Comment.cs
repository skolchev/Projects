using SapphireForum.Application.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;

namespace SapphireForum.Application.Models
{
    public class Comment
    {
        [Key]
        public int Id { get; set; }

        [Required, MinLength(20)]
        public string Text { get; set; }
        public DateTime PostDate { get; set; }
        public string UserId { get; set; }
        public virtual ApplicationUser User { get; set; }
        public int PostId { get; set; }
        public virtual Post Post { get; set; }
    }
}
