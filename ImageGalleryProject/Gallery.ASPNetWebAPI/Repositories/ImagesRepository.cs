using Gallery.ASPNetWebAPI.Models;
using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Gallery.ASPNetWebAPI.Repositories
{
    public class ImagesRepository
    {
        public static IEnumerable<ImageModel> GetAllImages()
        {
            using (var context = new Gallery.Data.GalleryContext())
            {
                var allGaleries = context.Galleries.Include("Images").ToList();
                
                if (allGaleries == null)
                {
                    throw new ServerErrorException("No galleries available");
                }
                List<ImageModel> images = new List<ImageModel>();

                foreach (var imagesCollection in allGaleries)
                {
                    images.AddRange(ParseImagesToModel(imagesCollection.Images));
                }

                return images;
            }
        }

        public static IEnumerable<ImageModel> GetAllImagesByUserID(int id)
        {
            using (var context = new Gallery.Data.GalleryContext())
            {
                var user = context.Users.Include("Galleries").Include("Galleries.Images")
                    .FirstOrDefault(u => u.ID == id);
                if (user == null)
                {
                    throw new ServerErrorException("Invalid user");
                }

                var gallery = user.Galleries;
                if (gallery.Count == 0)
                {
                    return new List<ImageModel>();
                }
                var userImages = ParseImagesToModel(gallery.FirstOrDefault().Images);
                return userImages;
            }
        }

        public static IEnumerable<ImageModel> GetAllImagesByUsername(string username)
        {
            using (var context = new Gallery.Data.GalleryContext())
            {
                var user = context.Users.Include("Galleries").Include("Galleries.Images")
                    .FirstOrDefault(u => u.Username == username);
                if (user == null)
                {
                    throw new ServerErrorException("Invalid user");
                }

                var gallery = user.Galleries;
                if (gallery.Count == 0)
                {
                    return new List<ImageModel>();
                }
                var userImages = ParseImagesToModel(gallery.FirstOrDefault().Images);
                return userImages;
            }

        }

        public static ImageModel GetImageByID(int id)
        {
            using (var context = new Gallery.Data.GalleryContext())
            {
                var img =
                    from i in context.Images
                    where i.ID == id
                    select i;

                Image image = img.FirstOrDefault();
                return new ImageModel
                {
                    ID = image.ID,
                    Title = image.Title,
                    Url = image.Url,
                    DateUploaded = image.DateUploaded
                };
            }
        }

        public static void AddImage(ImageModel image, int? albumID, int userID)
        {
            using (var context = new Gallery.Data.GalleryContext())
            {
                User user = context.Users.FirstOrDefault(u => u.ID == userID);
                if (user == null)
                {
                    throw new ServerErrorException("Invalid session");
                }

                Image newImage = new Image
                {
                    Title = image.Title,
                    Url = image.Url,
                    DateUploaded = image.DateUploaded
                };

                context.Users.Find(userID).Galleries.First().Images.Add(newImage);
                if (albumID != null)
                {
                    context.Users.Find(userID).Galleries.First().Albums
                        .First(a => a.ID == albumID).Images.Add(newImage);
                   
                }

                context.Images.Add(newImage);
                context.SaveChanges();
            }
        }

        public static void DeleteImage(int imageID, int userID)
        {
            using (var context = new Gallery.Data.GalleryContext())
            {
                var user = context.Users.Include("Galleries").Include("Galleries.Images")
                    .FirstOrDefault(u => u.ID == userID);
                if (user == null)
                {
                    throw new ServerErrorException("Invalid user");
                }

                var gallery = user.Galleries;
                if (gallery.Count == 0)
                {
                    throw new ServerErrorException("User has no gallery");
                }

                Image img = gallery.First().Images.FirstOrDefault(i => i.ID == imageID);
                gallery.First().Images.Remove(img);
                context.SaveChanges();
            }
        }

        private static IEnumerable<ImageModel> ParseImagesToModel(IEnumerable<Image> images)
        {
            var models =
                from img in images
                select new ImageModel()
                {
                    ID = img.ID,
                    Title = img.Title,
                    Url = img.Url,
                    DateUploaded = img.DateUploaded
                };

            return models.ToList();
        }
    }
}