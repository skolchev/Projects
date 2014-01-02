using SapphireForum.Application.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace SapphireForum.Application
{
    public partial class CreatePost : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void CreatePostLinkButton_Click(object sender, EventArgs e)
        {
            ApplicationDbContext context = new ApplicationDbContext();

            //Getting current User
            var user = context.Users.FirstOrDefault(u => u.UserName == User.Identity.Name);

            //Getting selected Categoty
            var selectedCategory = this.CategoriesDropDownList.SelectedValue;
            var selectedCategoryEntity = context.Categories.FirstOrDefault(c => c.Name == selectedCategory);

            //Creating Post
            SapphireForum.Application.Models.Post post = new SapphireForum.Application.Models.Post()
            {
                User = user,
                Title = this.PostTitleTextBox.Text,
                Text = this.PostTextTextBox.Text,
                PostDate = DateTime.Now,
                Category = selectedCategoryEntity,
            };
            context.Posts.Add(post);
            context.SaveChanges();

            //Getting all Tags
            var allTagsEntites = GetAllTags(this.PostTagsTextBox.Text);
            var tagsInDb = context.Tags;

            //Adding Tags to Post
            foreach (Tag tag in allTagsEntites)
            {
                var existingTag = context.Tags.FirstOrDefault(t => t.Text == tag.Text);

                if (existingTag == null)
                {
                    post.Tags.Add(tag);
                }
                else
                {
                    post.Tags.Add(existingTag);
                }
            }
            context.SaveChanges();

            Response.Redirect("Post.aspx?id=" + post.Id);
        }

        public string[] CategoriesDropList_GetData()
        {
            ApplicationDbContext context = new ApplicationDbContext();
            var categories = context.Categories.Select(c => c.Name).OrderBy(c => c);
            return categories.ToArray();
        }

        private ICollection<Tag> GetAllTags(string tagsFromTextBox)
        {
            //splitted tags from textBox
            string[] splittedTags = tagsFromTextBox.ToLower().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

            ICollection<Tag> tags = new HashSet<Tag>();

            for (int i = 0; i < splittedTags.Length; i++)
            {
                tags.Add(new Tag()
                {
                    Text = splittedTags[i],
                });
            }

            return tags;
        }
    }
}