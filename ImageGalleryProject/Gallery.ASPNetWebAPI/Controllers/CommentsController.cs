using Gallery.ASPNetWebAPI.Models;
using Gallery.ASPNetWebAPI.Repositories;
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
    public class CommentsController : BaseApiController
    {
        [HttpGet]
        [ActionName("get")]
        public HttpResponseMessage GetComments(int imageID, string sessionKey)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                var userID = UsersRepository.LoginUser(sessionKey);
                var previewComments = CommentsRepository.GetAll(imageID, userID);
                return previewComments;
            });
            return responseMsg;
        }

        [HttpPost]
        [ActionName("add")]
        public HttpResponseMessage AddComment([FromBody]CommentModel comment, string sessionKey)
        {
            var responseMsg = this.PerformOperation(() =>
            {
                var userId = UsersRepository.LoginUser(sessionKey);
                CommentsRepository.CreateComment(comment.ImageId, comment.Text, userId);

            });
            return responseMsg;
        }
    }
}
