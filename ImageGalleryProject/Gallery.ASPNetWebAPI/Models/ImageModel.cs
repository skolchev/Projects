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
    public class ImageModel
    {
        [DataMember(Name = "id")]
        public int ID { get; set; }

        [DataMember(Name = "title")]
        public string Title { get; set; }

        [DataMember(Name = "dateUploaded")]
        public DateTime? DateUploaded { get; set; }

        [DataMember(Name = "url")]
        public string Url { get; set; }

        [DataMember(Name = "size")]
        public double Size { get; set; }

        public static Expression<Func<Image, ImageModel>> FromImage
        {
            get
            {
                return x => new ImageModel
                {
                    ID = x.ID,
                    Title = x.Title,
                    DateUploaded = x.DateUploaded,
                    Url = x.Url,
                };
            }
        }

        public static ImageModel CreateModel(Image image)
        {
            return new ImageModel
            {
                ID = image.ID,
                DateUploaded = image.DateUploaded,
                Title = image.Title,
                Url = image.Url
            };
        }

        public Image CreateImage()
        {
            return new Image
            {
                ID = this.ID,
                Title = this.Title,
                Url = this.Url,
                DateUploaded = this.DateUploaded
            };
        }
    }
}