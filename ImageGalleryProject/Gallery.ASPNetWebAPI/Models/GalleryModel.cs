using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Runtime.Serialization;
using System.Web;

namespace Gallery.ASPNetWebAPI.Models
{
    [DataContract]
    public class GalleryModel
    {
        [DataMember(Name = "id")]
        public int ID { get; set; }
        [DataMember(Name = "name")]
        public string Name { get; set; }

        public static Expression<Func<Gallery.Models.Gallery, GalleryModel>> FromGallery
        {
            get
            {
                return x => new GalleryModel
                {
                    ID = x.ID,
                    Name = x.Name
                };
            }
        }
    }
}