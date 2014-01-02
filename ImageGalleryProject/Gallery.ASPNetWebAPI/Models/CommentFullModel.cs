using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace Gallery.ASPNetWebAPI.Models
{
    [DataContract]
    public class CommentFullModel : CommentModel
    {
        [DataMember(Name = "author")]
        public UserModel Author { get; set; }

        internal static CommentFullModel CreateComment(Comment comment)
        {
            return new CommentFullModel()
            {
                ID = comment.ID,
                Text = comment.Text,
                Author = UserModel.CreateModel(comment.Author)
            };
        }

        public override Comment CreateCommment()
        {
            return new Comment
            {
                ID = this.ID,
                Text = this.Text,
                Author = this.Author.CreateAuthor()
            };
        }
    }
}