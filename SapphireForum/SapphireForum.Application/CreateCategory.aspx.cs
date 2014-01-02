using SapphireForum.Application.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace SapphireForum.Application
{
    public partial class CreateCategory : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void Page_PreRender(object sender, EventArgs e)
        {
            this.TextBoxCategoryName.Text = string.Empty;
            this.TextBoxCaragoryDescription.Text = string.Empty;
        }
        protected void ButtonSubmitCaregory_Click(object sender, EventArgs e)
        {
            string name = this.TextBoxCategoryName.Text;
            string description = this.TextBoxCaragoryDescription.Text;
            if (string.IsNullOrWhiteSpace(name) ||
                string.IsNullOrWhiteSpace(description))
            {
                throw new ArgumentException();
            }
            Category category = new Category ()
            { Name = name, Description = description };

            ApplicationDbContext context = new ApplicationDbContext();
            context.Categories.Add(category);
            context.SaveChanges();
        }
    }
}