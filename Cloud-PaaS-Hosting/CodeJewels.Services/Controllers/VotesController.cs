using CodeJewels.DataLayer;
using Jewels.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace CodeJewels.Services.Controllers
{
    public class VotesController : BaseController
    {
        private const double MIN_RATING = 1.5;

        [HttpPost]
        [ActionName("add")]
        public HttpResponseMessage Add(int id, [FromBody] Vote vote)
        {
            var response = this.PerformOperation(() =>
            {
                var context = new CodeJewelsContext();
                using (context)
                {
                    var jewel = context.CodeJewels.Find(id);
                    if (jewel == null)
                    {
                        throw new ArgumentNullException("Cannot find jewel");
                    }
                    jewel.Votes.Add(vote);
                    context.Votes.Add(vote);
                    context.SaveChanges();

                    if (jewel.Votes.Count > 0)
                    {
                        double averageVote = jewel.Votes.Average(v => v.Value);
                        if (averageVote < MIN_RATING)
                        {
                            context.Votes.Remove(vote);
                            context.CodeJewels.Remove(jewel);
                            context.SaveChanges();
                        }
                    }

                    return vote;
                }
            });

            return response;
        }
    }
}
