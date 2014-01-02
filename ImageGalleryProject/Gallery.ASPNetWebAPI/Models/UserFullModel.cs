using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

namespace Gallery.ASPNetWebAPI.Models
{
    [DataContract]
    public class UserFullModel : UserModel
    {
        public UserFullModel()
        {
            this.Galleries = new HashSet<GalleryModel>();
        }

        [DataMember(Name = "authCode")]
        public string AuthCode { get; set; }

        [DataMember(Name = "galleries")]
        public ICollection<GalleryModel> Galleries { get; set; }
    }
}