using SapphireForum.Application.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace SapphireForum.Application
{
    public partial class Users : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        public IQueryable<SapphireForum.Application.Models.ApplicationUser> RepeaterUserTemplate_GetData()
        {
            ApplicationDbContext context = new ApplicationDbContext();
            return context.Users
                .Include("Posts")
                .OrderByDescending(u => u.Posts.Count).Take(10);
        }

        protected void RedirectToPosts_Click(object sender, CommandEventArgs e)
        {
            string url = this.ClientQueryString + "Posts.aspx?user=" + e.CommandArgument;
            this.Response.Redirect(url);
        }
    }
}