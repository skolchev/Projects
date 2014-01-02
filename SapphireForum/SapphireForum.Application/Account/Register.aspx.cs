using Microsoft.AspNet.Identity;
using Microsoft.AspNet.Identity.EntityFramework;
using Microsoft.AspNet.Identity.Owin;
using SapphireForum.Application.Models;
using System;
using System.Linq;
using System.Web;
using System.Web.UI;

namespace SapphireForum.Application.Account
{
    public partial class Register : Page
    {
        protected void CreateUser_Click(object sender, EventArgs e)
        {
            string userName = UserName.Text;
            var manager = new AuthenticationIdentityManager(new IdentityStore(new ApplicationDbContext()));
            ApplicationUser user = new ApplicationUser() 
            { 
                UserName = userName,
            };
            IdentityResult result = manager.Users.CreateLocalUser(user, Password.Text);
            if (result.Success) 
            {
                CreateDefaultRoleForRegisteringUser(user);
                manager.Authentication.SignIn(Context.GetOwinContext().Authentication, user.Id, isPersistent: false);
                OpenAuthProviders.RedirectToReturnUrl(Request.QueryString["ReturnUrl"], Response);
            }
            else 
            {
                ErrorMessage.Text = result.Errors.FirstOrDefault();
            }
        }

        private void CreateDefaultRoleForRegisteringUser(ApplicationUser user)
        {
            var context = new ApplicationDbContext();

            UserRole role = new UserRole()
            {
                RoleId = "2",
                UserId = user.Id,
            };

            context.UserRoles.Add(role);
            context.SaveChanges();
        }
    }
}