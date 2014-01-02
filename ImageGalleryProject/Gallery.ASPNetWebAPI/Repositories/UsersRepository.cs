using Gallery.ASPNetWebAPI.Models;
using Gallery.Data;
using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gallery.Repositories
{
    public class UsersRepository : BaseRepository
    {
        private const string SessionKeyChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        private const int SessionKeyLen = 50;

        private const string ValidUsernameChars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_1234567890";
        private const string ValidNameChars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
        private const int MinUsernameNameChars = 2;
        private const int MaxUsernameNameChars = 30;

        private static void ValidateSessionKey(string sessionKey)
        {
            if (sessionKey.Length != SessionKeyLen || sessionKey.Any(ch => !SessionKeyChars.Contains(ch)))
            {
                throw new ServerErrorException("Invalid Password", "ERR_INV_AUTH");
            }
        }

        private static string GenerateSessionKey(int userId)
        {
            StringBuilder keyChars = new StringBuilder(50);
            keyChars.Append(userId.ToString());
            while (keyChars.Length < SessionKeyLen)
            {
                int randomCharNum;
                lock (rand)
                {
                    randomCharNum = rand.Next(SessionKeyChars.Length);
                }
                char randomKeyChar = SessionKeyChars[randomCharNum];
                keyChars.Append(randomKeyChar);
            }
            string sessionKey = keyChars.ToString();
            return sessionKey;
        }

        private static void ValidateUsername(string username)
        {
            if (username == null || username.Length < MinUsernameNameChars || username.Length > MaxUsernameNameChars)
            {
                throw new ServerErrorException("Username should be between 4 and 30 symbols long", "INV_USRNAME_LEN");
            }
            else if (username.Any(ch => !ValidUsernameChars.Contains(ch)))
            {
                throw new ServerErrorException("Username contains invalid characters", "INV_USRNAME_CHARS");
            }
        }

        private static void ValidateName(string nickname)
        {
            if (nickname == null || nickname.Length < MinUsernameNameChars || nickname.Length > MaxUsernameNameChars)
            {
                throw new ServerErrorException("Name should be between 2 and 30 symbols long", "INV_NICK_LEN");
            }
            else if (nickname.Any(ch => !ValidNameChars.Contains(ch)))
            {
                throw new ServerErrorException("Name contains invalid characters", "INV_NICK_CHARS");
            }
        }

        private static void ValidateAuthCode(string authCode)
        {
            if (authCode.Length != Sha1CodeLength)
            {
                throw new ServerErrorException("Invalid authentication code length", "INV_USR_AUTH_LEN");
            }
        }

        /* public members */

        public static void CreateUser(string username, string firstName, string lastName, string authCode)
        {
            ValidateUsername(username);
            ValidateName(firstName);
            ValidateName(lastName);
            ValidateAuthCode(authCode);
            using (GalleryContext context = new GalleryContext())
            {
                var usernameToLower = username.ToLower();
                var firstNameToLower = firstName.ToLower();
                var lastNameToLower = lastName.ToLower();

                var dbUser = context.Users.FirstOrDefault(u => u.Username.ToLower() == usernameToLower);

                if (dbUser != null)
                {
                    if (dbUser.Username.ToLower() == usernameToLower)
                    {
                        throw new ServerErrorException("Username already exists", "ERR_DUP_USR");
                    }
                }

                dbUser = new User()
                {
                    Username = usernameToLower,
                    FirstName = firstName,
                    LastName = lastName,
                    AuthCode = authCode
                };
                context.Users.Add(dbUser);
                context.SaveChanges();
            }
        }

        public static string LoginUser(string username, string authCode, out string firstName, out string lastName)
        {
            ValidateUsername(username);
            ValidateAuthCode(authCode);
            var context = new GalleryContext();
            using (context)
            {
                var usernameToLower = username.ToLower();
                var user = context.Users.FirstOrDefault(u => u.Username.ToLower() == usernameToLower && u.AuthCode == authCode);
                if (user == null)
                {
                    throw new ServerErrorException("Invalid user authentication", "INV_USR_AUTH");
                }

                var sessionKey = GenerateSessionKey((int)user.ID);
                user.SessionKey = sessionKey;
                firstName = user.FirstName;
                lastName = user.LastName;
                context.SaveChanges();
                return sessionKey;
            }
        }

        public static int LoginUser(string sessionKey)
        {
            ValidateSessionKey(sessionKey);
            var context = new GalleryContext();
            using (context)
            {
                var user = context.Users.FirstOrDefault(u => u.SessionKey == sessionKey);
                if (user == null)
                {
                    throw new ServerErrorException("Invalid user authentication", "INV_USR_AUTH");
                }
                return (int)user.ID;
            }
        }

        public static void LogoutUser(string sessionKey)
        {
            ValidateSessionKey(sessionKey);
            var context = new GalleryContext();
            using (context)
            {
                var user = context.Users.FirstOrDefault(u => u.SessionKey == sessionKey);
                if (user == null)
                {
                    throw new ServerErrorException("Invalid user authentication", "INV_USR_AUTH");
                }
                user.SessionKey = null;
                context.SaveChanges();
            }
        }

        //public static IEnumerable<UserScore> GetAllUsers()
        //{
        //    var context = new BullsAndCowsEntities();
        //    using (context)
        //    {
        //        var users =
        //            (from user in context.Users
        //             select new UserScore()
        //             {
        //                 Nickname = user.Nickname,
        //                 Score = user.Scores.Any() ? user.Scores.Sum(sc => sc.Value) : 0
        //             });
        //        return users.ToList();
        //    }
        //}

        internal static IEnumerable<UserPreviewModel> GetAllUsers()
        {
            var context = new GalleryContext();
            var result = context.Users.Select(UserPreviewModel.FromUser).ToList();

            return result;
        }
    }
}
