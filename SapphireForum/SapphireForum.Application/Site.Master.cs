using Microsoft.AspNet.Identity.EntityFramework;
using SapphireForum.Application.Models;
using System;
using System.Linq;
using System.Collections.Generic;
using System.Security.Claims;
using System.Security.Principal;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace SapphireForum.Application
{
    public partial class SiteMaster : MasterPage
    {
        private const string AntiXsrfTokenKey = "__AntiXsrfToken";
        private const string AntiXsrfUserNameKey = "__AntiXsrfUserName";
        private string _antiXsrfTokenValue;

        protected void Page_Init(object sender, EventArgs e)
        {
            // The code below helps to protect against XSRF attacks
            var requestCookie = Request.Cookies[AntiXsrfTokenKey];
            Guid requestCookieGuidValue;
            if (requestCookie != null && Guid.TryParse(requestCookie.Value, out requestCookieGuidValue))
            {
                // Use the Anti-XSRF token from the cookie
                _antiXsrfTokenValue = requestCookie.Value;
                Page.ViewStateUserKey = _antiXsrfTokenValue;
            }
            else
            {
                // Generate a new Anti-XSRF token and save to the cookie
                _antiXsrfTokenValue = Guid.NewGuid().ToString("N");
                Page.ViewStateUserKey = _antiXsrfTokenValue;

                var responseCookie = new HttpCookie(AntiXsrfTokenKey)
                {
                    HttpOnly = true,
                    Value = _antiXsrfTokenValue
                };
                if (FormsAuthentication.RequireSSL && Request.IsSecureConnection)
                {
                    responseCookie.Secure = true;
                }
                Response.Cookies.Set(responseCookie);
            }

            Page.PreLoad += master_Page_PreLoad;
        }

        protected void master_Page_PreLoad(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                // Set Anti-XSRF token
                ViewState[AntiXsrfTokenKey] = Page.ViewStateUserKey;
                ViewState[AntiXsrfUserNameKey] = Context.User.Identity.Name ?? String.Empty;
            }
            else
            {
                // Validate the Anti-XSRF token
                if ((string)ViewState[AntiXsrfTokenKey] != _antiXsrfTokenValue
                    || (string)ViewState[AntiXsrfUserNameKey] != (Context.User.Identity.Name ?? String.Empty))
                {
                    throw new InvalidOperationException("Validation of Anti-XSRF token failed.");
                }
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void NavigationMenu_MenuItemDataBound(object sender, MenuEventArgs e)
        {
            if (ShouldRemoveItem(e.Item.Text))
            {
                e.Item.Parent.ChildItems.Remove(e.Item);
            }
        }

        private bool ShouldRemoveItem(string menuText)
        {
            var currentUser = Context.User;

            if (menuText == "Logout" && !currentUser.Identity.IsAuthenticated)
            {
                return true;
            }
            if (menuText == "Manage account" && !currentUser.Identity.IsAuthenticated)
            {
                return true;
            }
            if (menuText == "Create Post" && !currentUser.Identity.IsAuthenticated)
            {
                return true;
            }
            if (menuText == "Login" && currentUser.Identity.IsAuthenticated)
            {
                return true;
            }
            if (menuText == "Register" && currentUser.Identity.IsAuthenticated)
            {
                return true;
            } 
            if (menuText == "Admin" && !currentUser.IsInRole("Admin"))
            {
                return true;
            }

            return false;
        }

        private IEnumerable<SapphireForum.Application.Models.Comment> comments =
            new ApplicationDbContext().Comments.OrderByDescending(c => c.PostDate).Take(10);

        public IEnumerable<SapphireForum.Application.Models.Comment> RepeaterCommentTemplate_GetData()
        {
            return this.comments;
        }

        protected void TimerComments_Tick(object sender, EventArgs e)
        {
            this.comments = new ApplicationDbContext().Comments.OrderByDescending(c => c.PostDate).Take(10);
            this.RepeaterCommentTemplate.DataBind();
        }
    }

}