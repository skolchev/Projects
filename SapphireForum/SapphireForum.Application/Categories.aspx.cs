using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using SapphireForum.Application.Models;

namespace SapphireForum.Application
{
    public partial class Categories : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        public IQueryable<CategoryDTO> RepeaterCategories_GetData(int maximumRows, int startRowIndex, out int totalRowCount)
        {
            ApplicationDbContext context = new ApplicationDbContext();
            var query = from category in context.Categories
                select new CategoryDTO()
                {
                    Name = category.Name,
                    Description = category.Description,
                    PostsCount = category.Posts.Count
                };

            query = query.OrderByDescending(c => c.Name);
            totalRowCount = query.Count();
            query = query.Skip(startRowIndex).Take(maximumRows);
            return query;
        }


        protected void RedirectToPosts_Click(object sender, CommandEventArgs e)
        {
            string categoryName = e.CommandArgument.ToString();
            this.Response.Redirect("Posts.aspx?category=" + categoryName);
        }
    }
}