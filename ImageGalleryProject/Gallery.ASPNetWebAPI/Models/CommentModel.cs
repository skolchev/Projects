using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Runtime.Serialization;
using System.Web;

namespace Gallery.ASPNetWebAPI.Models
{
    [DataContract]
    public class CommentModel
    {
        [DataMember(Name = "id")]
        public int ID { get; set; }
        [DataMember(Name = "text")]
        public string Text { get; set; }
        [DataMember(Name = "imageId")]
        public int? ImageId { get; set; }


        public static Expression<Func<Comment, CommentModel>> FromComment
        {
            get
            {
                return x => new CommentModel
                {
                    ID = x.ID,
                    Text = x.Text,
                    ImageId=x.Image.ID         
                };
            }
        }

        public static CommentModel CreateModel(Comment comment)
        {
            return new CommentModel
            {
                ID = comment.ID,
                Text = comment.Text,
                ImageId = comment.Image_ID    
            };
        }

        public virtual Comment CreateCommment()
        {
            return new Comment 
            { 
                ID = this.ID,
                Text = this.Text,
                Image_ID =this.ImageId
            };
        }
    }
}