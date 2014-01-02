using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace Gallery.ASPNetWebAPI.Models
{
    [DataContract]
    public class ImageFullModel : ImageModel
    {
        public ImageFullModel()
        {
            this.Comments = new HashSet<CommentModel>();
        }

        [DataMember(Name = "comments")]
        public ICollection<CommentModel> Comments { get; set; }
    }
}