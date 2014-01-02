/// <reference path="http-requester.js" />
/// <reference path="class.js" />

// ------------------------------------------------NEEDS TO BE UPDATED!!!! ---------------------------------------------------------------
var persister = (function () {

    var nickname = localStorage.getItem("username");
    var sessionKey = localStorage.getItem("sessionKey");

    function saveUserData(userData) {
        localStorage.setItem("username", userData.username);
        localStorage.setItem("sessionKey", userData.sessionKey);
        username = userData.username;
        sessionKey = userData.sessionKey;
    }

    function clearUserData() {
        localStorage.removeItem("username");
        localStorage.removeItem("sessionKey");
        username = "";
        sessionKey = "";
    }

    var MainPersister = Class.create({
        init: function (rootUrl) {
            this.rootUrl = rootUrl;
            this.user = new UserPersister(this.rootUrl);
            this.gallery = new GalleryPersister(this.rootUrl);
            this.album = new AlbumPersister(this.rootUrl);
            this.images = new ImagePersister(this.rootUrl);
            this.comments = new CommentPersister(this.rootUrl);
            this.messages = new MessagesPersister(this.rootUrl);
            this.battle = new BattlePersister(this.rootUrl);
        },
        isUserLoggedIn: function () {
            var isLoggedIn = nickname != null && sessionKey != null;
            return isLoggedIn;
        },
        nickname: function () {
            return nickname;
        }
    });

    var UserPersister = Class.create({
        init: function (rootUrl) {
            this.rootUrl = rootUrl + "users/";
        },
        login: function (user, success, error) {
            var url = this.rootUrl + "login";
            var userData = {
                username: user.username,
                authCode: CryptoJS.SHA1(user.username + user.password).toString(),
            };

            httpRequester.postJSON(url, userData,
                function (data) {

                    data.username = userData.username;
                    saveUserData(data);
                    success(data);
                }, error);
        },
        register: function (user, success, error) {
            var url = this.rootUrl + "register";
            var userData = {
                username: user.username,
                firstName: user.firstName,
                lastName: user.lastName,
                authCode: CryptoJS.SHA1(user.username + user.password).toString(),
            };
            httpRequester.postJSON(url, userData,
                function (data) {
                    saveUserData(data);
                    success(data);
                }, error);
        },
        logout: function (success, error) {
            var url = this.rootUrl + "logout/" + sessionKey;
            httpRequester.getJSON(url, function (data) {
                clearUserData();
                success(data);
            }, error);
        },
        getAll: function(success, error){
            var url = this.rootUrl + "all";
            httpRequester.getJSON(url, function (data) {
                success(data);
            }, error)
        },
        scores: function (success, error) {
            var url = this.rootUrl + "scores/" + sessionKey;
            httpRequester.getJSON(url, success, error);
        }
    });
    
    var GalleryPersister = Class.create({
        init: function (url) {
            this.rootUrl = url + "galleries/";
        },
        getSingle: function (username, success, error) {
            var url = this.rootUrl + "getSingle";
            var galleryUsername = username;

            httpRequester.postJSON(url, galleryUsername, function (data) {
                success(data);
            }, error);
        },
        create: function (game, success, error) {
            var gameData = {
                title: game.title,
            };

            var url = this.rootUrl + "create/" + sessionKey;
            httpRequester.postJSON(url, gameData, success, error);
        },
        join: function (game, success, error) {            
            var url = this.rootUrl + "join/" + sessionKey;
            httpRequester.postJSON(url, game, success, error);
        },
        start: function (gameId, success, error) {
            var url = this.rootUrl + gameId + "/start/" + sessionKey;
            httpRequester.getJSON(url, success, error);

        },
        myActive: function (success, error) {
            var url = this.rootUrl + "my-active/" + sessionKey;
            httpRequester.getJSON(url, success, error);
        },
        open: function (success, error) {
            var url = this.rootUrl + "open/" + sessionKey;
            httpRequester.getJSON(url, success, error);
        },
        field: function (gameId, success, error) {
            var url = this.rootUrl + gameId + "/field/" + sessionKey;
            httpRequester.getJSON(url, success, error);
        },
    });

    var BattlePersister = Class.create({
        init: function (url) {
            this.rootUrl = url + 'battle/';
        },
        move: function (gameId, unit, success, error) {
            var url = this.rootUrl + gameId + "/move/" + sessionKey;
            httpRequester.postJSON(url, unit, success, error);
        },
        attack: function (gameId, unit, success, error) {
            var url = this.rootUrl + gameId + "/attack/" + sessionKey;
            httpRequester.postJSON(url, unit, success, error);
        },
        defend: function (gameId, data, success, error) {
            var url = this.rootUrl + gameId + "/defend/" + sessionKey;
            httpRequester.postJSON(url, data, success, error);
        }
    });

    var MessagesPersister = Class.create({
        init: function (url) {
            this.rootUrl = url + "messages/";
        },
        unread: function (success, error) {
            var url = this.rootUrl + "unread/" + sessionKey;
            httpRequester.getJSON(url, success, error);
        },
        all: function (success, error) {
            var url = this.rootUrl + "all/" + sessionKey;
            httpRequester.getJSON(url, success, error);
        }
    });

    var AlbumPersister = Class.create({
        init: function (url) {
            this.rootUrl = url + "albums/";
        },
        create: function (albumName, success, error) {
            var url = this.rootUrl + "create/" + sessionKey;
            var albumData = {title: albumName};

            httpRequester.postJSON(url, albumData, function (data) {
                success(data);
            }, error);
        },
        get: function (albumID, success, error) {
            var url = this.rootUrl + "get/" + sessionKey + "?albumID=" + albumID;
            httpRequester.getJSON(url, success, error);
        }
    });

    var ImagePersister = Class.create({
        init: function (url) {
            this.rootUrl = url + "Images/";
        },
        getImageByID: function (imageID, success, error) {
            var url = this.rootUrl + "byImageID/" + sessionKey + "?id=" + imageID;
            httpRequester.getJSON(url, success, error);
        }
    });

    var CommentPersister = Class.create({
        init: function (url) {
            this.rootUrl = url + "Comments/";
        },
        get: function (imageID, success, error) {
            var url = this.rootUrl + "get/" + sessionKey + "?id=" + imageID;
            httpRequester.getJSON(url, success, error);
        }
    });

    return {
        get: function (url) {
            return new MainPersister(url)
        }
    };

})();