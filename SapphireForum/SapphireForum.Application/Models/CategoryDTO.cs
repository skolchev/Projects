﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SapphireForum.Application.Models
{
    public class CategoryDTO
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public int PostsCount { get; set; }
    }
}