using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jewels.Models
{
    public class Vote
    {
        public int ID { get; set; }
        public double Value { get; set; }
        public string AuthorEmail { get; set; }
    }
}
