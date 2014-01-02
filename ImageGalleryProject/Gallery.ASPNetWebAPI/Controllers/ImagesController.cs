using Gallery.ASPNetWebAPI.Models;
using Gallery.ASPNetWebAPI.Repositories;
using Gallery.Repositories;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace Gallery.ASPNetWebAPI.Controllers
{
    public class ImagesController : BaseApiController
    {
        // api/Images/all/{sessionKey}
        [HttpGet]
        [ActionName("all")]
        public HttpResponseMessage GetAllImages(string sessionKey)
        {
            var response = this.PerformOperation(() => 
            { 
                var userID = UsersRepository.LoginUser(sessionKey);
                var images = ImagesRepository.GetAllImages();
                return images;
            });
            return response;
        }

        // api/Images/own/{sessionKey}
        [HttpGet]
        [ActionName("own")]
        public HttpResponseMessage GetImagesByUserID(string sessionKey)
        {
            var response = this.PerformOperation(() =>
            {
                var userID = UsersRepository.LoginUser(sessionKey);
                var images = ImagesRepository.GetAllImagesByUserID(userID);
                return images;
            });
            return response;
        }
        // api/images/byUsername/{sessionKey}?username={username}
        [HttpGet]
        [ActionName("byUsername")]
        public HttpResponseMessage GetImagesByUsername(string sessionKey, 
            string username)
        {
            var response = this.PerformOperation(() =>
            {
                var userID = UsersRepository.LoginUser(sessionKey);
                var images = ImagesRepository.GetAllImagesByUsername(username);
                return images;
            });

            return response;
        }

        // api/Images/byImageID/{sessionKey}?id={id}
        [HttpGet]
        [ActionName("byImageID")]
        public HttpResponseMessage GetImageByID(string sessionKey, int id)
        {
            var response = this.PerformOperation(() =>
            {
                var userID = UsersRepository.LoginUser(sessionKey);
                var image = ImagesRepository.GetImageByID(id);
                return image;
            });

            return response;
        }

        // api/Images/add/{sessionKey}
        [HttpPost]
        [ActionName("add")]
        public HttpResponseMessage Add(string sessionKey, [FromBody] ImageModel image, int? albumID = null)
        {
            var response = this.PerformOperation(() => 
            {
                var userID = UsersRepository.LoginUser(sessionKey);
                ImagesRepository.AddImage(image, albumID, userID);
            });
            return response;
        }

        // api/Images/Delete/{sessionKey}?imageID={imageID}
        [HttpDelete]
        public HttpResponseMessage Delete(string sessionKey, int imageID)
        {
            var response = this.PerformOperation(() => 
            {
                var userID = UsersRepository.LoginUser(sessionKey);
                ImagesRepository.DeleteImage(imageID, userID);
            });

            return response;
        }
    }
}
