using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jewels.Models
{
    public class CodeJewel
    {
        public int ID { get; set; }
        public virtual Category Category { get; set; }
        public string AuthorEmail { get; set; }
        public string Source { get; set; }
        public ICollection<Vote> Votes { get; set; }

        public CodeJewel()
        {
            this.Votes = new HashSet<Vote>();
        }
    }
}
