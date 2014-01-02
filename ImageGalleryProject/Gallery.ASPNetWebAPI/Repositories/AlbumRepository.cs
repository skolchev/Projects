

using Gallery.ASPNetWebAPI.Models;
using Gallery.Data;
using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//namespace Gallery.ASPNetWebAPI.Repositories
namespace Gallery.Repositories
{
    public class AlbumRepository : BaseRepository
    {
        private const string SessionKeyChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        private const int SessionKeyLen = 50;

        private const string ValidAlbumNameChars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_1234567890";
        private const int MinAlbumNameChars = 2;
        private const int MaxAlbumNameChars = 30;

        private static void ValidateSessionKey(string sessionKey)
        {
            if (sessionKey.Length != SessionKeyLen || sessionKey.Any(ch => !SessionKeyChars.Contains(ch)))
            {
                throw new ServerErrorException("Invalid Password", "ERR_INV_AUTH");
            }
        }
        private static void ValidateAlbumName(string albumName)
        {
            if (albumName == null || albumName.Length < MinAlbumNameChars || albumName.Length > MaxAlbumNameChars)
            {
                throw new ServerErrorException("The name of the album should be between 2 and 30 symbols long", "INV_USRNAME_LEN");
            }
            else if (albumName.Any(ch => !ValidAlbumNameChars.Contains(ch)))
            {
                throw new ServerErrorException("The name of the album contains invalid characters", "INV_USRNAME_CHARS");
            }
        }

        public static void CreateAlbum(AlbumModel album, int userID)
        {
            ValidateAlbumName(album.Title);

            using (GalleryContext context = new GalleryContext())
            {
                var albumNameToLower = album.Title.ToLower();

                //var dbUser = context.Users.FirstOrDefault(u => u.Username.ToLower() == usernameToLower);
                var dbAlbum = context.Albums.FirstOrDefault(a => a.Title.ToLower() == albumNameToLower);
                if (dbAlbum != null)
                {
                    if (dbAlbum.Title.ToLower() == albumNameToLower)
                    {
                        throw new ServerErrorException("Album already exists", "ERR_DUP_USR");
                    }
                }

                dbAlbum = new Album()
                {
                    Title = albumNameToLower,
                    DateCreated = album.DateCreated,
                    DateModified = album.DateModified
                };

                context.Users.Find(userID).Galleries.First().Albums.Add(dbAlbum);
                context.Albums.Add(dbAlbum);
                context.SaveChanges();
            }

        }
        internal static IEnumerable<AlbumPreviewModel> GetAllAlbums()
        {
            var context = new GalleryContext();
            var result = context.Albums.Select(AlbumPreviewModel.FromAlbum).ToList();
            
            return result;
        }

        internal static  AlbumFullModel GetAlbumByID(int albumID, int userID)
        {
            using (var context = new GalleryContext())
            {
                var images = context.Albums.FirstOrDefault(a => a.ID == albumID);

                return new AlbumFullModel
                {
                    Title = images.Title,
                    Images = 
                        (from i in images.Images
                        select new ImageModel
                        {
                            ID=i.ID,
                            Title=i.Title,
                            Url=i.Url
                        }).ToList()       
                    };
                };
            }
        }
    }