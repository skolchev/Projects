using Gallery.Repositories;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using Gallery.Models;
using System.Globalization;
using Gallery.ASPNetWebAPI.Models;

namespace Gallery.ASPNetWebAPI.Controllers
{
   public class UsersController : BaseApiController
    {
        /*
{
   "username": "Dodo",
   "nickname": "Doncho Minkov",
   "authCode": "6fa9133efe05348e430bd5a4585b595f0cb6cba3"
}
       */
        [HttpPost]
        [ActionName("register")]
        public HttpResponseMessage RegisterUser([FromBody]UserRegisterModel user)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                UsersRepository.CreateUser(user.Username, user.FirstName, user.LastName, user.AuthCode);
                string firstName = string.Empty;
                string lastName = string.Empty;
                var sessionKey = UsersRepository.LoginUser(user.Username, user.AuthCode, out firstName, out lastName);
                return new UserLoggedModel()
                {
                    FirstName = firstName,
                    LastName = lastName,
                    SessionKey = sessionKey
                };
            });
            return responseMsg;
        }

        [HttpPost]
        [ActionName("login")]
        public HttpResponseMessage LoginUser([FromBody]UserLoginModel user)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                string firstName = string.Empty;
                string lastName = string.Empty;

                var sessionKey = UsersRepository.LoginUser(user.Username, user.AuthCode, out firstName, out lastName);
                return new UserLoggedModel()
                {
                    FirstName = firstName,
                    LastName = lastName,
                    SessionKey = sessionKey
                };
            });
            return responseMsg;
        }

        [HttpGet]
        [ActionName("logout")]
        public HttpResponseMessage LogoutUser(string sessionKey)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                UsersRepository.LogoutUser(sessionKey);
            });
            return responseMsg;
        }

       [HttpGet]
       [ActionName("all")]

        public HttpResponseMessage PreviewUsers()
        {
            var responseMsg = this.PerformOperation(() =>
                {
                    var previewUsers = UsersRepository.GetAllUsers();
                    return previewUsers;
                });
            return responseMsg;
        }

        //[HttpGet]
        //[ActionName("scores")]
        //public HttpResponseMessage GetAllUsers(string sessionKey)
        //{
        //    var responseMsg = this.PerformOperation(() =>
        //    {
        //        UsersRepository.LoginUser(sessionKey);
        //        IEnumerable<UserScore> users = UsersRepository.GetAllUsers();

        //        return users;
        //    });
        //    return responseMsg;
        //}
    }
}
