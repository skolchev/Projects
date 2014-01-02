using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Runtime.Serialization;
using System.Linq.Expressions;

namespace Gallery.ASPNetWebAPI.Models
{
    [DataContract]
    public class UserLoginModel
    {
        [DataMember(Name = "username")]
        public string Username { get; set; }

        [DataMember(Name = "authCode")]
        public string AuthCode { get; set; }
    }

    [DataContract]
    public class UserPreviewModel
    {
        [DataMember(Name = "username")]
        public string Username { get; set; }

        [DataMember(Name = "firstName")]
        public string FirstName { get; set; }

        [DataMember(Name = "lastName")]
        public string LastName { get; set; }

        public static Expression<Func<User, UserPreviewModel>> FromUser
        {
            get
            {
                return x => new UserPreviewModel
                {
                    FirstName = x.FirstName,
                    LastName = x.LastName,
                    Username = x.Username
                };
            }
        }
    }

    [DataContract]
    public class UserRegisterModel : UserLoginModel
    {
        [DataMember(Name = "firstName")]
        public string FirstName { get; set; }

        [DataMember(Name = "lastName")]
        public string LastName { get; set; }
    }

    [DataContract]
    public class UserLoggedModel
    {
        [DataMember(Name = "sessionKey")]
        public string SessionKey { get; set; }

        [DataMember(Name = "firstName")]
        public string FirstName { get; set; }

        [DataMember(Name = "lastName")]
        public string LastName { get; set; }

    }
    public class UserModel
    {
        public int ID { get; set; }

        public string FirstName { get; set; }

        public string LastName { get; set; }

        public string Username { get; set; }

        internal static UserModel CreateModel(Gallery.Models.User user)
        {
            return new UserModel()
            {
                FirstName = user.FirstName,
                LastName = user.LastName,
                Username = user.Username,
                ID = user.ID
            };
        }

        public Gallery.Models.User CreateAuthor()
        {
            return new User()
            {
                ID = this.ID,
                Username = this.Username,
                FirstName = this.FirstName,
                LastName = this.LastName
            };
        }
    }
}