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
    public class AlbumPreviewModel
    {
        [DataMember(Name = "title")]
        public string Title { get; set; }


        public static Expression<Func<Album, AlbumPreviewModel>> FromAlbum
        {
            get
            {
                return x => new AlbumPreviewModel
                {
                    Title = x.Title,
                };
            }
        }
    }

    public class AlbumModel
    {
        [DataMember(Name = "id")]
        public int ID { get; set; }

        [DataMember(Name = "title")]
        public string Title { get; set; }

        [DataMember(Name = "dateCreated")]
        public DateTime? DateCreated { get; set; }

        [DataMember(Name = "dateModified")]
        public DateTime? DateModified { get; set; }

        [DataMember(Name = "size")]
        public double Size { get; set; }

        internal static AlbumModel CreateModel(Gallery.Models.Album album)
        {
            return new AlbumModel()
            {
                Title = album.Title,
                DateCreated = album.DateCreated,
                DateModified = album.DateModified,
                ID = album.ID,
            };
        }

        public Gallery.Models.Album CreateAlbum()
        {
            return new Album()
            {
                ID = this.ID,
                DateCreated = this.DateCreated,
                DateModified = this.DateModified,
                Title = this.Title,
            };
        }
    }

}