using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using SapphireForum.Application.Models;
using System.Web.ModelBinding;

namespace SapphireForum.Application
{
    public partial class Posts : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        public IQueryable<PostDTO> lvPosts_GetData(int maximumRows, int startRowIndex, out int totalRowCount, 
            [QueryString]string category, [QueryString]string tag, [QueryString]string user)
        {
            ApplicationDbContext db = new ApplicationDbContext();
            var query = db.Posts.Include("User").Include("Category").Include("Tags").Select(p => new PostDTO()
            {
                Id = p.Id,
                Title = p.Title,
                Text = p.Text,
                Category = p.Category,
                PostDate = p.PostDate,
                CommentsCount = p.Comments.Count,
                Tags = p.Tags,
                User = p.User
            }).AsQueryable();

            if (user != null)
            {
                query = query.Where(p => p.User.UserName == user);
                AllPostsHeading.Text += String.Format(" from <a href='?user={0}' class='btn'>{0}</a>", user);
            }

            if (category != null)
            {
                query = query.Where(p => p.Category.Name == category);
                AllPostsHeading.Text += String.Format(" in <a href='?category={0}' class='btn'>{0}</a>", category);
            }

            if (tag != null)
            {
                query = query.Where(p => p.Tags.Any(t => t.Text == tag));
                AllPostsHeading.Text += String.Format(" tagged as <a href='?tag={0}' class='btn'>{0}</a>", tag);
            }

            query = query.OrderByDescending(p => p.PostDate);
            totalRowCount = query.Count();
            query = query.Skip(startRowIndex).Take(maximumRows);
            return query;
        }
    }
}