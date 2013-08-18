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
    public class CodeJewelsController : BaseController
    {
        [HttpPost]
        [ActionName("add")]
        public HttpResponseMessage AddCodeJewel([FromBody] CodeJewel jewel)
        {
            var response = this.PerformOperation(() => 
            {
                var context = new CodeJewelsContext();
                using (context)
                {
                    context.CodeJewels.Add(jewel);
                    context.SaveChanges();
                    return jewel;
                }
            });
            
            return response;
        }

        [HttpGet]
        [ActionName("all")]
        public HttpResponseMessage GetAll()
        {
            var response = this.PerformOperation(() =>
            {
                var context = new CodeJewelsContext();
                using (context)
                {
                    var jewels = context.CodeJewels.ToList();
                    return jewels;
                }
            });
            return response;
        }

        [HttpGet]
        [ActionName("getBySource")]
        public HttpResponseMessage GetBySource(string source)
        {
            var response = this.PerformOperation(() =>
            {
                var context = new CodeJewelsContext();
                using (context)
                {
                    var jewels = context.CodeJewels
                        .Include("Votes")
                        .Include("Categories")
                        .Where(s => s.Source == source).ToList();

                    return jewels;
                }
            });

            return response;
        }

        [HttpGet]
        [ActionName("getByCategory")]
        public HttpResponseMessage GetByCategory(string category)
        {
            var response = this.PerformOperation(() =>
            {
                var context = new CodeJewelsContext();
                using (context)
                {
                    var jewels = context.CodeJewels
                        .Include("Votes")
                        .Include("Categories")
                        .Where(c => c.Category.Name == category).ToList();

                    return jewels;
                }
            });

            return response;
        }
    }
}
