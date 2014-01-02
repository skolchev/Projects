using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using SapphireForum.Application.Models;

namespace SapphireForum.Application.Admin
{
    public partial class Post : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            
        }

        protected void Page_PreRender(object sender, EventArgs e)
        {
            int postId = 0;
            if (!Page.IsPostBack)
            {
                if (!string.IsNullOrEmpty(Request.QueryString["id"]))
                {
                    string postIdString = Request.QueryString["id"];
                    postId = int.Parse(postIdString);
                }
            }

            var context = new ApplicationDbContext();
            if (postId != 0)
            {
                var post = context.Posts.Find(postId);
                this.TextBoxTitle.Text = post.Title;
                this.TextBoxText.Text = post.Text;
                this.HiddenFieldPostDate.Value = post.PostDate.ToString();
                foreach (var tag in context.Tags)
                {
                    this.TextBoxTags.Text += tag.Text + " ";
                }

                var categories = context.Categories.ToList();

                this.DropDownCategories.DataSource = categories;
                this.DropDownCategories.DataTextField = "Name";
                this.DropDownCategories.DataValueField = "Id";
                this.DropDownCategories.DataBind();

                this.DropDownCategories.Items.FindByText(post.Category.Name).Selected = true;
            }
        }

        
        protected void EditPost_Click(object sender, EventArgs e)
        {
            ApplicationDbContext context = new ApplicationDbContext();

            //Getting current User
            var user = context.Users.FirstOrDefault(u => u.UserName == User.Identity.Name);

            //Getting selected Categoty
            var selectedCategory = this.DropDownCategories.SelectedItem.Text;
            var selectedCategoryEntity = context.Categories.FirstOrDefault(c => c.Name == selectedCategory);

            string postIdString = Request.QueryString["id"];
            int postId = int.Parse(postIdString);

            var post = context.Posts.Find(postId);

            post.Title = this.TextBoxTitle.Text;
            post.Text = this.TextBoxText.Text;
            post.Category = selectedCategoryEntity;
            context.SaveChanges();

            //Getting all Tags
            var allTagsEntites = GetAllTags(this.TextBoxTags.Text);
            //post.Tags = null;
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

            Response.Redirect("~/Posts.aspx");
        }

        private ICollection<Tag> GetAllTags(string tagsFromTextBox)
        {
            //splitted tags from textBox
            string[] splittedTags = tagsFromTextBox.ToLower().Split(new char[]{' '}, StringSplitOptions.RemoveEmptyEntries);

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