using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Gallery.ASPNetWebAPI.Models;
using Gallery.Data;

namespace Gallery.ASPNetWebAPI.Repositories
{
    public class GalleryRepository
    {
        internal static IEnumerable<GalleryModel> GetAll(string sessionKey)
        {

            var context = new GalleryContext();
            var result = context.Galleries.Select(GalleryModel.FromGallery).ToList();

            return result;
        }

        internal static GalleryFullModel GetSingle(string username)
        {
            var context = new GalleryContext();
            using (context)
            {
                var gallery =
                    from g in context.Galleries.Include("User").Include("Albums").Include("Images")
                    where g.User.Username == username
                    select new GalleryFullModel
                    {
                        ID = g.ID,
                        Name = g.Name,
                        Albums =
                            from album in g.Albums
                            where g.User.Username == username
                            select new AlbumModel
                            {
                                DateCreated = album.DateCreated,
                                DateModified = album.DateModified,
                                ID = album.ID,
                                Title = album.Title
                            },
                        Images =
                            from i in g.Images
                            where g.User.Username == username
                            select new ImageModel
                            {
                                DateUploaded = i.DateUploaded,
                                ID = i.ID,
                                Title = i.Title,
                                Url = i.Url
                            }
                    };

                return gallery.FirstOrDefault();
            }
        }

        public static void CreateGallery(string name, string sessionKey)
        {
            using (GalleryContext context = new GalleryContext())
            {
                var dbGallery = new Gallery.Models.Gallery()
                {
                    Name = name
                };

                var userId = context.Users.Where(u => u.SessionKey == sessionKey).FirstOrDefault().ID;
                context.Users.Find(userId).Galleries.Add(dbGallery);
                context.SaveChanges();
            }
        }
    }
}