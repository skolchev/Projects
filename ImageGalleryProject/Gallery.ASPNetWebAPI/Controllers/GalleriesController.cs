using Gallery.ASPNetWebAPI.Repositories;
using Gallery.Data;
using Gallery.Models;
using Gallery.Repositories;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace Gallery.ASPNetWebAPI.Controllers
{
    public class GalleriesController : BaseApiController
    {
        [HttpGet]
        [ActionName("get")]
        public HttpResponseMessage GetGalleries(string sessionKey)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                var previewGalleries = GalleryRepository.GetAll(sessionKey);
                return previewGalleries;
            });
            return responseMsg;
        }

        [HttpPost]
        [ActionName("getSingle")]
        public HttpResponseMessage GetGallery([FromBody]string username)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                var gallery = GalleryRepository.GetSingle(username);
                return gallery;
            });
            return responseMsg;
        }

        [HttpPost]
        [ActionName("add")]
        public HttpResponseMessage AddGallery(string sessionKey)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                GalleryRepository.CreateGallery("deffault", sessionKey);

            });
            return responseMsg;
        }
    }
}
