﻿using SapphireForum.Application.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SapphireForum.Application.Models
{
    public class Category
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public virtual ICollection<Post> Posts { get; set; }

        public Category()
        {
            this.Posts = new HashSet<Post>();
        }
    }
}