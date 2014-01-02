using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.ModelBinding;
using System.Web.UI;
using System.Web.UI.WebControls;
using SapphireForum.Application.Models;

namespace SapphireForum.Application
{
    public partial class Post : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Page_PreRender(object sender, EventArgs e)
        {
            NewComment.Visible = (User.Identity.IsAuthenticated && User.IsInRole("User"));
        }

        public SapphireForum.Application.Models.Post fvPosts_GetItem([QueryString]int? id)
        {
            SapphireForum.Application.Models.Post post = null;

            if (id != null)
            {
                ApplicationDbContext db = new ApplicationDbContext();
                post = db.Posts.Include("User").Include("Tags")
                    .Include("Category").FirstOrDefault(p => p.Id == id);
            }

            return post;

        }

        protected void CommentsList_ItemEditing(object sender, ListViewEditEventArgs e)
        {
            ListView list = sender as ListView;
            if (list != null)
            {
                list.EditIndex = e.NewEditIndex;
            }
        }

        protected void CommentBtn_Click(object sender, EventArgs e)
        {
            using (ApplicationDbContext db = new ApplicationDbContext())
            {
                int postId = int.Parse(Request.QueryString["id"]);
                string text = NewCommentText.Text;
                ApplicationUser user = db.Users.Where(u => u.UserName == User.Identity.Name).FirstOrDefault();

                if (user == null)
                {
                    Page.ModelState.AddModelError("", "You have to be logged in to add a comment");
                    return;
                }
                if (text.Length < 20)
                {
                    Page.ModelState.AddModelError("", "The length of the comment must be more than 20 characters long");
                    return;
                }
                db.Comments.Add(new Comment()
                {
                    PostId = postId,
                    PostDate = DateTime.Now,
                    Text = text,
                    UserId = user.Id
                });

                db.SaveChanges();
                Response.Redirect(Request.RawUrl);
            }
            
        }

        protected void CommentsList_ItemDataBound(object sender, ListViewItemEventArgs e)
        {
            // Edit button
            LinkButton editButton = e.Item.FindControl("EditLinkButton") as LinkButton;
            Comment comment = e.Item.DataItem as Comment;
            if(editButton != null && comment != null){
                if (User.Identity.IsAuthenticated && (User.IsInRole("Admin") || comment.User.UserName.Equals(User.Identity.Name)))
                {
                    editButton.Visible = true;
                }
            }

            // Delete button
            LinkButton deleteButton = e.Item.FindControl("DeleteLinkButton") as LinkButton;
            if (deleteButton != null)
            {
                if (User.IsInRole("Admin"))
                {
                    deleteButton.Visible = true;
                }
            }
        }

        // The id parameter name should match the DataKeyNames value set on the control
        public void CommentsList_UpdateItem(int id)
        {
            SapphireForum.Application.Models.Comment item = null;
            ApplicationDbContext db = new ApplicationDbContext();
            item = db.Comments.Find(id);
            if (item == null)
            {
                // The item wasn't found
                ModelState.AddModelError("", String.Format("Item with id {0} was not found", id));
                return;
            }
            TryUpdateModel(item);
            if (ModelState.IsValid)
            {
                db.SaveChanges();
            }
        }

        // The return type can be changed to IEnumerable, however to support
        // paging and sorting, the following parameters must be added:
        //     int maximumRows
        //     int startRowIndex
        //     out int totalRowCount
        //     string sortByExpression
        public IQueryable<Comment> CommentsList_GetData(int maximumRows, int startRowIndex, out int totalRowCount, [QueryString]int? id)
        {
            IQueryable<Comment> comments = null;
            int total = 0;

            if (id != null)
            {
                ApplicationDbContext db = new ApplicationDbContext();
                comments = db.Comments.Include("User").Where(c => c.PostId == id).OrderBy(c => c.PostDate);
                total = comments.Count();
                comments = comments.Skip(startRowIndex).Take(maximumRows);
            }

            totalRowCount = total;
            return comments;
        }

        // The id parameter name should match the DataKeyNames value set on the control
        public void CommentsList_DeleteItem(int id)
        {
            using (ApplicationDbContext db = new ApplicationDbContext())
            {
                Comment comment = db.Comments.Find(id);
                db.Comments.Remove(comment);
                db.SaveChanges();
            }
        }

        protected void fvPosts_DataBound(object sender, EventArgs e)
        {
            // Edit button
            FormView formView = sender as FormView;
            SapphireForum.Application.Models.Post post = formView.DataItem as SapphireForum.Application.Models.Post;
            if (formView != null && post != null)
            {
                HyperLink editButton = formView.FindControl("EditLinkButton") as HyperLink;
                if (User.IsInRole("Admin"))
                {
                    editButton.Visible = true;
                    editButton.NavigateUrl += post.Id;
                }
            }
        }
    }
}