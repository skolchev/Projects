using SapphireForum.Application.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace SapphireForum.Application
{
    public partial class Tags : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        public IQueryable<TagDTO> TagsRepeater_GetData()
        {
            ApplicationDbContext context = new ApplicationDbContext();
            var tags = context.Tags.Include("Posts").Select(t => new TagDTO()
            {
                Id = t.Id,
                Text = t.Text,
                Posts = t.Posts,
                PostsCount = t.Posts.Count
            }).OrderByDescending(t => t.PostsCount);

            return tags;
        }

        protected void TagLinkButton_Command(object sender, CommandEventArgs e)
        {
            string tagName = e.CommandArgument.ToString();
            Response.Redirect("Posts.aspx?tag=" + tagName);
        }
    }
}